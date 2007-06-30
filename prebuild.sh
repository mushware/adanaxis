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

# $Id: empty.prebuild.sh,v 1.1 2007/06/27 11:56:44 southa Exp $
# $Log: empty.prebuild.sh,v $
# Revision 1.1  2007/06/27 11:56:44  southa
# Debian packaging
#

echo 'Prebuild script (prebuild.sh) disabled for release'

# For development work re-enable the source conditioner by uncommenting
# the lines below

# Run the source conditioner if present
# if [ -e SourceConditioner.pl ];then
# perl -w SourceConditioner.pl
# fi
