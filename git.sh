#!/bin/bash

if [ "$1" == "init" ]
then
elif [ "$1" == "pull" ]
then
    git pull
    git checkout aca
    git fetch orign
    git merge orign/master
elif [ "$1" == "commit" ]
    git add *
    git commit -m "$2" -a
    git push
then
fi
