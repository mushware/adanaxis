/*****************************************************************************
 *
 * (Mushware file header version 1.0)
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.co.uk.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/

/*
 * $Id: GameSolidMap.cpp,v 1.21 2002/08/18 12:20:41 southa Exp $
 * $Log: GameSolidMap.cpp,v $
 * Revision 1.21  2002/08/18 12:20:41  southa
 * Movement tweaks
 *
 * Revision 1.20  2002/08/09 17:09:04  southa
 * GameDialogue added
 *
 * Revision 1.19  2002/08/08 18:42:05  southa
 * More motion escape tweaks
 *
 * Revision 1.18  2002/08/08 18:38:16  southa
 * More motion escape tweaks
 *
 * Revision 1.17  2002/08/08 18:33:45  southa
 * Motion escape tweaks
 *
 * Revision 1.16  2002/08/08 18:32:27  southa
 * Corrected for new scaling
 *
 * Revision 1.15  2002/08/08 18:20:30  southa
 * Plot on screen of dimension 1.0
 *
 * Revision 1.14  2002/08/07 13:36:50  southa
 * Conditioned source
 *
 * Revision 1.13  2002/08/05 16:14:18  southa
 * Windback at low frame rates
 *
 * Revision 1.12  2002/08/02 12:56:40  southa
 * Working collision checking
 *
 * Revision 1.11  2002/08/02 11:00:44  southa
 * Tweaked motion trimming
 *
 * Revision 1.10  2002/08/02 10:02:28  southa
 * Added more angle tweaks
 *
 * Revision 1.9  2002/08/02 09:56:04  southa
 * Added angle tweaks
 *
 * Revision 1.8  2002/08/02 09:47:37  southa
 * Added corner escapes
 *
 * Revision 1.7  2002/08/02 09:05:10  southa
 * Movement modification in collison checking
 *
 * Revision 1.6  2002/08/01 16:47:12  southa
 * First multi-box collsion checking
 *
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
GameSolidMap::AdhesionSet(tVal inValue, U32 inX, U32 inY)
{
    COREASSERT(inX < m_xsize);
    COREASSERT(inY < m_ysize);
    m_adhesionMap[m_xsize * inY + inX] = inValue;
}

tVal
GameSolidMap::AdhesionGet(const GameSpacePoint& inPoint) const
{
    GameMapPoint mapPoint(SpaceToMap(inPoint));
    return PermeabilityGet(mapPoint);
}

tVal
GameSolidMap::AdhesionGet(const GameMapPoint& inPoint) const
{
    // Permeability is always 0 outside of the map
    if (inPoint.x < 0 || inPoint.y < 0) return 1.0;
    U32 x=static_cast<U32>(inPoint.x+0.5);
    U32 y=static_cast<U32>(inPoint.y+0.5);
    if (x >= m_xsize || y>= m_ysize) return 1.0;
    return m_adhesionMap[m_xsize * y + x];
}

void
GameSolidMap::TrimMotion(GameMotionSpec& inSpec) const
{
    tVal perm;
    GameMotionSpec trialSpec;
    bool deltaAngleSignificant = (fabs(inSpec.deltaAngle) > 0.005);
    trialSpec=inSpec;
    perm=MotionSpecPermeabilityGet(trialSpec);

    if (perm <= 0)
    {
        trialSpec=inSpec;
        trialSpec.deltaPos.x=0;
        perm=MotionSpecPermeabilityGet(trialSpec);
    }

    if (perm <= 0)
    {
        trialSpec=inSpec;
        trialSpec.deltaPos.y=0;
        perm=MotionSpecPermeabilityGet(trialSpec);
    }
    
    // Try minor tweaks first
    for (tVal delta=0.01; delta<=0.06; delta *= 2)
    {
        if (perm <= 0)
        {
            trialSpec=inSpec;
            trialSpec.deltaPos.x-=delta;
            perm=MotionSpecPermeabilityGet(trialSpec);
        }
        if (perm <= 0)
        {
            trialSpec=inSpec;
            trialSpec.deltaPos.x+=delta;
            perm=MotionSpecPermeabilityGet(trialSpec);
        }
        if (perm <= 0)
        {
            trialSpec=inSpec;
            trialSpec.deltaPos.y-=delta;
            perm=MotionSpecPermeabilityGet(trialSpec);
        }
        if (perm <= 0)
        {
            trialSpec=inSpec;
            trialSpec.deltaPos.y+=delta;
            perm=MotionSpecPermeabilityGet(trialSpec);
        }
    }
    
    if (perm <= 0 && inSpec.deltaPos.Magnitude() > 0.01 && !deltaAngleSignificant)
    {
	// Check that the player is trying to move sideways
        GLPoint bounds(inSpec.shape.Size());
 	GLPoint deltaPos(inSpec.deltaPos);
	deltaPos.RotateAboutZ(-inSpec.angle);
	bool movingSideways = false;
	if (bounds.x > bounds.y && fabs(deltaPos.x) > fabs(deltaPos.y))
	{
	    movingSideways=true;
	}
	else if (bounds.x < bounds.y && fabs(deltaPos.x) < fabs(deltaPos.y))
	{
	    movingSideways=true;
	}
	if (movingSideways)
	{	
        // Try some angle tweaks to move us into gaps
        for (tVal deltaAngle=0.01; deltaAngle<=0.021; deltaAngle *= 2)
        {
            trialSpec=inSpec;
            trialSpec.deltaAngle=deltaAngle;
            perm=MotionSpecPermeabilityGet(trialSpec);
            if (perm > 0) break;
            trialSpec.deltaAngle=-deltaAngle;
            perm=MotionSpecPermeabilityGet(trialSpec);
            if (perm > 0) break;
            
            trialSpec=inSpec;
            trialSpec.deltaPos.x=0;
            trialSpec.deltaAngle=deltaAngle;
            perm=MotionSpecPermeabilityGet(trialSpec);
            if (perm > 0) break;
            trialSpec.deltaAngle=-deltaAngle;
            perm=MotionSpecPermeabilityGet(trialSpec);
            if (perm > 0) break;

            trialSpec=inSpec;
            trialSpec.deltaPos.y=0;
            trialSpec.deltaAngle=deltaAngle;
            perm=MotionSpecPermeabilityGet(trialSpec);
            if (perm > 0) break;
            trialSpec.deltaAngle=-deltaAngle;
            perm=MotionSpecPermeabilityGet(trialSpec);
            if (perm > 0) break;
        }
	}
    }
	
    if (perm <= 0 && deltaAngleSignificant)
    {
	// Turn where we are if we can
        trialSpec=inSpec;
        trialSpec.deltaPos.x=0;
        trialSpec.deltaPos.y=0;
        perm=MotionSpecPermeabilityGet(trialSpec);
    }

    if (perm <= 0 && deltaAngleSignificant)
    {
	// Escape from a corner where x and y need to change
        trialSpec=inSpec;
        trialSpec.deltaPos.x=-0.05;
        trialSpec.deltaPos.y=-0.05;
        perm=MotionSpecPermeabilityGet(trialSpec);
        if (perm <= 0)
        {
            trialSpec.deltaPos.x=0.05;
            trialSpec.deltaPos.y=-0.05;
            perm=MotionSpecPermeabilityGet(trialSpec);
        }
        if (perm <= 0)
        {
            trialSpec.deltaPos.x=-0.05;
            trialSpec.deltaPos.y=0.05;
            perm=MotionSpecPermeabilityGet(trialSpec);
        }
        if (perm <= 0)
        {
            trialSpec.deltaPos.x=0.05;
            trialSpec.deltaPos.y=0.05;
            perm=MotionSpecPermeabilityGet(trialSpec);
        }
    }

    if (perm <= 0)
    {
	// Cannot move at all
        trialSpec=inSpec;
        trialSpec.deltaPos=GLPoint(0,0);
        trialSpec.deltaAngle=0;
    }
    
    inSpec=trialSpec;

    if (perm > 0 && perm != 1)
    {
        // Scale deltaPos for permeabilty, if we can
        trialSpec=inSpec;
        trialSpec.deltaPos *= perm;
        if (MotionSpecPermeabilityGet(trialSpec) > 0)
        {
            inSpec=trialSpec;
        }
    }
}

tVal
GameSolidMap::MotionSpecPermeabilityGet(const GameMotionSpec& inSpec) const
{
    tVal perm=kPermeabilityMax;
    tCollisionSet colSet;
    CollisionSetAdd(colSet, inSpec);
    for (U32 i=0; i<colSet.size(); ++i)
    {
        tVal newPerm=PermeabilityGet(colSet[i]);
        if (newPerm < perm) perm=newPerm;
        if (perm <= 0)
        {
            break;
        }
    }
    return perm;
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
        if (inQuad.PointGet(i) == inPoint) return true;
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
                                   (perm>1)?1:0, 0.33);
                GLLine line((point-GLPoint(0.5, 0.5)),
                            (point+GLPoint(0.5, 0.5)));

                line.Render();
                line.RotateAboutCentre(M_PI/2);
                line.Render();
            }
        }
    }
    glPopMatrix();
}
