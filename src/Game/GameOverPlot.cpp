/*****************************************************************************
 *
 * (Mushware file header version 1.2)
 *
 * This file contains original work by Andy Southgate.
 * Copyright Andy Southgate 2002.  All rights reserved.
 * Contact details can be found at http://www.mushware.com/
 *
 ****************************************************************************/

/*
 * $Id: GameOverPlot.cpp,v 1.4 2002/10/22 20:42:05 southa Exp $
 * $Log: GameOverPlot.cpp,v $
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

using namespace Mushware;

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

    COREASSERT(m_numRenderables < m_renderables.size());
    COREASSERT(m_numRenderables < m_colours.size());
    
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
