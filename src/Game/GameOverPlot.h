#ifndef GAMEOVERPLOT_H
#define GAMEOVERPLOT_H
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
 * $Id: GameOverPlot.h,v 1.5 2002/12/20 13:17:41 southa Exp $
 * $Log: GameOverPlot.h,v $
 * Revision 1.5  2002/12/20 13:17:41  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.4  2002/10/22 20:42:05  southa
 * Source conditioning
 *
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

#include "Mushcore.h"
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
    Mushware::U32 m_numRenderables;
    std::vector<GLRenderable *> m_renderables;
    std::vector<GLColour> m_colours;
};
#endif
