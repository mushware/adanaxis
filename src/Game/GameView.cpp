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
 * $Id: GameView.cpp,v 1.5 2002/10/22 20:42:07 southa Exp $
 * $Log: GameView.cpp,v $
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

#include "GameView.h"

GameView::GameView():
    m_dimensions(GLRectangle(0,0,0,0)),
    m_lightingFactor(1.0),
    m_ambientLighting(0.3),
    m_cameraPos(GLVector(0,0,1)),
    m_lookAtPos(GLVector(0,0,0)),
    m_cameraAngle(0)
{
    m_cameraPos.z = GLUtils::EyeDistanceGet();
}

void
GameView::MoveCameraToPlayer(const GLVector& inPos, tVal inAngle)
{
    m_cameraPos = inPos;
    m_cameraPos.z = GLUtils::EyeDistanceGet();

    m_lookAtPos = inPos;
    m_cameraAngle = inAngle;
}
