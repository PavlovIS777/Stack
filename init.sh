mkdir build
cd build
cmake ..
make stack_drive
make test
sudo apt-get install libgtest-dev libgmock-dev
sudo apt-get install libtbb-dev