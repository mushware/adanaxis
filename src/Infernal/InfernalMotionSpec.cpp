//%Header {
/*****************************************************************************
 *
 * File: src/Infernal/InfernalMotionSpec.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } pe6CzTneXBLw8Z1Xny0oUQ
/*
 * $Id: InfernalMotionSpec.cpp,v 1.1 2003/10/04 12:23:06 southa Exp $
 * $Log: InfernalMotionSpec.cpp,v $
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
 * GameDialogue added
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
#include "GameSTL.h"
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
