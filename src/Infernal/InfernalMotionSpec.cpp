//%Header {
/*****************************************************************************
 *
 * File: src/Infernal/InfernalMotionSpec.cpp
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
//%Header } wAPOM9/pmtDWUShQil/BnQ
/*
 * $Id: InfernalMotionSpec.cpp,v 1.6 2006/06/01 15:39:04 southa Exp $
 * $Log: InfernalMotionSpec.cpp,v $
 * Revision 1.6  2006/06/01 15:39:04  southa
 * DrawArray verification and fixes
 *
 * Revision 1.5  2005/05/19 13:02:05  southa
 * Mac release work
 *
 * Revision 1.4  2004/01/02 21:13:08  southa
 * Source conditioning
 *
 * Revision 1.3  2003/10/04 15:32:11  southa
 * Module split
 *
 * Revision 1.2  2003/10/04 12:44:35  southa
 * File renaming
 *
 * Revision 1.1  2003/10/04 12:23:06  southa
 * File renaming
 *
 * Revision 1.15  2003/09/17 19:40:32  southa
 * Source conditioning upgrades
 *
 * Revision 1.14  2003/08/21 23:08:49  southa
 * Fixed file headers
 *
 * Revision 1.13  2003/01/20 10:45:26  southa
 * Singleton tidying
 *
 * Revision 1.12  2003/01/13 14:31:59  southa
 * Build frameworks for Mac OS X
 *
 * Revision 1.11  2002/12/29 20:59:56  southa
 * More build fixes
 *
 * Revision 1.10  2002/12/20 13:17:41  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.9  2002/10/22 20:42:05  southa
 * Source conditioning
 *
 * Revision 1.8  2002/10/17 16:41:21  southa
 * Initialisation fix and player facet
 *
 * Revision 1.7  2002/08/27 08:56:24  southa
 * Source conditioning
 *
 * Revision 1.6  2002/08/09 17:09:04  southa
 * InfernalDialogue added
 *
 * Revision 1.5  2002/08/07 13:36:50  southa
 * Conditioned source
 *
 * Revision 1.4  2002/08/05 13:37:28  southa
 * Windback work
 *
 * Revision 1.3  2002/07/31 16:27:16  southa
 * Collision checking work
 *
 * Revision 1.2  2002/07/23 14:10:47  southa
 * Added InfernalMotion
 *
 * Revision 1.1  2002/07/18 11:40:35  southa
 * Overplotting and movement
 *
 */

#include "InfernalMotionSpec.h"

#include "InfernalData.h"
#include "InfernalSTL.h"
#include "InfernalView.h"

using namespace Mushware;
using namespace std;

InfernalMotionSpec::InfernalMotionSpec(const GLPoint& inPoint, tVal inAngle) :
    pos(inPoint),
    angle(inAngle),
    shape(GLRectangle(0,0,0,0)),
    deltaPos(GLPoint(0,0)),
    deltaAngle(0)
{
}

void
InfernalMotionSpec::ZeroSet(void)
{
    pos=GLPoint(0,0);
    angle=0;
    shape=GLRectangle(0,0,0,0);
    deltaPos=GLPoint(0,0);
    deltaAngle=0;
}

void
InfernalMotionSpec::Windback(tVal inScale)
{
    pos -= deltaPos * inScale;
    angle -= deltaAngle * inScale;
}

const InfernalMotionSpec
InfernalMotionSpec::WindbackGet(tVal inScale) const
{
    InfernalMotionSpec retSpec(*this);
    retSpec.Windback(inScale);
    return retSpec;
}

void
InfernalMotionSpec::ApplyDelta(void)
{
    pos += deltaPos;
    angle += deltaAngle;
}

void
InfernalMotionSpec::Render(void) const
{
    // Draw collision rectangle
    GLQuad quad(shape);
    GLQuad newQuad(shape);
    GLPoint newPos = pos+deltaPos;
    tVal newAngle=angle+deltaAngle;

    quad.RotateAboutCentre(angle);
    newQuad.RotateAboutCentre(newAngle);

    quad += pos;
    newQuad += newPos;

    // Draw old and new quads
    InfernalData::Sgl().CurrentViewGet()->OverPlotGet().
        RenderableAdd(quad, GLColour(0,0,1));
    InfernalData::Sgl().CurrentViewGet()->OverPlotGet().
        RenderableAdd(newQuad, GLColour(0,1,1));

    GLPoint angleVec(deltaAngle,0);
    angleVec.RotateAboutZ(newAngle);
    InfernalData::Sgl().CurrentViewGet()->OverPlotGet().
        RenderableAdd(GLLine(newPos+deltaPos*10, newPos+deltaPos*10+angleVec*10),
                      GLColour(1,0,0));

    InfernalData::Sgl().CurrentViewGet()->OverPlotGet().
        RenderableAdd(GLLine(newPos, newPos+deltaPos*10), GLColour(1,1,0));
}
