//%Header {
/*****************************************************************************
 *
 * File: src/Game/InfernalLightLinks.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } A3BgkNC/Ao1li2+NUPn5yg
/*
 * $Id: InfernalLightLinks.cpp,v 1.9 2003/09/17 19:40:32 southa Exp $
 * $Log: InfernalLightLinks.cpp,v $
 * Revision 1.9  2003/09/17 19:40:32  southa
 * Source conditioning upgrades
 *
 * Revision 1.8  2003/08/21 23:08:47  southa
 * Fixed file headers
 *
 * Revision 1.7  2003/01/13 14:31:59  southa
 * Build frameworks for Mac OS X
 *
 * Revision 1.6  2003/01/12 17:32:55  southa
 * Mushcore work
 *
 * Revision 1.5  2002/12/29 20:59:56  southa
 * More build fixes
 *
 * Revision 1.4  2002/12/20 13:17:40  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.3  2002/10/22 20:42:05  southa
 * Source conditioning
 *
 * Revision 1.2  2002/10/11 14:01:12  southa
 * Lighting work
 *
 * Revision 1.1  2002/10/10 18:25:15  southa
 * Light links and test lights
 *
 */

#include "InfernalLightLinks.h"

#include "GameSTL.h"

using namespace Mushware;
using namespace std;

InfernalLightLinks::InfernalLightLinks()
{
    for (U32 i=0; i<kNumLinks; ++i)
    {
        m_links[i].valid=false;
    }
}

void
InfernalLightLinks::Sort(void)
{
    for (U32 i=1; i < kNumLinks; ++i)
    {
        MUSHCOREASSERT(i>0);
        if (m_links[i-1].valid && m_links[i].valid)
        {
            if (m_links[i-1].link > m_links[i].link)
            {
                // Swap them
                tLink temp=m_links[i-1];
                m_links[i-1]=m_links[i];
                m_links[i]=temp;
                if (i>1)
                {
                    i-=2;
                }
                else
                {
                    i=0;
                }
            }
        }
    }
}
