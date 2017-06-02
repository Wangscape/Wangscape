pwd
git submodule update --init --recursive
brew install sfml boost
mkdir build
cd build
cmake ..
make
