#ifndef GAMEVIEW_H
#define GAMEVIEW_H
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
 * $Id: GameView.h,v 1.5 2002/10/22 20:42:07 southa Exp $
 * $Log: GameView.h,v $
 * Revision 1.5  2002/10/22 20:42:07  southa
 * Source conditioning
 *
 * Revision 1.4  2002/10/08 11:58:53  southa
 * Light cache
 *
 * Revision 1.3  2002/08/27 08:56:28  southa
 * Source conditioning
 *
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
    GameView();
    const GLRectangle& DimensionsGet(void) const { return m_dimensions; }
    tVal WidthGet(void) const { return m_dimensions.XSize(); }
    tVal HeightGet(void) const { return m_dimensions.YSize(); }
    void RectangleSet(const GLRectangle& inRectangle) { m_dimensions=inRectangle; }
    GameOverPlot& OverPlotGet(void) { return m_overPlot; }
    tVal LightingFactorGet(void) { return m_lightingFactor; }
    void LightingFactorSet(tVal inFactor) { m_lightingFactor = inFactor; }
    tVal AmbientLightingGet(void) { return m_ambientLighting; }
    void AmbientLightingSet(tVal inAmbient) { m_ambientLighting = inAmbient; }
    const GLVector& CameraPosGet(void) const { return m_cameraPos; }
    const GLVector& LookAtPosGet(void) const { return m_lookAtPos; }
    tVal CameraAngleGet(void) const { return m_cameraAngle; }
    void MoveCameraToPlayer(const GLVector& inPos, tVal inAngle);
    
private:
    GLRectangle m_dimensions;
    GameOverPlot m_overPlot;
    tVal m_lightingFactor;
    tVal m_ambientLighting;
    GLVector m_cameraPos;
    GLVector m_lookAtPos;
    tVal m_cameraAngle;
};
#endif
