//%Header {
/*****************************************************************************
 *
 * File: src/Infernal/InfernalView.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } cmMabNhtshruG70urNt8JA
/*
 * $Id: InfernalView.cpp,v 1.1 2003/10/04 12:23:07 southa Exp $
 * $Log: InfernalView.cpp,v $
 * Revision 1.1  2003/10/04 12:23:07  southa
 * File renaming
 *
 * Revision 1.11  2003/09/17 19:40:34  southa
 * Source conditioning upgrades
 *
 * Revision 1.10  2003/08/21 23:08:59  southa
 * Fixed file headers
 *
 * Revision 1.9  2003/01/13 14:32:01  southa
 * Build frameworks for Mac OS X
 *
 * Revision 1.8  2002/12/29 20:59:58  southa
 * More build fixes
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

#include "InfernalView.h"

#include "InfernalSTL.h"

using namespace Mushware;
using namespace std;

InfernalView::InfernalView():
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
InfernalView::MoveCameraToPlayer(const GLVector& inPos, tVal inAngle)
{
    m_cameraPos = inPos;
    m_cameraPos.z = GLUtils::EyeDistanceGet();

    m_lookAtPos = inPos;
    m_cameraAngle = inAngle;
}
