pwd
git submodule update --init --recursive
brew install sfml

git clone https://github.com/google/googletest.git
cd googletest
mkdir build
cd build
cmake ..
make
sudo make install
cd ../..

mkdir build
cd build
cmake .. -DCMAKE_MODULE_PATH=/usr/local/opt/sfml/share/SFML/cmake/Modules
make

./bin/WangscapeTest ../doc
