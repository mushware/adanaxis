/*
 * $Id: GameMotionSpec.cpp,v 1.2 2002/07/23 14:10:47 southa Exp $
 * $Log: GameMotionSpec.cpp,v $
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

GameMotionSpec::GameMotionSpec() :
    pos(GLPoint(0,0)),
    angle(0),
    shape(GLRectangle(0,0,0,0)),
    deltaPos(GLPoint(0,0)),
    deltaAngle(0)
{
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
        RenderableAdd(GLLine(newPos+deltaPos*10, newPos+deltaPos*10+angleVec*10), GLColour(1,0,0));


    GameData::Instance().CurrentViewGet()->OverPlotGet().
        RenderableAdd(GLLine(newPos, newPos+deltaPos*10), GLColour(1,1,0));
}
