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
# $Id: MakeInstaller.sh,v 1.3 2002/08/07 10:47:44 southa Exp $
# $Log: MakeInstaller.sh,v $
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

rm release/system/ic2
strip release/system/ic2.app/Contents/MacOS/ic2

cd macosx
rm -rf resources
mkdir resources
chmod 0775 resources
cd macosxlibs
# remake the links that CVS loses
/bin/sh MakeLinks.sh
for filename in *.dylib
do
cp -pR $filename ../resources/$filename
chmod 0775 ../resources/$filename
done
# cd back to macosx
cd ..

# Copy executable files
install -m 0775 IC2-macosx-setup.post resources/IC2-macosx-setup-$version.post_install
install -m 0775 IC2-macosx-setup.post resources/IC2-macosx-setup-$version.post_upgrade

# Copy non-executable files
for filename in *.html *.url
do
cp -pR "$filename" "resources/$filename"
chmod 0664 "resources/$filename"
done

# Special for udevgames
echo "*** Appending udevgames to contract.xml"
sed -e "s/<\/contract>//" ../release/contracts/first-day/contract.xml > tmpfile$$
cat tmpfile$$ contract-append.xml > ../release/contracts/first-day/contract.xml
rm tmpfile$$

cd ../release
for filename in *.txt
do
cp "$filename" "../macosx/resources/$filename"
done

cd ../macosx
for filename in *.txt
do
cp "$filename" "resources/$filename"
done

cd resources

# Fix the types
for filename in *.txt
do
$SetFile -a E "$filename"
done

for filename in *.url
do
$SetFile -a E -t LINK -c MSIE "$filename"
done

for filename in *.txt *.url
do
chmod 0664 "$filename"
done

echo 'Done.  Please build the package using macosx/package-spec.pmsp'
echo "and save with name IC2-macosx-setup-$version.pkg (important)."
