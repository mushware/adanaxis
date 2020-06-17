//%Header {
/*****************************************************************************
 *
 * File: src/Infernal/InfernalLightLinks.cpp
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
//%Header } VmgALJM8eclP3OmON5VkFA
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
