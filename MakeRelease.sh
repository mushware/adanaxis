#!/bin/sh
##############################################################################
#
# This file contains original work by Andy Southgate.  Contact details can be
# found at http://www.mushware.com.  This file was placed in the Public
# Domain by Andy Southgate and Mushware Limited in 2002.
#
# This software carries NO WARRANTY of any kind.
#
##############################################################################

#
# $Id: MakeRelease.sh,v 1.6 2002/10/22 22:36:17 southa Exp $
# $Log: MakeRelease.sh,v $
# Revision 1.6  2002/10/22 22:36:17  southa
# Use SDL_INIT_NOPARACHUTE to avoid hang exit on MacOS 10.1.5
#

echo Entering directory `pwd`
DEST=../release
echo Removing $DEST
rm -rf $DEST
mkdir $DEST
echo Making directories in $DEST
find . -path '*CVS' -prune -o -type d -exec mkdir -p $DEST/{} \;
echo Copying from . to $DEST
find . -path '*CVS' -prune -o -name '._ASP500.csv' -o -name '.DS_Store' -o -name 'Makefile*' -prune -o -type f -exec cp -p {} $DEST/{} \;
cp ../AUTHORS $DEST/AUTHORS.txt
cp ../ChangeLog $DEST/ChangeLog.txt
cp ../COPYING $DEST/COPYING.txt
cp ../INSTALL $DEST/INSTALL.txt
cp ../NEWS $DEST/NEWS.txt
cp ../README $DEST/README.txt
cp system/start.txt system/start_backup.txt
chmod -R g+w $DEST
echo Done
