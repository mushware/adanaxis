#!/bin/sh
#
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
# $Id: autogen.sh,v 1.2 2002/10/06 11:17:33 southa Exp $
# $Log: autogen.sh,v $
# Revision 1.2  2002/10/06 11:17:33  southa
# Fixed missing . in find
#
# Revision 1.1  2002/09/01 22:04:37  southa
# Created
#

chmod +x autogen.sh
chmod +x ic2
chmod +x install-sh

cd src
echo Building Makefile.am in `pwd`
echo 'bin_PROGRAMS=ic2binary' > Makefile.am
echo -n 'ic2binary_SOURCES=' >> Makefile.am
find . -path './Platform/*/*' -prune -o -name '*.cpp' -exec echo -n " " {} \;  >> Makefile.am
find . -path './Platform/*/*' -prune -o -name '*.h' -exec echo -n " " {} \;  >> Makefile.am
find . -path './Platform/*/*' -prune -o -name 'sstream' -exec echo -n " " {} \; >> Makefile.am
echo '' >> Makefile.am
echo INCLUDES=-I\$\{srcdir\}/API >> Makefile.am
echo -n 'EXTRA_DIST=' >> Makefile.am
find . -path './Platform/*/*' -a -name '*.h' -exec echo -n " " {} \;  >> Makefile.am
find . -path './Platform/*/*' -a -name '*.cpp' -exec echo -n " " {} \;  >> Makefile.am
echo '' >> Makefile.am
cd ..

cd ic2data
echo Building data Makefile.am in `pwd`
rm -f Makefile.am
echo -n 'nobase_dist_pkgdata_DATA =' >> Makefile.am
find . -path '*CVS' -prune -o -name 'Makefile*' -prune -o -type f -exec echo -n " " {} \; | sed -e "s/\.\///g" >> Makefile.am
echo '' >> Makefile.am
cd ..

aclocal
autoheader
automake
autoconf

echo Done.
