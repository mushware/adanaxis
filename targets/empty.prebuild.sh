#!/bin/sh

##############################################################################
#
# This file contains original work by Andy Southgate.  Contact details can be
# found at http://www.mushware.com/.  This file was placed in the Public
# Domain by Andy Southgate and Mushware Limited in 2007.
#
# This software carries NO WARRANTY of any kind.
#
##############################################################################

# $Id: prebuild.sh,v 1.2 2005/05/27 19:25:23 southa Exp $
# $Log: prebuild.sh,v $

echo 'Prebuild script (prebuild.sh) disabled for release'

# For development work re-enable the source conditioner by uncommenting
# the lines below

# Run the source conditioner if present
# if [ -e SourceConditioner.pl ];then
# perl -w SourceConditioner.pl
# fi
