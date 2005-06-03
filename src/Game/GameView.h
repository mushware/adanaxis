#ifndef GAMEVIEW_H
#define GAMEVIEW_H
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
 * $Id: GameView.h,v 1.7 2002/12/20 13:17:44 southa Exp $
 * $Log: GameView.h,v $
 * Revision 1.7  2002/12/20 13:17:44  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.6  2002/12/03 20:28:17  southa
 * Network, player and control work
 *
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

#include "Mushcore.h"
#include "mushGL.h"

#include "GameOverPlot.h"

class GameView
{
public:
    GameView();
    const GLRectangle& DimensionsGet(void) const { return m_dimensions; }
    Mushware::tVal WidthGet(void) const { return m_dimensions.XSize(); }
    Mushware::tVal HeightGet(void) const { return m_dimensions.YSize(); }
    void RectangleSet(const GLRectangle& inRectangle) { m_dimensions=inRectangle; }
    GameOverPlot& OverPlotGet(void) { return m_overPlot; }
    Mushware::tVal LightingFactorGet(void) { return m_lightingFactor; }
    void LightingFactorSet(Mushware::tVal inFactor) { m_lightingFactor = inFactor; }
    Mushware::tVal AmbientLightingGet(void) { return m_ambientLighting; }
    void AmbientLightingSet(Mushware::tVal inAmbient) { m_ambientLighting = inAmbient; }
    const GLVector& CameraPosGet(void) const { return m_cameraPos; }
    const GLVector& LookAtPosGet(void) const { return m_lookAtPos; }
    Mushware::tVal CameraAngleGet(void) const { return m_cameraAngle; }
    void MoveCameraToPlayer(const GLVector& inPos, Mushware::tVal inAngle);
    
private:
    GLRectangle m_dimensions;
    GameOverPlot m_overPlot;
    Mushware::tVal m_lightingFactor;
    Mushware::tVal m_ambientLighting;
    GLVector m_cameraPos;
    GLVector m_lookAtPos;
    Mushware::tVal m_cameraAngle;
};
#endif
