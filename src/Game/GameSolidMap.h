#ifndef GAMESOLIDMAP_H
#define GAMESOLIDMAP_H
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
 * $Id: GameSolidMap.h,v 1.7 2002/08/18 15:13:16 southa Exp $
 * $Log: GameSolidMap.h,v $
 * Revision 1.7  2002/08/18 15:13:16  southa
 * Adhesion handling
 *
 * Revision 1.6  2002/08/07 13:36:50  southa
 * Conditioned source
 *
 * Revision 1.5  2002/08/02 09:05:11  southa
 * Movement modification in collison checking
 *
 * Revision 1.4  2002/08/01 16:47:12  southa
 * First multi-box collsion checking
 *
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
    enum
    {
        kPermeabilityMax=16
    };
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
    void AdhesionSet(tVal inValue, U32 inX, U32 inY);
    tVal AdhesionGet(const GameSpacePoint& inPoint) const;
    tVal AdhesionGet(const GameMapPoint& inPoint) const;
    void TrimMotion(GameMotionSpec& inSpec) const;
    void OverPlotCollisionSet(const GameMotionSpec& inSpec) const;
    void Render(const GameMapArea& inArea) const;
    
private:
    typedef vector<GameMapPoint> tCollisionSet;
    void CollisionSetAdd(tCollisionSet& outSet, const GameMotionSpec& inSpec) const;
    void OverPlotBox(const GameMapPoint& inPoint) const;
    bool CollisionElementCheck(const GameMapPoint& inPoint, const GLQuad& inQuad) const;
    tVal MotionSpecPermeabilityGet(const GameMotionSpec& inSpec) const;
    U32 m_xsize;
    U32 m_ysize;
    tVal m_xstep;
    tVal m_ystep;
    tValarray<tVal> m_solidMap;
    tValarray<tVal> m_adhesionMap;
};
#endif
