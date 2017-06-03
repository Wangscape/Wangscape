pwd
git submodule update --init --recursive
brew install sfml
mkdir build
cd build
cmake .. -DCMAKE_MODULE_PATH=/usr/local/opt/sfml/share/SFML/cmake/Modules
make
