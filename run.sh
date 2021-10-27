#/bin/bash

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:../lib

if [ ! -n "$1" ]
then
	echo "usage: ./run.sh appname"
else
	./$1 $2 $3 $4 $5
fi
