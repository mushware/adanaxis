/*
 * $Id: GameSolidMap.h,v 1.2 2002/07/16 19:30:09 southa Exp $
 * $Log: GameSolidMap.h,v $
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
    void PermeabilitySet(tVal inValue, U32 inX, U32 inY);
    tVal PermeabilityGet(U32 inX, U32 inY) const;
    tVal PermeabilityGet(const GameSpacePoint& inPoint) const;
    tVal PermeabilityGet(const GameMapPoint& inPoint) const;
    void TrimMotion(GameMotionSpec& inSpec) const;
    void RenderCollisionSet(const GLRectangle& inRect, tVal inAngle);
    void Render(const GameMapArea& inArea) const;
    
private:
    U32 m_xsize;
    U32 m_ysize;
    tVal m_xstep;
    tVal m_ystep;
    tValarray<tVal> m_solidMap;
};
