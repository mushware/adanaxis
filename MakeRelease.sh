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
cp ../AUTHORS $DEST/AUTHORS.txt
cp ../ChangeLog $DEST/ChangeLog.txt
cp ../COPYING $DEST/COPYING.txt
cp ../INSTALL $DEST/INSTALL.txt
cp ../NEWS $DEST/NEWS.txt
cp ../README $DEST/README.txt
cp system/start.txt system/start_backup.txt
mkdir $DEST/save
chmod -R g+w $DEST
echo Done
