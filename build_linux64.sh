#!/bin/bash

file_name=$0
target=${file_name#*_}
target=${target%%.*}
build_dir=build/$target
dist_dir=../../dist/$target

if [ ! -d "$build_dir" ]; then
	mkdir -p $build_dir
fi

cd $build_dir
cmake ../.. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=$dist_dir -DTARGET=$target
make && make install

