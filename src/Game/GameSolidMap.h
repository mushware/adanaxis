/*
 * $Id: GameSolidMap.h,v 1.3 2002/07/31 16:27:17 southa Exp $
 * $Log: GameSolidMap.h,v $
 * Revision 1.3  2002/07/31 16:27:17  southa
 * Collision checking work
 *
 * Revision 1.2  2002/07/16 19:30:09  southa
 * Simplistic collision checking
 *
 * Revision 1.1  2002/07/16 17:48:09  southa
 * Collision and optimisation work
 *
 */

#include "mushCore.h"
#include "mushGL.h"

class GameMapArea;
class GameMotionSpec;
class GameMapPoint;
class GameSpacePoint;

class GameSolidMap
{
public:
    GameSolidMap();
    void SizeSet(U32 inX, U32 inY);
    void StepSet(tVal inXStep, tVal inYStep);
    const GameMapPoint SpaceToMap(const GameSpacePoint inPoint) const;
    const GameMapPoint SpaceToMapFractional(const GameSpacePoint inPoint) const;
    const GameSpacePoint MapToSpace(const GameMapPoint inPoint) const;
    void PermeabilitySet(tVal inValue, U32 inX, U32 inY);
    tVal PermeabilityGet(U32 inX, U32 inY) const;
    tVal PermeabilityGet(const GameSpacePoint& inPoint) const;
    tVal PermeabilityGet(const GameMapPoint& inPoint) const;
    void TrimMotion(GameMotionSpec& inSpec) const;
    void OverPlotCollisionSet(const GameMotionSpec& inSpec) const;
    void Render(const GameMapArea& inArea) const;
    
private:
    typedef vector<GameMapPoint> tCollisionSet;
    void CollisionSetAdd(tCollisionSet& outSet, const GameMotionSpec& inSpec) const;
    void OverPlotBox(const GameMapPoint& inPoint) const;
    bool CollisionElementCheck(const GameMapPoint& inPoint, const GLQuad& inQuad) const;
    
    U32 m_xsize;
    U32 m_ysize;
    tVal m_xstep;
    tVal m_ystep;
    tValarray<tVal> m_solidMap;
};
