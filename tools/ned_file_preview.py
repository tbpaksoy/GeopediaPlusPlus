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

    file_list = get_s3_file_list()

    if not file_list:
        print("No files found or error occurred.")
        sys.exit(1)
    for file in range(len(file_list)):
        print(f"File {file}: {file_list[file]}")


if __name__ == "__main__":
    main()
