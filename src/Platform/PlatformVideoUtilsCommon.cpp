//%Header {
/*****************************************************************************
 *
 * File: src/Platform/PlatformVideoUtilsCommon.cpp
 *
 * Copyright: Andy Southgate 2002-2007, 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/
//%Header } RVJe+k32gMZmehP7lN7Q1Q
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
