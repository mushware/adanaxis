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
# $Id: MakeInstaller.sh,v 1.4 2005/05/27 19:25:24 southa Exp $
# $Log: MakeInstaller.sh,v $
# Revision 1.4  2005/05/27 19:25:24  southa
# win32 build fixes
#
# Revision 1.3  2002/10/20 22:31:06  southa
# Fixed win32 release build
#
# Revision 1.2  2002/08/27 13:18:11  southa
# Fixed line endings in LICENCE file
#
# Revision 1.1  2002/08/07 12:36:14  southa
# Created
#

# Script for generating the win32 installer.

if test "x$4" = "x"
then
echo 'Usage: $0 <name> <version> <build directory> <data directory>'
exit 1
fi

name="$1"
package="$2"
version="$3"
builddir="$4"
datadir="$5"
releasedir="release/$name"
readmedir="release/$name/documents"
appdir="$datadir/system/"

echo "Building win32 installer for '$name$' version '$version'"
echo "from '$builddir' and '$datadir' to '$releasedir'"

cp -pR "$builddir/$package.exe" "$appdir"

for filename in VisualC/visualclibs/*.dll
do
cp "$filename" "${appdir}"
done

rm -rf "$releasedir"
mkdir -p release
cp -pR "$datadir" "$releasedir"

find "$releasedir" -type d -name 'CVS' -prune -exec rm -rf "{}" \;
find "$releasedir" -name '.DS_Store' -exec rm -f "{}" \;
find "$releasedir" -name 'Makefile*' -exec rm -f "{}" \;

cp "$releasedir/system/start.txt" "$releasedir/system/start_backup.txt"

mkdir -p "$readmedir"
for filename in
do
cp "$filename" "${readmedir}"
done

cp COPYING "${readmedir}/Licence.txt"
cp ChangeLog "${readmedir}/ChangeLog.txt"

# Copy the source tar archive, removing the data directory in the pipe
gunzip -c "$package-$version.tar.gz" | tar --delete "$package-$version/data-*" | GZIP=--best gzip > "$releasedir/system/$package-src-$version.tar.gz"

echo 'Converting text and XML file to DOS line endings'
find "$releasedir" \( -iname '*.xml' -o -iname '*.txt' \) -exec unix2dos {} \;

echo 'Building win32 installer'

# Copy non-executable files
cp 'win32/Mushware web site.url' "$releasedir"

cd win32
c:/ruby/bin/ruby FileListToNSI.rb installer.nsi installer_new.nsi "$name"
makensis installer_new.nsi

echo 'Done'
