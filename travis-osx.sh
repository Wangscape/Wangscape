pwd
git submodule update --init --recursive
brew install sfml armadillo qt5

mkdir build
cd build
cmake .. -DCMAKE_MODULE_PATH=/usr/local/opt/sfml/share/SFML/cmake/Modules -DCMAKE_PREFIX_PATH=$(brew --prefix qt5)
make

./bin/WangscapeTest ../doc

for d in ../doc/examples/*/ ; do
    echo "Running example in $d"
    ./bin/Wangscape "$d"/example_options.json -v
done
