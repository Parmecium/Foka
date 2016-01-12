#!/bin/bash

if [ "$1" == "init" ]
then
    git checkout aca
elif [ "$1" == "pull" ]
then
    git checkout aca
    git pull origin aca
    git pull origin master
    git merge master
elif [ "$1" == "commit" ]
then
    git add --all
    git commit -m "$2" -a
    git push origin aca
fi
