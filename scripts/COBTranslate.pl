#!/usr/bin/perl -w

##############################################################################
#
# This file contains original work by Andy Southgate.  Contact details can be
# found at http://www.mushware.com.  This file was placed in the Public
# Domain by Andy Southgate and Mushware Limited in 2004.
#
# This software carries NO WARRANTY of any kind.
#
##############################################################################
# $Id: COBTranslate.pl,v 1.1 2004/06/12 14:30:35 southa Exp $
# $Log: COBTranslate.pl,v $
# Revision 1.1  2004/06/12 14:30:35  southa
# Created
#

use COBHandler;

use strict;

my $gVerbose = 1;

sub main()
{
    my $inFile = "../test/COB/Cube0.cob";
    my $outFile = "../test/COB/Cube0.msh";
    COBHandler::Translate($inFile, $outFile);
}

main();
