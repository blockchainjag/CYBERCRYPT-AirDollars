#! /bin/bash

start=$(date +%s)

make clean

./autogen.sh
./configure
make

strip src/airdollars*
strip src/qt/airdollars*

end=$(date +%s)
echo "Build Time: $(($end-$start)) seconds"

