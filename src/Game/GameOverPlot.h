#ifndef GAMEOVERPLOT_H
#define GAMEOVERPLOT_H
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
 * $Id: GameOverPlot.h,v 1.6 2003/01/11 13:03:14 southa Exp $
 * $Log: GameOverPlot.h,v $
 * Revision 1.6  2003/01/11 13:03:14  southa
 * Use Mushcore header
 *
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
