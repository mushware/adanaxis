//%includeGuardStart {
#ifndef MUSHMESHTOOLS_H
#define MUSHMESHTOOLS_H
//%includeGuardStart } 3QmVbluf3UkkQebEInihFQ
//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshTools.h
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
//%Header } fPwhnd1p1YdoaN8IyCGxoA
/*
 * $Id: MushMeshTools.h,v 1.16 2006/08/20 14:19:21 southa Exp $
 * $Log: MushMeshTools.h,v $
 * Revision 1.16  2006/08/20 14:19:21  southa
 * Seek operation
 *
 * Revision 1.15  2006/07/18 16:58:38  southa
 * Texture fixes
 *
 * Revision 1.14  2006/07/17 14:43:40  southa
 * Billboarded deco objects
 *
 * Revision 1.13  2006/06/14 18:45:48  southa
 * Ruby mesh generation
 *
 * Revision 1.12  2006/06/13 19:30:36  southa
 * Ruby mesh generation
 *
 * Revision 1.11  2006/06/09 21:07:13  southa
 * Tiled skin generation
 *
 * Revision 1.10  2006/06/09 11:43:03  southa
 * Facet to texture transformation
 *
 * Revision 1.9  2006/06/08 20:17:31  southa
 * Texture tile generation method 2
 *
 * Revision 1.8  2006/06/01 15:39:32  southa
 * DrawArray verification and fixes
 *
 * Revision 1.7  2005/07/19 10:07:06  southa
 * Adanaxis work
 *
 * Revision 1.6  2005/07/12 12:18:18  southa
 * Projectile work
 *
 * Revision 1.5  2005/05/19 13:02:11  southa
 * Mac release work
 *
 * Revision 1.4  2005/02/27 01:01:31  southa
 * Eigenplane markers
 *
 * Revision 1.3  2005/02/03 21:03:02  southa
 * Build fixes
 *
 * Revision 1.2  2005/02/03 15:46:53  southa
 * Quaternion work
 *
 * Revision 1.1  2004/10/31 23:34:07  southa
 * Hypercube rendering test
 *
 */

#include "MushMeshStandard.h"
#include "MushMeshVector.h"
#include "MushMeshQuaternion.h"
#include "MushMeshQuaternionPair.h"
#include "MushMeshPreMatrix.h"

class MushMesh4Mesh;
class MushMesh4TextureTile;
class MushMeshPosticity;

//:generate standard ostream xml1
class MushMeshTools : public MushcoreVirtualObject
{
public:
    enum
    {
        kAxisXY = 0,
        kAxisZW = 1,
        kAxisXZ = 2,
        kAxisYW = 3,
        kAxisXW = 4,
        kAxisYZ = 5
    };
    
	virtual ~MushMeshTools() {}
	typedef std::vector<Mushware::t4Val> tFacetVertices;
	
    static Mushware::t3x3Val RotateInXY(Mushware::tVal inAngle);
    static Mushware::t4x4Val MatrixRotateInAxis(Mushware::U32 inAxis, Mushware::tVal inAngle);
    static Mushware::tQValPair QuaternionRotateInAxis(Mushware::U32 inAxis, Mushware::tVal inAngle);
    static Mushware::tQValPair RandomOrientation(void);
    static Mushware::tVal Random(const Mushware::tVal inMin, const Mushware::tVal inMax);
    static Mushware::t4Val RandomVector(const Mushware::tVal inMin, const Mushware::tVal inMax);
    static Mushware::t4Val RandomUnitVector(void);
    static void RandomAngularVelocity(Mushware::tQValPair& outPair, Mushware::tVal inAmount);
	
	static Mushware::tQValPair QuaternionRotateToXAxis(const Mushware::t4Val &inVec);
	static Mushware::tQValPair QuaternionRotateToXYPlane(const Mushware::t4Val &inVec);
	static Mushware::tQValPair QuaternionRotateVectorPairToXYPlane(const Mushware::t4Val &inVec1, const Mushware::t4Val &inVec2);
	
	static Mushware::t4Val EdgeFromVertices(const tFacetVertices& inVertices, Mushware::U32 inNum);
	static Mushware::U32 LongestEdgeSelect(const tFacetVertices& inVertices);
	static Mushware::U32 MostOrthogonalEdgeSelect(const tFacetVertices& inVertices, const Mushware::t4Val& inVec);
	static void BoundingVectorsMake(Mushware::t4Val& outMin, Mushware::t4Val& outMax, const tFacetVertices& inVertices);

	static void FacetToTextureTransformMake(MushMesh4TextureTile& ioTile, const std::vector<Mushware::t4Val>& inVertices);
	static void VerticesForFacet(std::vector<Mushware::t4Val>& outVertices, const MushMesh4Mesh& inMesh,
								 Mushware::U32 inFaceNum, Mushware::U32 inFacetNum);
	static void TextureCoordsForFacet(std::vector<Mushware::t4Val>& outTexCoords, const MushMesh4Mesh& inMesh,
									  Mushware::U32 inFaceNum, Mushware::U32 inFacetNum);
    static void ClampedRotateToWAxis(Mushware::tQValPair& outPair, const Mushware::t4Val& inTarget, Mushware::tVal inAmount);
    static void PartialRotateToWAxis(Mushware::tQValPair& outPair, const Mushware::t4Val& inTarget, Mushware::tVal inAmount);

    static void WorldToObject(Mushware::tQValPair& ioPair, const MushMeshPosticity& inPost);
    static void WorldToObject(Mushware::t4Val& ioVec, const MushMeshPosticity& inPost);
    static void ObjectToWorld(Mushware::tQValPair& ioPair, const MushMeshPosticity& inPost);
    static void ObjectToWorld(Mushware::t4Val& ioVec, const MushMeshPosticity& inPost);
    static void TurnToFace(Mushware::tQValPair& outPair, const MushMeshPosticity& inPost,
                           const Mushware::t4Val& inTarget, Mushware::tVal inAmount);
     
    
//%classPrototypes {
public:
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } 1oBgFruy5qHAaudtV+Hcmg
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushMeshTools& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } NPgu1rRspSnV7PLxN0kaAg
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
