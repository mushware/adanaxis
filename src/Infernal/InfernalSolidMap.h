//%includeGuardStart {
#ifndef INFERNALSOLIDMAP_H
#define INFERNALSOLIDMAP_H
//%includeGuardStart } b+VVSAHEyUTKRjE83licXQ
//%Header {
/*****************************************************************************
 *
 * File: src/Infernal/InfernalSolidMap.h
 *
 * Copyright: Andy Southgate 2002-2007, 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/
//%Header } rC2HhXQejg2VQaT9rRmqQA
/*
 * $Id: InfernalSolidMap.h,v 1.6 2006/06/01 15:39:05 southa Exp $
 * $Log: InfernalSolidMap.h,v $
 * Revision 1.6  2006/06/01 15:39:05  southa
 * DrawArray verification and fixes
 *
 * Revision 1.5  2005/05/19 13:02:06  southa
 * Mac release work
 *
 * Revision 1.4  2004/01/06 20:46:51  southa
 * Build fixes
 *
 * Revision 1.3  2004/01/02 21:13:09  southa
 * Source conditioning
 *
 * Revision 1.2  2003/10/04 12:44:36  southa
 * File renaming
 *
 * Revision 1.1  2003/10/04 12:23:06  southa
 * File renaming
 *
 * Revision 1.16  2003/09/17 19:40:33  southa
 * Source conditioning upgrades
 *
 * Revision 1.15  2003/08/21 23:08:55  southa
 * Fixed file headers
 *
 * Revision 1.14  2003/01/13 14:32:00  southa
 * Build frameworks for Mac OS X
 *
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

#include "mushMushcore.h"
#include "mushGL.h"

class InfernalMapArea;
class InfernalMotionSpec;
class InfernalMapPoint;
class InfernalSpacePoint;

class InfernalSolidMap
{
public:
    enum
    {
        kPermeabilityMax=16
    };
    InfernalSolidMap();
    void SizeSet(Mushware::U32 inX, Mushware::U32 inY);
    void StepSet(Mushware::tVal inXStep, Mushware::tVal inYStep);
    const InfernalMapPoint SpaceToMap(const InfernalSpacePoint inPoint) const;
    const InfernalMapPoint SpaceToMapFractional(const InfernalSpacePoint inPoint) const;
    const InfernalSpacePoint MapToSpace(const InfernalMapPoint inPoint) const;
    void PermeabilitySet(Mushware::tVal inValue, Mushware::U32 inX, Mushware::U32 inY);
    Mushware::tVal PermeabilityGet(Mushware::U32 inX, Mushware::U32 inY) const;
    Mushware::tVal PermeabilityGet(const InfernalSpacePoint& inPoint) const;
    Mushware::tVal PermeabilityGet(const InfernalMapPoint& inPoint) const;
    void AdhesionSet(Mushware::tVal inValue, Mushware::U32 inX, Mushware::U32 inY);
    Mushware::tVal AdhesionGet(const InfernalSpacePoint& inPoint) const;
    Mushware::tVal AdhesionGet(const InfernalMapPoint& inPoint) const;
    void TrimMotion(InfernalMotionSpec& inSpec) const;
    void OverPlotCollisionSet(const InfernalMotionSpec& inSpec) const;
    void RenderSolid(const InfernalMapArea& inArea) const { Render(inArea, kTypePermeability); }
    void RenderAdhesion(const InfernalMapArea& inArea) const { Render(inArea, kTypeAdhesion); }
    
private:
    enum tType
    {
        kInvalid,
        kTypeNone,
        kTypePermeability,
        kTypeAdhesion
    };

    void Render(const InfernalMapArea& inArea, tType inType) const;

    typedef std::vector<InfernalMapPoint> tCollisionSet;
    void CollisionSetAdd(tCollisionSet& outSet, const InfernalMotionSpec& inSpec) const;
    void OverPlotBox(const InfernalMapPoint& inPoint) const;
    bool CollisionElementCheck(const InfernalMapPoint& inPoint, const GLQuad& inQuad) const;
    Mushware::tVal MotionSpecPermeabilityGet(const InfernalMotionSpec& inSpec) const;
    Mushware::U32 m_xsize;
    Mushware::U32 m_ysize;
    Mushware::tVal m_xstep;
    Mushware::tVal m_ystep;
    MushwareValarray<Mushware::tVal> m_solidMap;
    MushwareValarray<Mushware::tVal> m_adhesionMap;
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
