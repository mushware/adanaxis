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
 * $Id: GameMotionSpec.cpp,v 1.8 2002/10/17 16:41:21 southa Exp $
 * $Log: GameMotionSpec.cpp,v $
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
 * Added GameMotion
 *
 * Revision 1.1  2002/07/18 11:40:35  southa
 * Overplotting and movement
 *
 */

#include "GameMotionSpec.h"
#include "GameData.h"
#include "GameView.h"

GameMotionSpec::GameMotionSpec(const GLPoint& inPoint, tVal inAngle) :
    pos(inPoint),
    angle(inAngle),
    shape(GLRectangle(0,0,0,0)),
    deltaPos(GLPoint(0,0)),
    deltaAngle(0)
{
}

void
GameMotionSpec::ZeroSet(void)
{
    pos=GLPoint(0,0);
    angle=0;
    shape=GLRectangle(0,0,0,0);
    deltaPos=GLPoint(0,0);
    deltaAngle=0;
}

void
GameMotionSpec::Windback(tVal inScale)
{
    pos -= deltaPos * inScale;
    angle -= deltaAngle * inScale;
}

const GameMotionSpec
GameMotionSpec::WindbackGet(tVal inScale) const
{
    GameMotionSpec retSpec(*this);
    retSpec.Windback(inScale);
    return retSpec;
}

void
GameMotionSpec::ApplyDelta(void)
{
    pos += deltaPos;
    angle += deltaAngle;
}

void
GameMotionSpec::Render(void) const
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
    GameData::Instance().CurrentViewGet()->OverPlotGet().
        RenderableAdd(quad, GLColour(0,0,1));
    GameData::Instance().CurrentViewGet()->OverPlotGet().
        RenderableAdd(newQuad, GLColour(0,1,1));

    GLPoint angleVec(deltaAngle,0);
    angleVec.RotateAboutZ(newAngle);
    GameData::Instance().CurrentViewGet()->OverPlotGet().
        RenderableAdd(GLLine(newPos+deltaPos*10, newPos+deltaPos*10+angleVec*10),
                      GLColour(1,0,0));

    GameData::Instance().CurrentViewGet()->OverPlotGet().
        RenderableAdd(GLLine(newPos, newPos+deltaPos*10), GLColour(1,1,0));
}
