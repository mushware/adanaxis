#!/bin/sh
##############################################################################
#
# This file contains original work by Andy Southgate.  Contact details can be
# found at http://www.mushware.com/. This file was placed in the Public
# Domain by Andy Southgate and Mushware Limited in 2005.
#
# This software carries NO WARRANTY of any kind.
#
##############################################################################
#
# $Id: MakeRelease.sh,v 1.11 2007/03/13 21:45:10 southa Exp $
# $Log: MakeRelease.sh,v $
# Revision 1.11  2007/03/13 21:45:10  southa
# Release process
#
# Revision 1.10  2006/06/22 19:07:25  southa
# Build fixes
#
# Revision 1.9  2005/08/02 14:37:44  southa
# Adanaxis control demo work
#
# Revision 1.8  2005/06/04 13:53:58  southa
# Release tweaks
#
# Revision 1.7  2005/06/04 13:45:11  southa
# Release 0.1.2 tweaks
#
# Revision 1.6  2005/06/04 13:18:44  southa
# Updates for Mac OS Release 0.1.2
#
# Revision 1.5  2005/05/27 19:25:24  southa
# win32 build fixes
#
# Revision 1.4  2005/05/20 14:55:30  southa
# Release tweaks
#
# Revision 1.3  2005/05/20 13:18:59  southa
# Release work
#
# Revision 1.2  2005/05/20 10:26:24  southa
# Release work
#
# Revision 1.1  2005/05/19 13:03:40  southa
# Mac release work
#

# Script for generating the Mac OS X release

if test "x$5" = "x"
then
echo "Usage: $0 <name> <package name> <version> <build directory> <data directory>"
exit 1
fi

name="$1"
package="$2"
version="$3"
builddir="$4"
datadir="$5"
releasedir="release/$name"
readmedir="release/$name"
sourceapp="$builddir/$name.app"
appdir="$releasedir/$name.app"
resourcesdir="$appdir/Contents/Resources/mushware-resources"

SetFile="/Developer/Tools/SetFile"

echo "Building MacOS X release for project '$name' version '$version'"
echo "from '$builddir' and '$datadir' to '$releasedir'"

echo 'This scripts expects that the macosxlibs checkout is present.'

rm -rf "$releasedir"
mkdir -p "$releasedir"
cp -pR "$sourceapp" "$appdir"
rm -f "$resourcesdir"
cp -pR "$datadir" "$resourcesdir"

find "$resourcesdir" -type d -name 'CVS' -prune -exec rm -rf "{}" \;
find "$resourcesdir" -name '.DS_Store' -exec rm -f "{}" \;
find "$resourcesdir" -name 'Makefile*' -exec rm -f "{}" \;

rm -rf "$resourcesdir/mushware-cache"
rm -rf "$resourcesdir/pixelsrc"
rm -rf "$resourcesdir/wavesrc"

cp "$resourcesdir/system/start.txt" "$resourcesdir/system/start_backup.txt"

mkdir -p "$readmedir"
for filename in
do
ditto -rsrcFork "$filename" "${readmedir}"
done

cp COPYING "${readmedir}/Licence.txt"
cp ChangeLog "${readmedir}/ChangeLog.txt"

# Copy the source tar archive, removing the data directory in the pipe
gunzip -c "$package-$version.tar.gz" | tar --delete "$package-$version/data-*" | GZIP=--best gzip > "$resourcesdir/system/$package-src-$version.tar.gz"

ditto -xz -rsrc "macosx/Mushware web site.webloc.cpgz" "${releasedir}"

echo Fixing up file types
find "${releasedir}" -name '*.txt' -exec $SetFile -a E "{}" \;
find "${releasedir}" -name '*.pdf' -exec echo $SetFile -a E "{}" \;
# find ${releasedir} -name '*.url' -exec $SetFile -a E -t LINK -c MSIE {} \;

echo Setting permissions
find "${releasedir}" -perm +0100 -exec chmod 0777 "{}" \;
find "${releasedir}" -false -perm +0100 -exec chmod 0666 "{}" \;

echo Bulding disk image
imagename="release/$package-macosx-$version.dmg"
tempimagename="release/temp_$package-macosx-$version.dmg"
rm -f "${tempimagename}" "${imagename}"
hdiutil create -ov -anyowners -fs HFS+ -srcFolder "${releasedir}" "${tempimagename}"
hdiutil convert -ov -format UDZO -o "${imagename}" "${tempimagename}"
rm "${tempimagename}"
hdiutil internet-enable "${imagename}"
# hdiutil imageinfo "${imagename}"
hdiutil verify "${imagename}"
chmod 0666 "${imagename}"
ls -l "${imagename}"
echo Done.  Name of disc image is $imagename.
