/*
 * $Id$
 * $Log$
 */

#include "mushCore.h"
#include "mushGL.h"

class GameOverPlot
{
public:
    GameOverPlot() : m_numRenderables(0) {}
    ~GameOverPlot() { Clear(); }
    void RenderableAdd(const GLRenderable& inRenderable, const GLColour& inColour);
    void Render(void) const;
    void Clear(void);

private:
    U32 m_numRenderables;
    vector<GLRenderable *> m_renderables;
    vector<GLColour> m_colours;
};
