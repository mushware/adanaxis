//%Header {
/*****************************************************************************
 *
 * File: src/Infernal/InfernalView.cpp
 *
 * Copyright: Andy Southgate 2002-2007, 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/
//%Header } k3JNBVenroYs3yZDOKCp8A
/*
 * $Id: InfernalView.cpp,v 1.5 2006/06/01 15:39:09 southa Exp $
 * $Log: InfernalView.cpp,v $
 * Revision 1.5  2006/06/01 15:39:09  southa
 * DrawArray verification and fixes
 *
 * Revision 1.4  2005/05/19 13:02:06  southa
 * Mac release work
 *
 * Revision 1.3  2004/01/02 21:13:09  southa
 * Source conditioning
 *
 * Revision 1.2  2003/10/04 15:32:12  southa
 * Module split
 *
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
