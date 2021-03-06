#!/bin/bash

if [ "$1" == "debug" ]
then
    make clean
    make debug
    gdb mersuthepig
elif [ "$1" == "run" ]
then
    make clean
    make linux
    ./mersuthepig
elif [ "$1" == "clean" ]
then
    make clean
else
    make clean
    make linux
fi
