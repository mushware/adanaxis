/*
 * $Id$
 * $Log$
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
