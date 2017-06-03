pwd
git submodule update --init --recursive
brew install -vd sfml
ls -R /usr/local/opt/sfml/
ls -a /usr/share
mkdir build
cd build
cmake .. -DSFML_DIR=/usr/local/opt/sfml/
make
