/*
 * $Id: GameSolidMap.h,v 1.1 2002/07/16 17:48:09 southa Exp $
 * $Log: GameSolidMap.h,v $
 * Revision 1.1  2002/07/16 17:48:09  southa
 * Collision and optimisation work
 *
 */

#include "mushCore.h"
#include "mushGL.h"

class GameMapArea;

class GameSolidMap
{
public:
    void SizeSet(U32 inX, U32 inY);
    void PermeabilitySet(tVal inValue, U32 inX, U32 inY);
    tVal PermeabilityGet(U32 inX, U32 inY) const;
    tVal PermeabilityGet(const GLPoint& inPoint) const;
    void TrimVector(GLPoint& ioVec, const GLPoint& inStart) const;
    void RenderCollisionSet(const GLRectangle& inRect, tVal inAngle);
    void Render(const GameMapArea& inArea, const GLPoint& inSteps) const;
    
private:
    U32 m_xsize;
    U32 m_ysize;
    tValarray<tVal> m_solidMap;
};


