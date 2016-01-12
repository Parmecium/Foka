#!/bin/bash

if [ "$1" == "debug" ]
then
    make clean
    make debug
    gdb foka
elif [ "$1" == "run" ]
then
    make clean
    make linux
    ./foka
elif [ "$1" == "clean" ]
then
    make clean
else
    make clean
    make linux
fi
