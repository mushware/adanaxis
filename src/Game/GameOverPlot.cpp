/*
 * $Id$
 * $Log$
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
