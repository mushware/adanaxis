//%Header {
/*****************************************************************************
 *
 * File: src/GL/GLTextureDef.cpp
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
//%Header } OOrRAyvrCR3pOm/g3fMP8Q
/*
 * $Id: GLTextureDef.cpp,v 1.13 2006/06/01 15:38:53 southa Exp $
 * $Log: GLTextureDef.cpp,v $
 * Revision 1.13  2006/06/01 15:38:53  southa
 * DrawArray verification and fixes
 *
 * Revision 1.12  2005/05/19 13:02:00  southa
 * Mac release work
 *
 * Revision 1.11  2004/01/02 21:13:06  southa
 * Source conditioning
 *
 * Revision 1.10  2003/09/17 19:40:30  southa
 * Source conditioning upgrades
 *
 * Revision 1.9  2003/08/21 23:08:30  southa
 * Fixed file headers
 *
 * Revision 1.8  2003/01/13 14:31:55  southa
 * Build frameworks for Mac OS X
 *
 * Revision 1.7  2003/01/12 17:32:51  southa
 * Mushcore work
 *
 * Revision 1.6  2002/12/29 20:59:53  southa
 * More build fixes
 *
 * Revision 1.5  2002/12/20 13:17:36  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.4  2002/10/22 20:42:01  southa
 * Source conditioning
 *
 * Revision 1.3  2002/08/27 08:56:20  southa
 * Source conditioning
 *
 * Revision 1.2  2002/08/07 13:36:47  southa
 * Conditioned source
 *
 * Revision 1.1  2002/07/19 15:44:39  southa
 * Graphic optimisations
 *
 */

#include "GLTextureDef.h"

#include "GLSTL.h"

using namespace Mushware;
using namespace std;

bool
GLTextureDef::NeedsAlpha(void) const
{
    if (!m_needsAlphaValid)
    {
        DetermineNeedsAlpha();
    }
    return m_needsAlpha;
}

void
GLTextureDef::DetermineNeedsAlpha(void) const
{
    U8 *dataPtr=reinterpret_cast<U8 *>(m_dataPtr);
    U32 dataSize=m_width*m_height; // Number of pixels to check
    
    MUSHCOREASSERT(dataPtr != NULL || dataSize == 0);

    m_needsAlpha=false;
    dataPtr += 3; // Advance to first alpha byte
    for (U32 i=0; i<dataSize; ++i)
    {
        if (*dataPtr != 255)
        {
            m_needsAlpha = true;
            break;
        }
        dataPtr+=4;
    }
    m_needsAlphaValid=true;
}
