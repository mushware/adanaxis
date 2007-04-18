//%Header {
/*****************************************************************************
 *
 * File: src/Infernal/InfernalLightLinks.cpp
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
//%Header } +uUySXUXQW9cYWKi7tA7LQ
/*
 * $Id: InfernalLightLinks.cpp,v 1.6 2006/06/01 15:39:03 southa Exp $
 * $Log: InfernalLightLinks.cpp,v $
 * Revision 1.6  2006/06/01 15:39:03  southa
 * DrawArray verification and fixes
 *
 * Revision 1.5  2005/05/19 13:02:05  southa
 * Mac release work
 *
 * Revision 1.4  2004/01/02 21:13:08  southa
 * Source conditioning
 *
 * Revision 1.3  2003/10/04 15:32:10  southa
 * Module split
 *
 * Revision 1.2  2003/10/04 12:44:35  southa
 * File renaming
 *
 * Revision 1.1  2003/10/04 12:23:05  southa
 * File renaming
 *
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

#include "InfernalSTL.h"

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
