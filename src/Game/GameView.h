#ifndef GAMEVIEW_H
#define GAMEVIEW_H
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
 * $Id: GameView.h,v 1.2 2002/08/07 13:36:51 southa Exp $
 * $Log: GameView.h,v $
 * Revision 1.2  2002/08/07 13:36:51  southa
 * Conditioned source
 *
 * Revision 1.1  2002/07/18 11:49:28  southa
 * Created
 *
 */

#include "mushCore.h"
#include "mushGL.h"
#include "GameOverPlot.h"

class GameView
{
public:
    GameView() : m_dimensions(GLRectangle(0,0,0,0)) {}
    const GLRectangle& DimensionsGet(void) const { return m_dimensions; }
    tVal WidthGet(void) const { return m_dimensions.XSize(); }
    tVal HeightGet(void) const { return m_dimensions.YSize(); }
    void RectangleSet(const GLRectangle& inRectangle) { m_dimensions=inRectangle; }
    GameOverPlot& OverPlotGet(void) { return m_overPlot; }
    
private:
    GLRectangle m_dimensions;
    GameOverPlot m_overPlot;
};
#endif
