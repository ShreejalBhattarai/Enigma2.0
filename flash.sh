export PATH=/usr/bin:$PATH
rm -rf build
mkdir build
cd build
cmake ..
cmake --build .
