#!/bin/sh

rm -rf release

echo "在Linux下构建VMarchTools!"
mkdir -p release
cd release || exit
cmake ..

echo "构建二进制文件!"
make

echo "建立VMarchTools软连接"
rm -rf /usr/bin/vmarch
ln -s $(pwd)/VMarchTools /usr/bin/vmarch
ls -lar /usr/bin | grep vmarch
