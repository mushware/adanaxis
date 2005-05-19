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
# $Id: MakeInstaller.sh,v 1.6 2003/04/06 12:35:23 southa Exp $
# $Log: MakeInstaller.sh,v $
# Revision 1.6  2003/04/06 12:35:23  southa
# Fixes for release
#
# Revision 1.5  2002/11/20 12:18:51  southa
# Remove installer for macosx
#
# Revision 1.4  2002/10/20 17:53:19  southa
# Preparation for 0.1.0
#
# Revision 1.3  2002/08/07 10:47:44  southa
# Preparation for release 0.0.3
#
# Revision 1.2  2002/07/01 15:16:40  southa
# MacOS X installer fixes
#
# Revision 1.1  2002/07/01 13:46:12  southa
# MacOS X installer automation
#
#

# Script for generating the MacOS X installer.  Needs a bit of manual
# intervention

CpMac=/Developer/Tools/CpMac
SetFile=/Developer/Tools/SetFile
releaseDir=`pwd`/release

if test "x$1" = "x"
then
echo Usage: $0 [version]
echo e.g. $0 0_0_1
exit 1
fi

version=$1

echo "Building MacOS X installer for version $version"

echo 'This scripts expects that the ProjectBuilder application is built and'
echo 'installed in the ic2data directory, make release has been done, and'
echo 'the macosxlibs checkout is present.'

rm "${releaseDir}/system/ic2"
strip "${releaseDir}/system/ic2.app/Contents/MacOS/ic2"

frameworksDir=${releaseDir}/system/ic2.app/Contents/Frameworks
mkdir "${frameworksDir}"

cd macosx
cd macosxlibs
# remake the links that CVS loses
/bin/sh MakeLinks.sh
for filename in *.dylib
do
cp -pR "$filename" "${frameworksDir}/$filename"
done
# cd back to macosx
cd ..

# for filename in *.txt
# do
# ditto -rsrcFork "$filename" "${releaseDir}/$filename"
# done

ditto -rsrcFork "Mushware web site.url" "${releaseDir}/Mushware web site.url"
ditto -rsrcFork "UpdateCheck.url" "${releaseDir}/system/UpdateCheck.url"

# Special for udevgames
# echo "*** Appending udevgames to contract.xml"
# sed -e "s/<\/contract>//" ../release/contracts/first-day/contract.xml > tmpfile$$
# cat tmpfile$$ contract-append.xml > ../release/contracts/first-day/contract.xml
# rm tmpfile$$

echo Fixing up file types
# find ${releaseDir} -name '*.txt' -exec $SetFile -a E {} \;
find ${releaseDir} -name '*.url' -exec $SetFile -a E -t LINK -c MSIE {} \;
ln -s 'system/ic2.app' "${releaseDir}/Infernal Contractor II"

echo Setting permissions
find ${releaseDir} -type f -exec chmod 0664 {} \;
find ${releaseDir} -type d -exec chmod 0775 {} \;
find ${releaseDir} -name ic2 -exec chmod 0775 {} \;
find ${releaseDir} -name '*.dylib' -exec chmod 0775 {} \;

echo Done.  Name for disc image is IC2-macosx-setup-$version
