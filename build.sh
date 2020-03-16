#!/bin/sh

current_dir=$(cd `dirname $0`; pwd)
echo "current_dir: ${current_dir}"

# rm -rf $current_dir/build
mkdir -p $current_dir/build
cd $current_dir/build
cmake -DCMAKE_INSTALL_PREFIX="/" -DCMAKE_VERBOSE_MAKEFILE=OFF $current_dir
# make && make install DESTDIR=$current_dir
make