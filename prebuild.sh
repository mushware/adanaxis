#!/bin/sh

##############################################################################
#
# This file contains original work by Andy Southgate.  Contact details can be
# found at http://www.mushware.com/.  This file was placed in the Public
# Domain by Andy Southgate and Mushware Limited in 2002-2003.
#
# This software carries NO WARRANTY of any kind.
#
##############################################################################

# $Id$
# $Log$

echo Executing prebuild script

# Run the source conditioner if present
if [ -f SourceConditioner.pl ];then
perl -w SourceConditioner.pl
fi
