//%Header {
/*****************************************************************************
 *
 * File: src/Main/PrimaryMain.cpp
 *
 * Author: Andy Southgate 2002-2006
 *
 * This file contains original work by Andy Southgate.  The author and his
 * employer (Mushware Limited) irrevocably waive all of their copyright rights
 * vested in this particular version of this file to the furthest extent
 * permitted.  The author and Mushware Limited also irrevocably waive any and
 * all of their intellectual property rights arising from said file and its
 * creation that would otherwise restrict the rights of any party to use and/or
 * distribute the use of, the techniques and methods used herein.  A written
 * waiver can be obtained via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } KxuU1xe9B2cXSguXQDNP2Q
/*
 * $Id: PrimaryMain.cpp,v 1.2 2005/05/19 13:02:07 southa Exp $
 * $Log: PrimaryMain.cpp,v $
 * Revision 1.2  2005/05/19 13:02:07  southa
 * Mac release work
 *
 * Revision 1.1  2004/01/05 14:27:40  southa
 * MushPie work and build fixes
 *
 */

#include "PrimaryMain.h"
#include "SecondaryMain.h"

int main(int argc, char *argv[])
{
    return SecondaryMain(argc, argv);
}
