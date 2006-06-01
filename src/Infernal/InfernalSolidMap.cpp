//%Header {
/*****************************************************************************
 *
 * File: src/Infernal/InfernalSolidMap.cpp
 *
 * Author: Andy Southgate 2002-2006
 *
 * This file contains original work by Andy Southgate.  The author and his
 * employer (Mushware Limited) irrevocably waive all of their copyright rights
 * vested in this particular version of this file to the furthest extent
 * permitted.  The author and Mushware Limited also irrevocably waive any and
 * all of their intellectual property rights arising from said file and its
 * creation that would otherwise restrict the rights of any party to use and/or
 * distribute the use of, the techniques and methods used herein.  A written
 * waiver can be obtained via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } ifX0uWFt5trpFqM63IDIYg
/*
 * $Id: InfernalSolidMap.cpp,v 1.5 2005/05/19 13:02:06 southa Exp $
 * $Log: InfernalSolidMap.cpp,v $
 * Revision 1.5  2005/05/19 13:02:06  southa
 * Mac release work
 *
 * Revision 1.4  2004/01/02 21:13:09  southa
 * Source conditioning
 *
 * Revision 1.3  2003/10/04 15:32:11  southa
 * Module split
 *
 * Revision 1.2  2003/10/04 12:44:36  southa
 * File renaming
 *
 * Revision 1.1  2003/10/04 12:23:06  southa
 * File renaming
 *
 * Revision 1.36  2003/09/17 19:40:33  southa
 * Source conditioning upgrades
 *
 * Revision 1.35  2003/08/21 23:08:54  southa
 * Fixed file headers
 *
 * Revision 1.34  2003/01/20 10:45:27  southa
 * Singleton tidying
 *
 * Revision 1.33  2003/01/13 14:32:00  southa
 * Build frameworks for Mac OS X
 *
 * Revision 1.32  2003/01/12 17:32:56  southa
 * Mushcore work
 *
 * Revision 1.31  2002/12/29 20:59:57  southa
 * More build fixes
 *
 * Revision 1.30  2002/12/20 13:17:42  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.29  2002/10/22 20:42:05  southa
 * Source conditioning
 *
 * Revision 1.28  2002/10/17 15:50:59  southa
 * Config saving, pause and quit
 *
 * Revision 1.27  2002/10/12 15:25:18  southa
 * Facet renderer
 *
 * Revision 1.26  2002/10/08 17:13:18  southa
 * Tiered maps
 *
 * Revision 1.25  2002/08/27 08:56:26  southa
 * Source conditioning
 *
 * Revision 1.24  2002/08/18 20:44:35  southa
 * Initial chequepoint work
 *
 * Revision 1.23  2002/08/18 15:15:43  southa
 * Adhesion handling
 *
 * Revision 1.21  2002/08/18 12:20:41  southa
 * Movement tweaks
 *
 * Revision 1.20  2002/08/09 17:09:04  southa
 * InfernalDialogue added
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
 * Added InfernalMotion
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

#include "InfernalSolidMap.h"

#include "mushGL.h"

#include "InfernalData.h"
#include "InfernalMapArea.h"
#include "InfernalMapPoint.h"
#include "InfernalMotionSpec.h"
#include "InfernalSTL.h"
#include "InfernalSpacePoint.h"
#include "InfernalView.h"

using namespace Mushware;
using namespace std;

InfernalSolidMap::InfernalSolidMap():
    m_xsize(0),
    m_ysize(0),
    m_xstep(1),
    m_ystep(1)
{
}

void
InfernalSolidMap::SizeSet(U32 inXSize, U32 inYSize)
{
    m_xsize=inXSize;
    m_ysize=inYSize;
    m_solidMap.resize(0);
    m_solidMap.resize(m_xsize*m_ysize);
    m_adhesionMap.resize(0);
    m_adhesionMap.resize(m_xsize*m_ysize);
}

void
InfernalSolidMap::StepSet(tVal inXStep, tVal inYStep)
{
    m_xstep=inXStep;
    m_ystep=inYStep;
}

const InfernalMapPoint
InfernalSolidMap::SpaceToMapFractional(const InfernalSpacePoint inPoint) const
{
    InfernalMapPoint retVal(inPoint / GLPoint(m_xstep, m_ystep));
    return retVal;
}

const InfernalMapPoint
InfernalSolidMap::SpaceToMap(const InfernalSpacePoint inPoint) const
{
    InfernalMapPoint retVal(inPoint / GLPoint(m_xstep, m_ystep));
    retVal += GLPoint(0.5,0.5);
    retVal.MakeInteger();
    return retVal;
}

const InfernalSpacePoint
InfernalSolidMap::MapToSpace(const InfernalMapPoint inPoint) const
{
    return InfernalSpacePoint(inPoint * GLPoint(m_xstep, m_ystep));
}

void
InfernalSolidMap::PermeabilitySet(tVal inValue, U32 inX, U32 inY)
{
    MUSHCOREASSERT(inX < m_xsize);
    MUSHCOREASSERT(inY < m_ysize);
    m_solidMap[m_xsize * inY + inX] = inValue;
}

tVal
InfernalSolidMap::PermeabilityGet(U32 inX, U32 inY) const
{
    MUSHCOREASSERT(inX < m_xsize);
    MUSHCOREASSERT(inY < m_ysize);
    return m_solidMap[m_xsize * inY + inX];
}

tVal
InfernalSolidMap::PermeabilityGet(const InfernalSpacePoint& inPoint) const
{
    InfernalMapPoint mapPoint(SpaceToMap(inPoint));
    return PermeabilityGet(mapPoint);
}

tVal
InfernalSolidMap::PermeabilityGet(const InfernalMapPoint& inPoint) const
{
    // Permeability is always 0 outside of the map
    if (inPoint.x < 0 || inPoint.y < 0) return 0;
    U32 x=static_cast<U32>(inPoint.x+0.5);
    U32 y=static_cast<U32>(inPoint.y+0.5);
    if (x >= m_xsize || y>= m_ysize) return 0;
    return m_solidMap[m_xsize * y + x];
}

void
InfernalSolidMap::AdhesionSet(tVal inValue, U32 inX, U32 inY)
{
    MUSHCOREASSERT(inX < m_xsize);
    MUSHCOREASSERT(inY < m_ysize);
    m_adhesionMap[m_xsize * inY + inX] = inValue;
}

tVal
InfernalSolidMap::AdhesionGet(const InfernalSpacePoint& inPoint) const
{
    InfernalMapPoint mapPoint(SpaceToMap(inPoint));
    return AdhesionGet(mapPoint);
}

tVal
InfernalSolidMap::AdhesionGet(const InfernalMapPoint& inPoint) const
{
    // Permeability is always 0 outside of the map
    if (inPoint.x < 0 || inPoint.y < 0) return 1.0;
    U32 x=static_cast<U32>(inPoint.x+0.5);
    U32 y=static_cast<U32>(inPoint.y+0.5);
    if (x >= m_xsize || y>= m_ysize) return 1.0;
    return m_adhesionMap[m_xsize * y + x];
}

void
InfernalSolidMap::TrimMotion(InfernalMotionSpec& inSpec) const
{
    tVal perm;
    InfernalMotionSpec trialSpec;
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
InfernalSolidMap::MotionSpecPermeabilityGet(const InfernalMotionSpec& inSpec) const
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
InfernalSolidMap::OverPlotCollisionSet(const InfernalMotionSpec& inSpec) const
{
    tCollisionSet colSet;
    CollisionSetAdd(colSet, inSpec);
    for (U32 i=0; i<colSet.size(); ++i)
    {
        OverPlotBox(colSet[i]);
    }
}

void
InfernalSolidMap::OverPlotBox(const InfernalMapPoint& inPoint) const
{
    InfernalSpacePoint spacePoint(MapToSpace(inPoint));

    GLPoint rectOffset(m_xstep/2 - 1, m_ystep/2 - 1);
    
    GLRectangle rect(spacePoint-rectOffset,
                     spacePoint+rectOffset);

    InfernalData::Sgl().CurrentViewGet()->OverPlotGet().
        RenderableAdd(rect, GLColour(1,0.5,0));
}

void
InfernalSolidMap::CollisionSetAdd(tCollisionSet& outSet, const InfernalMotionSpec& inSpec) const
{
    // InfernalSpacePoint spacePoint(inSpec.pos+inSpec.deltaPos);
    // InfernalMapPoint mapPoint(SpaceToMap(spacePoint));

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
        mapQuad.PointSet(i, SpaceToMapFractional(InfernalSpacePoint(newQuad.PointGet(i))));
    }
    
    // Find the map area which encloses newQuad
    GLRectangle mapRect;
    mapQuad.BoundingRectangleGet(mapRect);
    mapRect+=GLPoint(0.5,0.5);
    mapRect.MakeInteger();
    mapRect.Clip(GLRectangle(0, 0, m_xsize-1, m_ysize-1));
    InfernalMapPoint mapPoint;
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
InfernalSolidMap::CollisionElementCheck(const InfernalMapPoint& inPoint, const GLQuad& inQuad) const
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
InfernalSolidMap::Render(const InfernalMapArea& inArea, tType inType) const
{
    GLUtils gl;
    glMatrixMode(GL_MODELVIEW);
    GLUtils::PushMatrix();
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
    GLState::DepthSet(GLState::kDepthNone);
    GLState::ModulationSet(GLState::kModulationColour);
    GLState::BlendSet(GLState::kBlendLine);
    
    for (point.x=minPoint.x; point.x<maxPoint.x; ++point.x)
    {
        for (point.y=minPoint.y; point.y<maxPoint.y; ++point.y)
        {
            if (inArea.IsWithin(point))
            {
                GLLine line((point-GLPoint(0.5, 0.5)),
                            (point+GLPoint(0.5, 0.5)));

                tVal value;
                switch (inType)
                {
                    case kTypePermeability:
                        value=PermeabilityGet(InfernalMapPoint(point));
                        break;

                    case kTypeAdhesion:
                        value=AdhesionGet(InfernalMapPoint(point));
                        break;

                    default:
                        value=0;
                        break;
                }
                GLState::ColourSet(0.5+0.5*cos(value*M_PI),
                                   0.5-0.5*cos(value*M_PI),
                                   (value>1)?1:0, 0.7);
                line.Render();
                line.RotateAboutCentre(M_PI/2);
                line.Render();
            }
        }
    }
    GLUtils::PopMatrix();
}
