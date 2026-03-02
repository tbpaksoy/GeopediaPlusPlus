import geopandas as gpd
import os
import sys
import requests
import xml.etree.ElementTree as ET


def get_s3_file_list():
    bucket_url = "https://naturalearth.s3.amazonaws.com/"
    headers = {"User-Agent": "Mozilla/5.0"}

    try:
        response = requests.get(bucket_url, headers=headers)
        response.raise_for_status()

        root = ET.fromstring(response.content)

        ns = {'s3': 'http://s3.amazonaws.com/doc/2006-03-01/'}

        files = [child.find('s3:Key', ns).text for child in root.findall('s3:Contents', ns)
                 if child.find('s3:Key', ns).text.endswith('.zip')]

        return sorted(files)
    except requests.exceptions.RequestException as e:
        print(f"Error fetching S3 file list: {e}")
        return []


def main():

    args = sys.argv

    if len(args) < 3:
        return

    index: int = -1

    if args[1].isdecimal():
        index = int(args[1])

    file_list = get_s3_file_list()

    if index == -1 and len(file_list) > 0 and args[1] in file_list:
        index = file_list.index(args[1])

    if not file_list:
        print("No files found or error occurred.")
        sys.exit(1)
    for file in range(len(file_list)):
        print(f"File {file}: {file_list[file]}")

    temp_zip = "temp_download.zip"

    try:
        if index < 0 or index >= len(file_list):
            print("Invalid index. Exiting.")
            sys.exit(1)
        target_key = file_list[int(
            index)]
        download_url = f"https://naturalearth.s3.amazonaws.com/{target_key}"

        output_name = args[2]
        if not output_name.endswith(".json") and not output_name.endswith(".geojson"):
            sys.exit("Output filename must end with .json or .geojson")

        if not os.path.exists("data"):
            os.makedirs("data")

        print(f"Downloading {target_key}...")
        response = requests.get(download_url, headers={
                                "User-Agent": "Mozilla/5.0"})

        with open(temp_zip, 'wb') as f:
            f.write(response.content)

        response.raise_for_status()
        data = gpd.read_file(temp_zip)
        data.to_file(f"data/{output_name}", driver="GeoJSON")
        print(f"File saved as data/{output_name}")
    finally:
        if os.path.exists(temp_zip):
            os.remove(temp_zip)


if __name__ == "__main__":
    main()
