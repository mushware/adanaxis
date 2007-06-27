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

# $Id: app.prebuild.sh,v 1.1 2007/06/27 11:56:44 southa Exp $
# $Log: app.prebuild.sh,v $
# Revision 1.1  2007/06/27 11:56:44  southa
# Debian packaging
#
# Revision 1.2  2005/05/27 19:25:23  southa
# win32 build fixes
#
# Revision 1.1  2003/09/17 20:04:58  southa
# Build changes
#

echo Executing prebuild script

# Run the source conditioner if present
if [ -e SourceConditioner.pl ];then
perl -w SourceConditioner.pl
fi
