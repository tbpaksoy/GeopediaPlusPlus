set -euo pipefail

if [ -x "./build/build.sh" ]; then
    echo "Running ./build/build.sh to produce library..."
    (cd build && ./build.sh)
else
    echo "No build/build.sh found or not executable; skipping library build."
fi

includes=(
    /usr/local/include
    /home/tahsin/C++Libs/Clipper2/CPP/Clipper2Lib/include
    /home/tahsin/C++Libs/glfw/include
)
include_args=()

for inc in "${includes[@]}"; do
    include_args+=("-I$inc")
done

shopt -s nullglob

for file in *.cpp; do
    exe="${file%.cpp}"
    echo "Compiling $file -> $exe"
    clang++ -fcolor-diagnostics -fansi-escape-codes "${include_args[@]}" -g "$file" -o "$exe" -lglfw -lGL -lGLEW ./build/libgpp.a
done

if [ "${1-}" = "run" ]; then
    for file in *.cpp; do
        exe="${file%.cpp}"
        if [ -x "./$exe" ]; then
            echo "Running ./$exe"
            ./$exe
        else
            echo "Executable ./$exe not found or not executable; skipped."
        fi
    done
fi