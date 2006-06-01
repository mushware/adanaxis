//%Header {
/*****************************************************************************
 *
 * File: src/MushModel/MushModelCommands.cpp
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
//%Header } WKdpdtR8s/MXlXvt0wP5gQ
/*
 * $Id: MushModelCommands.cpp,v 1.2 2005/05/19 13:02:12 southa Exp $
 * $Log: MushModelCommands.cpp,v $
 * Revision 1.2  2005/05/19 13:02:12  southa
 * Mac release work
 *
 * Revision 1.1  2004/01/08 22:41:10  southa
 * MushModel commands
 *
 */

#include "MushModelCommands.h"

#include "MushModelMultiFacet.h"

using namespace Mushware;
using namespace std;

void
MushModelCommands::Install(void)
{
}

namespace { MushcoreInstaller Installer(MushModelCommands::Install); }

void
MushModelCommands::NullFunction(void)
{
}
