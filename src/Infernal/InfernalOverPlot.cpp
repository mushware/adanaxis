//%Header {
/*****************************************************************************
 *
 * File: src/Game/InfernalOverPlot.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } anJr/qj1j1c9NVL9xUFAqw
/*
 * $Id: InfernalOverPlot.cpp,v 1.10 2003/09/17 19:40:32 southa Exp $
 * $Log: InfernalOverPlot.cpp,v $
 * Revision 1.10  2003/09/17 19:40:32  southa
 * Source conditioning upgrades
 *
 * Revision 1.9  2003/08/21 23:08:50  southa
 * Fixed file headers
 *
 * Revision 1.8  2003/01/13 14:31:59  southa
 * Build frameworks for Mac OS X
 *
 * Revision 1.7  2003/01/12 17:32:55  southa
 * Mushcore work
 *
 * Revision 1.6  2002/12/29 20:59:56  southa
 * More build fixes
 *
 * Revision 1.5  2002/12/20 13:17:41  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.4  2002/10/22 20:42:05  southa
 * Source conditioning
 *
 * Revision 1.3  2002/08/27 08:56:24  southa
 * Source conditioning
 *
 * Revision 1.2  2002/08/07 13:36:50  southa
 * Conditioned source
 *
 * Revision 1.1  2002/07/18 11:40:35  southa
 * Overplotting and movement
 *
 */

#include "InfernalOverPlot.h"

#include "GameSTL.h"

using namespace Mushware;
using namespace std;

void
InfernalOverPlot::RenderableAdd(const GLRenderable& inRenderable, const GLColour& inColour)
{
    if (m_numRenderables >= m_renderables.size())
    {
        m_renderables.resize(m_numRenderables+32);
    }

    if (m_numRenderables >= m_colours.size())
    {
        m_colours.resize(m_numRenderables+32);
    }

    MUSHCOREASSERT(m_numRenderables < m_renderables.size());
    MUSHCOREASSERT(m_numRenderables < m_colours.size());
    
    m_renderables[m_numRenderables]=inRenderable.Clone();
    m_colours[m_numRenderables]=inColour;
    ++m_numRenderables;
}

void
InfernalOverPlot::Render(void) const
{
    for (U32 i=0; i<m_numRenderables; ++i)
    {
        m_colours[i].Apply();
        m_renderables[i]->Render();
    }
}

void
InfernalOverPlot::Clear(void)
{
    for (U32 i=0; i<m_numRenderables; ++i)
    {
        delete m_renderables[i];
    }
    m_numRenderables=0;
}
