#!/bin/bash

. /work/sdk/sv-g6sh-qnx-system-sdk/qnxsdp-env.sh

file_name=$0
target=${file_name#*_}
target=${target%%.*}
arch=${file_name#*-}
arch=${arch%%.*}
build_dir=build/$target
dist_dir=../../dist/$target

if [ ! -d "$build_dir" ]; then
	mkdir -p $build_dir
fi

cd $build_dir
cmake ../.. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=$dist_dir -DTARGET=$target -DQNX_ARCH=$arch -DCMAKE_TOOLCHAIN_FILE=qnx.cmake
make && make install

