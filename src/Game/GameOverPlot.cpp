/*****************************************************************************
 *
 * (Mushware file header version 1.3)
 *
 * Copyrighted work by Andy Southgate 2003
 *
 * This file may be redistributed and/or modified under the terms of the
 * Mushware licence which you should have received with this file.  For
 * information, please contact the author via http://www.mushware.com/.
 *
 ****************************************************************************/

/*
 * $Id: GameOverPlot.cpp,v 1.8 2003/01/13 14:31:59 southa Exp $
 * $Log: GameOverPlot.cpp,v $
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

#include "GameOverPlot.h"

#include "GameSTL.h"

using namespace Mushware;
using namespace std;

void
GameOverPlot::RenderableAdd(const GLRenderable& inRenderable, const GLColour& inColour)
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
GameOverPlot::Render(void) const
{
    for (U32 i=0; i<m_numRenderables; ++i)
    {
        m_colours[i].Apply();
        m_renderables[i]->Render();
    }
}

void
GameOverPlot::Clear(void)
{
    for (U32 i=0; i<m_numRenderables; ++i)
    {
        delete m_renderables[i];
    }
    m_numRenderables=0;
}
