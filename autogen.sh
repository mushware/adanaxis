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
# $Id: autogen.sh,v 1.7 2003/01/13 23:05:19 southa Exp $
# $Log: autogen.sh,v $
# Revision 1.7  2003/01/13 23:05:19  southa
# Mustl test application
#
# Revision 1.6  2003/01/11 17:12:09  southa
# Created
#
# Revision 1.5  2003/01/11 17:07:48  southa
# Mushcore library separation
#
# Revision 1.4  2002/12/17 00:58:26  southa
# Added support for libmustl target
#
# Revision 1.3  2002/10/06 22:09:56  southa
# Initial lighting test
#
# Revision 1.2  2002/10/06 11:17:33  southa
# Fixed missing . in find
#
# Revision 1.1  2002/09/01 22:04:37  southa
# Created
#

chmod +x autogen.sh
chmod +x install-sh

case "$1" in
ic2)
    echo Building configuration for package ic2
    echo
    cp -f ic2.configure.in configure.in
    cp -f ic2.Makefile.am Makefile.am
    chmod +x ic2
    
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
    ;;
    
mustl)
    echo Building configuration for package mustl
    echo
    cp -f mustl.configure.in configure.in
    cp -f lib.Makefile.am Makefile.am
    cd src
    echo Building Makefile.am in `pwd`
    echo 'lib_LTLIBRARIES=libmustl.la' > Makefile.am
    echo -n 'libmustl_la_SOURCES=' >> Makefile.am
    find . -name 'Mustl*.cpp' -exec echo -n " " {} \;  >> Makefile.am
    find . -name 'Mustl*.h' -exec echo -n " " {} \;  >> Makefile.am
    find . -name 'sstream' -exec echo -n " " {} \; >> Makefile.am
    echo '' >> Makefile.am
    
    echo 'bin_PROGRAMS=test_mustl' >> Makefile.am
    echo -n 'test_mustl_SOURCES=' >> Makefile.am
    find . -name 'TestMustl*.cpp' -exec echo -n " " {} \;  >> Makefile.am
    find . -name 'TestMustl*.h' -exec echo -n " " {} \;  >> Makefile.am
    find . -name 'sstream' -exec echo -n " " {} \; >> Makefile.am
    echo '' >> Makefile.am
    echo 'test_mustl_LDADD = libmustl.la' >> Makefile.am
        
    echo 'test_mustl_INCLUDES=-I\$\{srcdir\}/Mustl' >> Makefile.am

    cd ..
    echo -n 'EXTRA_DIST=' >> Makefile.am
    find test/mustl -name '*.mhtml' -exec echo -n " " {} \;  >> Makefile.am
    find test/mustl -name '*.html' -exec echo -n " " {} \;  >> Makefile.am
    find test/mustl -name '*.css' -exec echo -n " " {} \;  >> Makefile.am
    echo '' >> Makefile.am

    ;;

mushcore)
    echo Building configuration for package mushcore
    echo
    cp -f mushcore.configure.in configure.in
    cp -f lib.Makefile.am Makefile.am
    cd src
    echo Building Makefile.am in `pwd`

    echo 'lib_LTLIBRARIES=libmushcore.la' > Makefile.am

    echo -n 'libmushcore_la_SOURCES=' >> Makefile.am
    find . -path './Platform/*/*' -prune -o -name 'Mushcore*.cpp' -exec echo -n " " {} \;  >> Makefile.am
    find . -path './Platform/*/*' -prune -o -name 'Mushcore*.h' -exec echo -n " " {} \;  >> Makefile.am
    find . -path './Platform/*/*' -prune -o -name 'sstream' -exec echo -n " " {} \; >> Makefile.am
    echo '' >> Makefile.am    
    
    echo 'library_includedir=$(includedir)/Mushcore' >> Makefile.am

    echo -n 'library_include_HEADERS=' >> Makefile.am
    find . -path './Platform/*/*' -prune -o -name 'Mushcore*.h' -exec echo -n " " {} \;  >> Makefile.am
    echo '' >> Makefile.am    

    cd ..

    ;;


*)
echo Please supply a package name to build.  Choices are ic2, mustl. mushcore.
exit 1
esac


aclocal
autoheader
automake
autoconf

echo Done.
