#!/bin/sh

##############################################################################
#
# This file contains original work by Andy Southgate.  Contact details can be
# found at http://www.mushware.co.uk.  This file was placed in the Public
# Domain by Andy Southgate and Mushware Limited in 2002.
#
# This software carries NO WARRANTY of any kind.
#
##############################################################################

#
# $Id: MakeInstaller.sh,v 1.1 2002/08/07 12:36:14 southa Exp $
# $Log: MakeInstaller.sh,v $
# Revision 1.1  2002/08/07 12:36:14  southa
# Created
#

# Script for generating the win32 installer.

if test "x$1" = "x"
then
echo Usage: $0 [version]
echo e.g. $0 0_0_1
exit 1
fi

version=$1

echo "Building win32 installer for version $version"

cp -p win32/ic2_app.ico release/system
echo 'Converting text and XML file to DOS line endings'
find release \( -iname '*.xml' -o -iname '*.txt' \) -exec unix2dos {} \;
echo 'Converting LICENCE file to DOS line endings'
unix2dos win32/LICENCE
echo 'Building win32 installer'
cd win32
makensis installer.nsi
mv IC2-win32-setup-0_0_0.exe IC2-win32-setup-$version.exe
echo 'Done'
