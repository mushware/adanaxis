/*****************************************************************************
 *
 * (Mushware file header version 1.0)
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.co.uk.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/


/*
 * $Id: GameOverPlot.cpp,v 1.2 2002/08/07 13:36:50 southa Exp $
 * $Log: GameOverPlot.cpp,v $
 * Revision 1.2  2002/08/07 13:36:50  southa
 * Conditioned source
 *
 * Revision 1.1  2002/07/18 11:40:35  southa
 * Overplotting and movement
 *
 */

#include "GameOverPlot.h"

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
