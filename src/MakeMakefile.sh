#!/bin/sh
echo Regenerating Makefile.am
rm Makefile.am
echo bin_PROGRAMS=coreapp > Makefile.am
echo -n coreapp_SOURCES= >> Makefile.am
/usr/bin/find . -name '*.cpp' -exec echo -n {} " " \; >> Makefile.am
/usr/bin/find . -name '*.hp' -exec echo -n {} " " \; >> Makefile.am
echo >> Makefile.am
echo INCLUDES=-IAPI >> Makefile.am

