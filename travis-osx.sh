pwd
git submodule update --init --recursive
brew install sfml

git clone https://github.com/google/googletest.git
cd googletest
mkdir build
cd build
cmake ..
make
cd ../..

mkdir build
cd build
cmake .. -DCMAKE_MODULE_PATH=/usr/local/opt/sfml/share/SFML/cmake/Modules
make

./bin/WangscapeTest ../doc

for d in ../doc/examples/*/ ; do
    echo "Running example in $d/"
    ./bin/Wangscape "$d"/example_options.json
done
