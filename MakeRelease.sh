#!/bin/sh
cd ic2data
echo Entering directory `pwd`
DEST=../release
echo Removing $DEST
rm -rf $DEST
mkdir $DEST
echo Making directories in $DEST
find . -path '*CVS' -prune -o -type d -exec mkdir -p $DEST/{} \;
echo Copying from . to $DEST
find . -path '*CVS' -prune -o -name '._ASP500.csv' -o -name '.DS_Store' -prune -o -type f -exec cp -p {} $DEST/{} \;
echo Done
