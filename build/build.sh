shopt -s globstar

for file in ../src/**/*.cpp ../src/*.cpp; do
    echo "Compiling $file"
    clang++ -std=c++17 -g -I../src -I/usr/include -I/home/tahsin/C++Libs/poly2tri -c "$file"
done

ar rcs libgpp.a *.o