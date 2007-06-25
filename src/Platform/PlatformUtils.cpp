//%Header {
/*****************************************************************************
 *
 * File: src/Platform/PlatformUtils.cpp
 *
 * Author: Andy Southgate 2002-2007
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
//%Header } Zt0ORFgHY7Ga51/+T0jRpw
/*
 * $Id: PlatformUtils.cpp,v 1.20 2007/04/18 09:23:23 southa Exp $
 * $Log: PlatformUtils.cpp,v $
 * Revision 1.20  2007/04/18 09:23:23  southa
 * Header and level fixes
 *
 * Revision 1.19  2006/06/01 15:39:57  southa
 * DrawArray verification and fixes
 *
 * Revision 1.18  2005/05/19 13:02:21  southa
 * Mac release work
 *
 * Revision 1.17  2004/01/02 21:13:16  southa
 * Source conditioning
 *
 * Revision 1.16  2003/09/17 19:40:39  southa
 * Source conditioning upgrades
 *
 * Revision 1.15  2003/08/21 23:09:34  southa
 * Fixed file headers
 *
 * Revision 1.14  2003/02/05 18:49:52  southa
 * Build fixes
 *
 * Revision 1.13  2002/12/29 21:00:00  southa
 * More build fixes
 *
 * Revision 1.12  2002/12/20 13:17:47  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.11  2002/12/12 18:38:58  southa
 * Mustl separation
 *
 * Revision 1.10  2002/11/01 17:24:49  southa
 * Network links on win32
 *
 * Revision 1.9  2002/11/01 16:56:49  southa
 * Fixed platform inclusion
 *
 * Revision 1.8  2002/10/22 20:42:07  southa
 * Source conditioning
 *
 * Revision 1.7  2002/10/14 18:13:18  southa
 * GLModeDef work
 *
 * Revision 1.6  2002/08/27 08:56:29  southa
 * Source conditioning
 *
 * Revision 1.5  2002/08/07 13:36:51  southa
 * Conditioned source
 *
 * Revision 1.4  2002/07/06 18:04:20  southa
 * More designer work
 *
 * Revision 1.3  2002/06/27 12:36:08  southa
 * Build process fixes
 *
 * Revision 1.2  2002/06/11 16:23:57  southa
 * New paths to data files
 *
 * Revision 1.1  2002/06/06 14:59:57  southa
 * Mouse fixes
 *
 * Revision 1.1  2002/06/06 10:40:09  southa
 * Created
 *
 */

#include "PlatformInputUtils.cpp"
#include "PlatformMiscUtils.cpp"
#include "PlatformVideoUtils.cpp"

using namespace Mushware;
using namespace std;

const GLModeDef&
PlatformVideoUtils::DefaultModeDef(void) const
{
    U32 modeNum = 0;
    
    for (U32 i=2; i < m_modeDefs.size(); ++i)
    {
        if (m_modeDefs[i].Width() == 1024 &&
            m_modeDefs[i].Height() == 768)
        {
            modeNum = i;   
        }
    }
    return m_modeDefs[modeNum];
}

Mushware::U32
PlatformVideoUtils::ModeDefFind(const GLModeDef& inModeDef) const
{
    U32 retVal = 0;
    for (U32 i=1; i<m_modeDefs.size(); ++i)
    {
        if (inModeDef == m_modeDefs[i])
        {
            retVal = i;
        }
    }
    return retVal;
}

const GLModeDef&
PlatformVideoUtils::PreviousModeDef(const GLModeDef& inModeDef) const
{
    U32 modeNum = ModeDefFind(inModeDef);

    if (modeNum == 0)
    {
        modeNum = m_modeDefs.size() - 1;
    }
    else
    {
        --modeNum;
    }
    return m_modeDefs[modeNum];
}

const GLModeDef&
PlatformVideoUtils::NextModeDef(const GLModeDef& inModeDef) const
{
    U32 modeNum = ModeDefFind(inModeDef);
    
    ++modeNum;
    if (modeNum >= m_modeDefs.size())
    {
        modeNum = 0;
    }
    
    return m_modeDefs[modeNum];
}

U32
PlatformVideoUtils::NumModesGet(void) const
{
    return m_modeDefs.size();
}

void
PlatformVideoUtils::RenderModeInfo(U32 inNum) const
{
    throw MushcoreLogicFail("RenderModeInfo deprecated");
}
