//%Header {
/*****************************************************************************
 *
 * File: src/Platform/PlatformVideoUtilsCommon.cpp
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
//%Header } aIwXiGk9kHOd93Iw4g709A
/*
 * $Id$
 * $Log$
 */

#include "PlatformVideoUtils.h"

#include "mushGL.h"
#include "mushMedia.h"
#include "mushPlatform.h"

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
