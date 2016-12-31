cd lib\spotify-json
rmdir build32 /S /Q
mkdir build32
cd build32
cmake .. -DBoost_NO_BOOST_CMAKE=TRUE ^
         -DBOOST_ROOT=..\..\..\packages\boost.1.62.0.0\lib\native
cmake --build . --config Debug
cmake --build . --config Release
cd ..\..\..