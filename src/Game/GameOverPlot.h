#ifndef GAMEOVERPLOT_H
#define GAMEOVERPLOT_H
/*****************************************************************************
 *
 * (Mushware file header version 1.1)
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/

/*
 * $Id: GameOverPlot.h,v 1.3 2002/08/27 08:56:25 southa Exp $
 * $Log: GameOverPlot.h,v $
 * Revision 1.3  2002/08/27 08:56:25  southa
 * Source conditioning
 *
 * Revision 1.2  2002/08/07 13:36:50  southa
 * Conditioned source
 *
 * Revision 1.1  2002/07/18 11:40:35  southa
 * Overplotting and movement
 *
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
#endif
