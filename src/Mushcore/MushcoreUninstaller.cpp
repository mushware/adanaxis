//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreUninstaller.cpp
 *
 * Author: Andy Southgate 2002-2005
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
//%Header } KBBrKbnMxA+7BMI5EjKHMQ
/*
 * $Id: MushcoreUninstaller.cpp,v 1.5 2004/01/02 21:13:14 southa Exp $
 * $Log: MushcoreUninstaller.cpp,v $
 * Revision 1.5  2004/01/02 21:13:14  southa
 * Source conditioning
 *
 * Revision 1.4  2003/09/17 19:40:36  southa
 * Source conditioning upgrades
 *
 * Revision 1.3  2003/08/21 23:09:18  southa
 * Fixed file headers
 *
 * Revision 1.2  2003/01/17 13:30:41  southa
 * Source conditioning and build fixes
 *
 * Revision 1.1  2003/01/16 13:11:32  southa
 * Install and uninstall MustlPlatform
 *
 */

#include "MushcoreUninstaller.h"

#include "MushcoreFail.h"

using namespace Mushware;
using namespace std;

MushcoreUninstaller::MushcoreUninstaller(tFuncPtr inFuncPtr) :
    m_funcPtr(inFuncPtr)
{
    if (inFuncPtr == NULL)
    {
        throw(MushcoreLogicFail("Cannot pass NULL to MushcoreUninstaller"));
    }
}

MushcoreUninstaller::~MushcoreUninstaller()
{
    m_funcPtr();
}

void
MushcoreUninstaller::NullFunction(void) const
{
}
