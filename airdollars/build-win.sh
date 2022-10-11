#! /bin/bash

start=$(date +%s)

make clean

PATH=$(echo "$PATH" | sed -e 's/:\/mnt.*//g')
cd depends
make HOST=x86_64-w64-mingw32
cd ..
./autogen.sh
./configure --prefix=$PWD/depends/x86_64-w64-mingw32
make

strip src/airdollars*.exe
strip src/qt/airdollars*.exe

end=$(date +%s)
echo "Build Time: $(($end-$start)) seconds"

