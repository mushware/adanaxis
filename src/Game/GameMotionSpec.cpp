/*
 * $Id: GameMotionSpec.cpp,v 1.1 2002/07/18 11:40:35 southa Exp $
 * $Log: GameMotionSpec.cpp,v $
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

    GameData::Instance().CurrentViewGet()->OverPlotGet().
        RenderableAdd(quad, GLColour(0,0,1));
    GameData::Instance().CurrentViewGet()->OverPlotGet().
        RenderableAdd(newQuad, GLColour(0,1,1));

    GLPoint angleVec(deltaAngle,0);
    angleVec.RotateAboutZ(angle);
    // Add deltaPos + deltaAngle
    GameData::Instance().CurrentViewGet()->OverPlotGet().
        RenderableAdd(GLLine(newPos, newPos+angleVec*10), GLColour(1,0,0));

    // Add deltaPos
    GameData::Instance().CurrentViewGet()->OverPlotGet().
        RenderableAdd(GLLine(newPos, newPos+deltaPos*10), GLColour(1,1,0));
}
