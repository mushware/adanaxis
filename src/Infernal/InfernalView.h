//%includeGuardStart {
#ifndef INFERNALVIEW_H
#define INFERNALVIEW_H
//%includeGuardStart } aCH3kmt0EIOJSEZnfInxWQ
//%Header {
/*****************************************************************************
 *
 * File: src/Game/InfernalView.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } jRXzYzTMHDfmSWVEeGNYcw
/*
 * $Id: InfernalView.h,v 1.10 2003/09/17 19:40:34 southa Exp $
 * $Log: InfernalView.h,v $
 * Revision 1.10  2003/09/17 19:40:34  southa
 * Source conditioning upgrades
 *
 * Revision 1.9  2003/08/21 23:08:59  southa
 * Fixed file headers
 *
 * Revision 1.8  2003/01/11 13:03:15  southa
 * Use Mushcore header
 *
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

#include "InfernalOverPlot.h"

class InfernalView
{
public:
    InfernalView();
    const GLRectangle& DimensionsGet(void) const { return m_dimensions; }
    Mushware::tVal WidthGet(void) const { return m_dimensions.XSize(); }
    Mushware::tVal HeightGet(void) const { return m_dimensions.YSize(); }
    void RectangleSet(const GLRectangle& inRectangle) { m_dimensions=inRectangle; }
    InfernalOverPlot& OverPlotGet(void) { return m_overPlot; }
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
    InfernalOverPlot m_overPlot;
    Mushware::tVal m_lightingFactor;
    Mushware::tVal m_ambientLighting;
    GLVector m_cameraPos;
    GLVector m_lookAtPos;
    Mushware::tVal m_cameraAngle;
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
