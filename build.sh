#!/bin/bash

if [ "$1" == "debug" ]
then
    make clean
    make debug
    ./foka
elif [ "$1" == "run" ]
then
    make clean
    make linux
    ./foka
else
    make clean
    make linux
fi
