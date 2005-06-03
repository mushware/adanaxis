#ifndef GAMESOLIDMAP_H
#define GAMESOLIDMAP_H
/*****************************************************************************
 *
 * (Mushware file header version 1.2)
 *
 * This file contains original work by Andy Southgate.
 * Copyright Andy Southgate 2002.  All rights reserved.
 * Contact details can be found at http://www.mushware.com/
 *
 ****************************************************************************/

/*
 * $Id: GameSolidMap.h,v 1.13 2003/01/11 17:07:52 southa Exp $
 * $Log: GameSolidMap.h,v $
 * Revision 1.13  2003/01/11 17:07:52  southa
 * Mushcore library separation
 *
 * Revision 1.12  2003/01/11 13:03:14  southa
 * Use Mushcore header
 *
 * Revision 1.11  2002/12/20 13:17:43  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.10  2002/10/22 20:42:06  southa
 * Source conditioning
 *
 * Revision 1.9  2002/10/17 15:50:59  southa
 * Config saving, pause and quit
 *
 * Revision 1.8  2002/08/27 08:56:26  southa
 * Source conditioning
 *
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

#include "Mushcore.h"
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
    void SizeSet(Mushware::U32 inX, Mushware::U32 inY);
    void StepSet(Mushware::tVal inXStep, Mushware::tVal inYStep);
    const GameMapPoint SpaceToMap(const GameSpacePoint inPoint) const;
    const GameMapPoint SpaceToMapFractional(const GameSpacePoint inPoint) const;
    const GameSpacePoint MapToSpace(const GameMapPoint inPoint) const;
    void PermeabilitySet(Mushware::tVal inValue, Mushware::U32 inX, Mushware::U32 inY);
    Mushware::tVal PermeabilityGet(Mushware::U32 inX, Mushware::U32 inY) const;
    Mushware::tVal PermeabilityGet(const GameSpacePoint& inPoint) const;
    Mushware::tVal PermeabilityGet(const GameMapPoint& inPoint) const;
    void AdhesionSet(Mushware::tVal inValue, Mushware::U32 inX, Mushware::U32 inY);
    Mushware::tVal AdhesionGet(const GameSpacePoint& inPoint) const;
    Mushware::tVal AdhesionGet(const GameMapPoint& inPoint) const;
    void TrimMotion(GameMotionSpec& inSpec) const;
    void OverPlotCollisionSet(const GameMotionSpec& inSpec) const;
    void RenderSolid(const GameMapArea& inArea) const { Render(inArea, kTypePermeability); }
    void RenderAdhesion(const GameMapArea& inArea) const { Render(inArea, kTypeAdhesion); }
    
private:
    enum tType
    {
        kInvalid,
        kTypeNone,
        kTypePermeability,
        kTypeAdhesion
    };

    void Render(const GameMapArea& inArea, tType inType) const;

    typedef std::vector<GameMapPoint> tCollisionSet;
    void CollisionSetAdd(tCollisionSet& outSet, const GameMotionSpec& inSpec) const;
    void OverPlotBox(const GameMapPoint& inPoint) const;
    bool CollisionElementCheck(const GameMapPoint& inPoint, const GLQuad& inQuad) const;
    Mushware::tVal MotionSpecPermeabilityGet(const GameMotionSpec& inSpec) const;
    Mushware::U32 m_xsize;
    Mushware::U32 m_ysize;
    Mushware::tVal m_xstep;
    Mushware::tVal m_ystep;
    MushwareValarray<Mushware::tVal> m_solidMap;
    MushwareValarray<Mushware::tVal> m_adhesionMap;
};
#endif
