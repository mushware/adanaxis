#!/bin/sh
##############################################################################
#
# This file contains original work by Andy Southgate.  Contact details can be
# found at http://www.mushware.com.  This file was placed in the Public
# Domain by Andy Southgate and Mushware Limited 2002-2006.
#
# This software carries NO WARRANTY of any kind.
#
##############################################################################
#
# $Id: MakeInstaller.sh,v 1.10 2007/06/16 08:26:50 southa Exp $
# $Log: MakeInstaller.sh,v $
# Revision 1.10  2007/06/16 08:26:50  southa
# Prerelease tweaks
#
# Revision 1.9  2007/06/14 14:59:15  southa
# win32 fixes
#
# Revision 1.8  2007/06/14 01:03:53  southa
# win32 build fixes
#
# Revision 1.7  2006/06/26 17:03:35  southa
# win32 installer tweaks
#
# Revision 1.6  2006/06/26 12:55:13  southa
# win32 installer updates
#
# Revision 1.5  2005/08/05 10:33:38  southa
# win32 build fixes
#
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

if test "x$6" = "x"
then
echo "Usage: $0 <name> <package name> <version> <build directory> <data directory> <demo flag>"
exit 1
fi

name="$1"
package="$2"
version="$3"
builddir="$4"
datadir="$5"
if [ "$6" = "1" ]; then
  type='demo'
  appSuffix=' Demo'
else
  type='full'
  appSuffix=''
fi
imageSuffix="-$type"
releasedir="release/$name"
readmedir="release/$name/documents"
appdir="$datadir/system/"
resourcesdir="$releasedir"
echo "Building win32 installer for '$name' version '$version'"
echo "from '$builddir' and '$datadir' to '$releasedir'"

cp -pR "$builddir/$package.exe" "$appdir"

for filename in VisualStudio/visualclibs/*.dll VisualC/ruby/Release/mushruby.dll
do
cp "$filename" "${appdir}"
done

rm -rf "$releasedir"
mkdir -p release
cp -pR "$datadir" "$releasedir"

find "$releasedir" -type d -name 'CVS' -prune -exec rm -rf "{}" \;
find "$releasedir" -name '.DS_Store' -exec rm -f "{}" \;
find "$releasedir" -name 'Makefile*' -exec rm -f "{}" \;
rm -rf "$releasedir/mushware-cache"
rm -rf "$releasedir/pixelsrc"
rm -rf "$releasedir/wavesrc"

ruby scripts/AmendToType.rb --releasedir="$releasedir" --resourcesdir="$resourcesdir" \
  --type="$type" --name="$name" || exit 1

cp "$releasedir/system/start.txt" "$releasedir/system/start_backup.txt"

mkdir -p "$readmedir"
for filename in
do
cp "$filename" "${readmedir}"
done

cp "$releasedir/COPYING" "${readmedir}/Licence.txt"
cp ChangeLog "${readmedir}/ChangeLog.txt"

# Copy the source tar archive, removing the data directory in the pipe
gunzip -c "$package-$version.tar.gz" | tar --wildcards --delete "$package-$version/data-*" | GZIP=--best gzip > "$releasedir/system/$package-src-$version.tar.gz"

echo 'Converting text and XML file to DOS line endings'
find "$releasedir" \( -iname '*.xml' -o -iname '*.txt' \) -exec unix2dos {} \;

echo 'Building win32 installer'

# Copy non-executable files
cp 'win32/Mushware web site.url' "$releasedir"

cd win32
ruby FileListToNSI.rb installer.nsi installer_new.nsi "$name" "${name}$appSuffix $version" "${package}$imageSuffix-win32-$version.exe" || exit 1
makensis installer_new.nsi

echo 'Done'
