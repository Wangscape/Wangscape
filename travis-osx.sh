pwd
git submodule update --init --recursive
brew install -vd sfml
mkdir build
cd build
cmake .. -DSFML_DIR=/usr/local/opt/sfml/
make
