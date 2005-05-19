#!/bin/sh

##############################################################################
#
# This file contains original work by Andy Southgate.  Contact details can be
# found at http://www.mushware.co.uk.  This file was placed in the Public
# Domain by Andy Southgate and Mushware Limited in 2005.
#
# This software carries NO WARRANTY of any kind.
#
##############################################################################

#
# $Id: MakeInstaller.sh,v 1.6 2003/04/06 12:35:23 southa Exp $
# $Log: MakeInstaller.sh,v $

# Script for generating the Mac OS X package.  Needs a bit of manual
# intervention

name="$1"
version="$2"
builddir="$3"
datadir="$4"
releasedir="release/$name"
readmedir="release/$name/Read Me"
appdir="$datadir/system/$name.app"

SetFile="/Developer/Tools/SetFile"

echo "Building MacOS X release for project '$name' version '$version'"
echo "from '$builddir' and '$datadir' to '$releasedir'"

echo 'This scripts expects that the ProjectBuilder application is built and'
echo 'installed in the data directory, and the macosxlibs checkout is present.'

rm -rf "$appdir"
cp -pR "$builddir/$name.app" "$appdir"

rm -rf "$releasedir"
mkdir -p release
cp -pR "$datadir" "$releasedir"

find "$releasedir" -type d -name 'CVS' -prune -exec rm -rf "{}" \;
find "$releasedir" -name '.DS_Store' -exec rm -f "{}" \;

mkdir -p "$releasedir/Read Me"
for filename in macosx/*.txt
do
ditto -rsrcFork "$filename" "${readmedir}"
done

cp COPYING "${readmedir}/Licence.txt"
cp ChangeLog "${readmedir}/Copying.txt"

ditto -rsrcFork "macosx/Mushware web site.webloc" "${releasedir}/Mushware web site.webloc"

echo Fixing up file types
find "${releaseDir}" -name '*.txt' -exec $SetFile -a E {} \;
# find ${releasedir} -name '*.url' -exec $SetFile -a E -t LINK -c MSIE {} \;
ln -s "system/$name.app" "${releasedir}/$name.app"
echo Setting permissions
find ${releasedir} -perm +0100 -exec chmod 0777 {} \;
find ${releasedir} -false -perm +0100 -exec chmod 0666 {} \;

echo Bulding disk image
imagename="release/$name-macosx-$version.dmg"
tempimagename="release/temp_$name-macosx-$version.dmg"
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
