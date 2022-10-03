mkdir build
cd build
mkdir Release
mkdir Debug
cmake .. -DCMAKE_BUILD_TYPE=Debug
make test
sudo apt-get install libgtest-dev libgmock-dev
sudo apt-get install libtbb-dev