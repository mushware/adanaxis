/*
 * $Id: GameSolidMap.cpp,v 1.5 2002/07/31 16:27:16 southa Exp $
 * $Log: GameSolidMap.cpp,v $
 * Revision 1.5  2002/07/31 16:27:16  southa
 * Collision checking work
 *
 * Revision 1.4  2002/07/23 14:10:47  southa
 * Added GameMotion
 *
 * Revision 1.3  2002/07/19 17:51:11  southa
 * Texture tweaks
 *
 * Revision 1.2  2002/07/16 19:30:09  southa
 * Simplistic collision checking
 *
 * Revision 1.1  2002/07/16 17:48:08  southa
 * Collision and optimisation work
 *
 */

#include "GameSolidMap.h"

#include "mushGL.h"

#include "GameData.h"
#include "GameView.h"
#include "GameMapArea.h"
#include "GameMotionSpec.h"
#include "GameMapPoint.h"
#include "GameSpacePoint.h"

GameSolidMap::GameSolidMap():
    m_xsize(0),
    m_ysize(0),
    m_xstep(1),
    m_ystep(1)
{
}

void
GameSolidMap::SizeSet(U32 inXSize, U32 inYSize)
{
    m_xsize=inXSize;
    m_ysize=inYSize;
    m_solidMap.resize(0);
    m_solidMap.resize(m_xsize*m_ysize);
}

void
GameSolidMap::StepSet(tVal inXStep, tVal inYStep)
{
    m_xstep=inXStep;
    m_ystep=inYStep;
}

const GameMapPoint
GameSolidMap::SpaceToMapFractional(const GameSpacePoint inPoint) const
{
    GameMapPoint retVal(inPoint / GLPoint(m_xstep, m_ystep));
    return retVal;
}

const GameMapPoint
GameSolidMap::SpaceToMap(const GameSpacePoint inPoint) const
{
    GameMapPoint retVal(inPoint / GLPoint(m_xstep, m_ystep));
    retVal += GLPoint(0.5,0.5);
    retVal.MakeInteger();
    return retVal;
}

const GameSpacePoint
GameSolidMap::MapToSpace(const GameMapPoint inPoint) const
{
    return GameSpacePoint(inPoint * GLPoint(m_xstep, m_ystep));
}

void
GameSolidMap::PermeabilitySet(tVal inValue, U32 inX, U32 inY)
{
    COREASSERT(inX < m_xsize);
    COREASSERT(inY < m_ysize);
    m_solidMap[m_xsize * inY + inX] = inValue;
}

tVal
GameSolidMap::PermeabilityGet(U32 inX, U32 inY) const
{
    COREASSERT(inX < m_xsize);
    COREASSERT(inY < m_ysize);
    return m_solidMap[m_xsize * inY + inX];
}

tVal
GameSolidMap::PermeabilityGet(const GameSpacePoint& inPoint) const
{
    GameMapPoint mapPoint(SpaceToMap(inPoint));
    return PermeabilityGet(mapPoint);
}

tVal
GameSolidMap::PermeabilityGet(const GameMapPoint& inPoint) const
{
    // Permeability is always 0 outside of the map
    if (inPoint.x < 0 || inPoint.y < 0) return 0;
    U32 x=static_cast<U32>(inPoint.x+0.5);
    U32 y=static_cast<U32>(inPoint.y+0.5);
    if (x >= m_xsize || y>= m_ysize) return 0;
    return m_solidMap[m_xsize * y + x];
}

void
GameSolidMap::TrimMotion(GameMotionSpec& inSpec) const
{
    tCollisionSet colSet;
    CollisionSetAdd(colSet, inSpec);
    for (U32 i=0; i<colSet.size(); ++i)
    {
        if (PermeabilityGet(colSet[i]) == 0)
        {
            inSpec.deltaPos=GLPoint(0,0);
            inSpec.deltaAngle=0;
        }
    }
}

void
GameSolidMap::OverPlotCollisionSet(const GameMotionSpec& inSpec) const
{
    tCollisionSet colSet;
    CollisionSetAdd(colSet, inSpec);
    for (U32 i=0; i<colSet.size(); ++i)
    {
        OverPlotBox(colSet[i]);
    }
}

void
GameSolidMap::OverPlotBox(const GameMapPoint& inPoint) const
{
    GameSpacePoint spacePoint(MapToSpace(inPoint));

    GLPoint rectOffset(m_xstep/2 - 1, m_ystep/2 - 1);
    
    GLRectangle rect(spacePoint-rectOffset,
                     spacePoint+rectOffset);

    GameData::Instance().CurrentViewGet()->OverPlotGet().
        RenderableAdd(rect, GLColour(1,0.5,0));
}

void
GameSolidMap::CollisionSetAdd(tCollisionSet& outSet, const GameMotionSpec& inSpec) const
{
    // GameSpacePoint spacePoint(inSpec.pos+inSpec.deltaPos);
    // GameMapPoint mapPoint(SpaceToMap(spacePoint));

    // Get the projection of the MotionSpec rectangle in GameSpace into newQuad
    GLQuad newQuad(inSpec.shape);
    GLPoint newPos = inSpec.pos+inSpec.deltaPos;
    tVal newAngle = inSpec.angle+inSpec.deltaAngle;
    newQuad.RotateAboutCentre(newAngle);
    newQuad += newPos;

    // Translate the quad to map space
    GLQuad mapQuad;
    for (U32 i=0; i<4; ++i)
    {
        mapQuad.PointSet(i, SpaceToMapFractional(GameSpacePoint(newQuad.PointGet(i))));
    }
    
    // Find the map area which encloses newQuad
    GLRectangle mapRect;
    mapQuad.BoundingRectangleGet(mapRect);
    mapRect+=GLPoint(0.5,0.5);
    mapRect.MakeInteger();
    mapRect.Clip(GLRectangle(0, 0, m_xsize-1, m_ysize-1));
    GameMapPoint mapPoint;
    for (mapPoint.x=mapRect.xmin; mapPoint.x<=mapRect.xmax; ++mapPoint.x)
    {
        for (mapPoint.y=mapRect.ymin; mapPoint.y<=mapRect.ymax; ++mapPoint.y)
        {
            // Map position x,y is a potential collision set member
            if (CollisionElementCheck(mapPoint, mapQuad))
            {
                outSet.push_back(mapPoint);
            }
        }
    }
}

bool
GameSolidMap::CollisionElementCheck(const GameMapPoint& inPoint, const GLQuad& inQuad) const
{
    for (U32 i=0; i<4; ++i)
    {
        // if (inQuad.PointGet(i) == inPoint) return true;
    }

    // Build set of test lines and test rectangle
    GLRectangle mapRect(inPoint-GLPoint(0.5, 0.5), inPoint+GLPoint(0.5, 0.5));

    for (U32 i=0; i<4; ++i)
    {
        if (mapRect.IsIntersecting(
               GLLine(inQuad.PointGet(i),
                      inQuad.PointGet((i+1) % 4)
                      )
                                   )
            ) return true;
    }
    
    return false;
}

void
GameSolidMap::Render(const GameMapArea& inArea) const
{
    GLUtils gl;
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    gl.SetPosition(0,0);
    GLUtils::Scale(m_xstep, m_ystep, 1);
    GLPoint minPoint=inArea.MinPointGet();
    GLPoint maxPoint=inArea.MaxPointGet();

    GLRectangle wholeMap(0, 0, m_xsize, m_ysize);
    wholeMap.ConstrainPoint(minPoint);
    wholeMap.ConstrainPoint(maxPoint);

    minPoint.MakeInteger();
    maxPoint.MakeInteger();

    GLPoint point;
    GLUtils::BlendSet(GLUtils::kBlendLine);

    for (point.x=minPoint.x; point.x<maxPoint.x; ++point.x)
    {
        for (point.y=minPoint.y; point.y<maxPoint.y; ++point.y)
        {
            if (inArea.IsWithin(point))
            {
                tVal perm=PermeabilityGet(point.U32XGet(), point.U32YGet());
                GLUtils::ColourSet(0.5+0.5*cos(perm*M_PI),
                                   0.5-0.5*cos(perm*M_PI),
                                   (perm>1)?1:0);
                GLLine line((point-GLPoint(0.4, 0.4)),
                            (point+GLPoint(0.4, 0.4)));

                line.Render();
                line.RotateAboutCentre(M_PI/2);
                line.Render();
            }
        }
    }
    glPopMatrix();
}
