//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshTools.cpp
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
//%Header } cQoVIV2DdH4LiqrKzfp8tw
/*
 * $Id: MushMeshTools.cpp,v 1.9 2006/06/09 11:43:03 southa Exp $
 * $Log: MushMeshTools.cpp,v $
 * Revision 1.9  2006/06/09 11:43:03  southa
 * Facet to texture transformation
 *
 * Revision 1.8  2006/06/08 20:17:31  southa
 * Texture tile generation method 2
 *
 * Revision 1.7  2006/05/01 17:39:01  southa
 * Texture generation
 *
 * Revision 1.6  2005/07/18 13:13:36  southa
 * Extrude to point and projectile mesh
 *
 * Revision 1.5  2005/07/12 12:18:18  southa
 * Projectile work
 *
 * Revision 1.4  2005/05/19 13:02:11  southa
 * Mac release work
 *
 * Revision 1.3  2005/02/27 01:01:31  southa
 * Eigenplane markers
 *
 * Revision 1.2  2005/02/03 15:46:53  southa
 * Quaternion work
 *
 * Revision 1.1  2004/10/31 23:34:07  southa
 * Hypercube rendering test
 *
 */

#include "MushMeshTools.h"

#include "MushMeshSTL.h"
#include "MushMesh4Mesh.h"
#include "MushMesh4TextureTile.h"

using namespace Mushware;
using namespace std;

MushMeshPreMatrix<tVal, 3, 3>
MushMeshTools::RotateInXY(tVal inAngle)
{
    return MushMeshPreMatrix<tVal, 3, 3>
    (
         MushMeshVector<tVal, 3>( cos(inAngle), sin(inAngle), 0),
         MushMeshVector<tVal, 3>(-sin(inAngle), cos(inAngle), 0),
         MushMeshVector<tVal, 3>(            0,            0, 1)
     );
}

Mushware::t4x4Val
MushMeshTools::MatrixRotateInAxis(U32 inAxis, tVal inAngle)
{
    switch (inAxis)
    {
        case 0:            
            return MushMeshPreMatrix<tVal, 4, 4>
            (
             MushMeshVector<tVal, 4>( cos(inAngle),-sin(inAngle),            0,            0),
             MushMeshVector<tVal, 4>( sin(inAngle), cos(inAngle),            0,            0),
             MushMeshVector<tVal, 4>(            0,            0,            1,            0),
             MushMeshVector<tVal, 4>(            0,            0,            0,            1)
             );
            
        case 1:            
            return MushMeshPreMatrix<tVal, 4, 4>
            (
             MushMeshVector<tVal, 4>(            1,            0,            0,            0),
             MushMeshVector<tVal, 4>(            0,            1,            0,            0),
             MushMeshVector<tVal, 4>(            0,            0, cos(inAngle),-sin(inAngle)),
             MushMeshVector<tVal, 4>(            0,            0, sin(inAngle), cos(inAngle))
             );
        
        case 2:            
            return MushMeshPreMatrix<tVal, 4, 4>
            (
             MushMeshVector<tVal, 4>( cos(inAngle),            0,-sin(inAngle),            0),
             MushMeshVector<tVal, 4>(            0,            1,            0,            0),
             MushMeshVector<tVal, 4>( sin(inAngle),            0, cos(inAngle),            0),
             MushMeshVector<tVal, 4>(            0,            0,            0,            1)
             );
            
        case 3:            
            return MushMeshPreMatrix<tVal, 4, 4>
            (
             MushMeshVector<tVal, 4>(            1,            0,            0,            0),
             MushMeshVector<tVal, 4>(            0, cos(inAngle),            0,-sin(inAngle)),
             MushMeshVector<tVal, 4>(            0,            0,            1,            0),
             MushMeshVector<tVal, 4>(            0, sin(inAngle),            0, cos(inAngle))
             );
            
        case 4:            
            return MushMeshPreMatrix<tVal, 4, 4>
            (
             MushMeshVector<tVal, 4>( cos(inAngle),            0,            0,-sin(inAngle)),
             MushMeshVector<tVal, 4>(            0,            1,            0,            0),
             MushMeshVector<tVal, 4>(            0,            0,            1,            0),
             MushMeshVector<tVal, 4>( sin(inAngle),            0,            0, cos(inAngle))
             );
            
        case 5:            
            return MushMeshPreMatrix<tVal, 4, 4>
            (
             MushMeshVector<tVal, 4>(            1,            0,            0,            0),
             MushMeshVector<tVal, 4>(            0, cos(inAngle),-sin(inAngle),            0),
             MushMeshVector<tVal, 4>(            0, sin(inAngle), cos(inAngle),            0),
             MushMeshVector<tVal, 4>(            0,            0,            0,            1)
             );

        default:
        {
            ostringstream message;
            message << "Bad axis number (0 <= " << inAxis << " <= 5)";
            throw MushcoreLogicFail(message.str());
        }
    }
}

Mushware::tQValPair
MushMeshTools::QuaternionRotateInAxis(U32 inAxis, tVal inAngle)
{
    tVal halfAngle = inAngle/2;
    switch (inAxis)
    {
        case 0:            
            return tQValPair
            (
             tQVal(cos(halfAngle), sin(halfAngle), 0, 0),
             tQVal(cos(halfAngle), sin(halfAngle), 0, 0)
             );
            
        case 1:            
            return tQValPair
            (
             tQVal(cos(halfAngle), sin(halfAngle), 0, 0),
             tQVal(cos(halfAngle),-sin(halfAngle), 0, 0)
             );
            
        case 2:            
            return tQValPair
            (
             tQVal(cos(halfAngle), 0, sin(halfAngle), 0),
             tQVal(cos(halfAngle), 0, sin(halfAngle), 0)
             );
            
        case 3:            
            return tQValPair
            (
             tQVal(cos(halfAngle), 0,-sin(halfAngle), 0),
             tQVal(cos(halfAngle), 0, sin(halfAngle), 0)
             );
            
        case 4:            
            return tQValPair
            (
             tQVal(cos(halfAngle), 0, 0, sin(halfAngle)),
             tQVal(cos(halfAngle), 0, 0, sin(halfAngle))
             );
            
        case 5:            
            return tQValPair
            (
             tQVal(cos(halfAngle), 0, 0, sin(halfAngle)),
             tQVal(cos(halfAngle), 0, 0,-sin(halfAngle))
             );
            
        default:
        {
            ostringstream message;
            message << "Bad axis number (0 <= " << inAxis << " <= 5)";
            throw MushcoreLogicFail(message.str());
        }
    }
}

Mushware::tQValPair
MushMeshTools::RandomOrientation(void)
{
    tQVal q1, q2;
    for (U32 i=0; i<4; ++i)
    {
        q1.Set(Random(-1,1), i);
        q2.Set(Random(-1,1), i);
    }
    
    q1.InPlaceNormalise();
    q2.InPlaceNormalise();
    
    return tQValPair(q1, q2);
}    

Mushware::tVal
MushMeshTools::Random(const Mushware::tVal inMin, const Mushware::tVal inMax)
{
    return inMin + (inMax - inMin) * static_cast<double>(std::rand())/RAND_MAX;
}

Mushware::t4Val
MushMeshTools::RandomVector(const Mushware::tVal inMin, const Mushware::tVal inMax)
{
	t4Val retVal;
    for (U32 i=0; i<4; ++i)
	{
		if (Random(-1,1) > 0)
		{
			retVal.Set(Random(inMin, inMax), i);			
		}
		else
		{
			retVal.Set(-Random(inMin, inMax), i);
		}
	}
	return retVal;
}

void
MushMeshTools::RandomAngularVelocityMake(Mushware::tQValPair& outPair, Mushware::tVal inAmount)
{
    tQValPair orientation = MushMeshTools::RandomOrientation();
    outPair.ToRotationIdentitySet();
    
    outPair.OuterMultiplyBy(orientation);
    
    // Rotate in xy
    outPair.OuterMultiplyBy(MushMeshTools::QuaternionRotateInAxis
                                                    (0, MushMeshTools::Random(-inAmount, inAmount)));
    // Rotate in zw
    outPair.OuterMultiplyBy(MushMeshTools::QuaternionRotateInAxis
                                                    (1, MushMeshTools::Random(-inAmount, inAmount)));
    
    outPair.OuterMultiplyBy(orientation.Conjugate());
}

Mushware::tQValPair
MushMeshTools::QuaternionRotateToXAxis(const Mushware::t4Val &inVec)
{
	// Generates a rotation which aligns the supplied vector with the x axis
    t4Val rotVec(inVec);
	
	tQValPair retVal = QuaternionRotateInAxis(kAxisXW, -std::atan2(rotVec.W(), rotVec.X()));
	retVal.VectorRotate(rotVec);
	
	tQValPair rotXZ = QuaternionRotateInAxis(kAxisXZ, -std::atan2(rotVec.Z(), rotVec.X()));
	rotXZ.VectorRotate(rotVec);
	retVal.OuterMultiplyBy(rotXZ);
	
	tQValPair rotXY = QuaternionRotateInAxis(kAxisXY, -std::atan2(rotVec.Y(), rotVec.X()));
    retVal.OuterMultiplyBy(rotXY);
    
	return retVal;
}

Mushware::tQValPair
MushMeshTools::QuaternionRotateToXYPlane(const Mushware::t4Val &inVec)
{
	/* Generates a rotation which moves the supplied vector into the xy plane
	 * without using any rotations which change x
	 */
    t4Val rotVec(inVec);
	
	tQValPair retVal = QuaternionRotateInAxis(kAxisYW, -std::atan2(rotVec.W(), rotVec.Y()));
	retVal.VectorRotate(rotVec);
	
	tQValPair rotYZ = QuaternionRotateInAxis(kAxisYZ, -std::atan2(rotVec.Z(), rotVec.Y()));
    retVal.OuterMultiplyBy(rotYZ);
    
	return retVal;
}

Mushware::tQValPair
MushMeshTools::QuaternionRotateVectorPairToXYPlane(const Mushware::t4Val &inVec1, const Mushware::t4Val &inVec2)
{
	/* Generates a rotation which moves the first vector to the x axis, and the second
	 * vector into the xy plane.  Details are in the 'Projection and Rendering 1'
	 * document (2006-06-08 version) at mushware.com, in the texture generation section
	 */
	
	tQValPair qR1 = QuaternionRotateToXAxis(inVec1); // R1 matrix
	tQValPair qR2 = QuaternionRotateToXYPlane(qR1.RotatedVector(inVec2));
	
	qR1.OuterMultiplyBy(qR2); // qR1 now the final rotation
	
	return qR1;
}

Mushware::t4Val
MushMeshTools::EdgeFromVertices(const tFacetVertices& inVertices, Mushware::U32 inNum)
{
	MUSHCOREASSERT(inNum < inVertices.size());

	U32 numVertices = inVertices.size();
	U32 nextVertex = inNum+1;
	if (nextVertex >= numVertices) nextVertex = 0;

	return inVertices[nextVertex] - inVertices[inNum];
}


Mushware::U32
MushMeshTools::LongestEdgeSelect(const tFacetVertices& inVertices)
{
    tVal greatestLengthSquared = 0;
	U32 longestEdge = 0;
	U32 numVertices = inVertices.size();
	
	for (U32 i=0; i<numVertices; ++i)
	{
		t4Val edgeVec = EdgeFromVertices(inVertices, i);
		
		tVal lengthSquared = edgeVec * edgeVec;
		
		if (lengthSquared > greatestLengthSquared)
		{
			greatestLengthSquared = lengthSquared;
			longestEdge = i;
		}
	}
	return longestEdge;		
}

Mushware::U32
MushMeshTools::MostOrthogonalEdgeSelect(const tFacetVertices& inVertices, const Mushware::t4Val& inVec)
{
	// Returns the edge with the largest orthogonal component
    tVal greatestOrthoComp = 0;
	U32 mostOrthoEdge = 0;
	tVal vecLength = inVec.Magnitude();
	
	MUSHCOREASSERT(vecLength > 0);
	
	U32 numVertices = inVertices.size();
	
	for (U32 i=0; i<numVertices; ++i)
	{
		t4Val edgeVec = EdgeFromVertices(inVertices, i);

		tVal edgeVecLength = edgeVec.Magnitude();
		
		if (edgeVecLength > 0) // Ignore degenerate edges
		{
			tVal cosAngle = (inVec * edgeVec) / (vecLength * edgeVecLength);
			MUSHCOREASSERT(cosAngle > -1.001 && cosAngle < 1.001);
			
			tVal cosAngleSquared = cosAngle * cosAngle;
			
			if (cosAngleSquared > 1) cosAngleSquared = 1;
			
			tVal sinAngle = std::sqrt(1 - cosAngleSquared);
			
			tVal orthoComp = sinAngle * edgeVecLength;
			
			if (orthoComp > greatestOrthoComp)
			{
				greatestOrthoComp = orthoComp;
				mostOrthoEdge = i;
			}
		}
	}
	return mostOrthoEdge;
}

void
MushMeshTools::BoundingVectorsMake(Mushware::t4Val& outMin, Mushware::t4Val& outMax, const tFacetVertices& inVertices)
{
	MUSHCOREASSERT(inVertices.size() > 0);
	outMin = inVertices[0];
	outMax = inVertices[0];
	
	U32 numVertices = inVertices.size();
	
	for (U32 i=1; i<numVertices; ++i)
	{
		const t4Val& vertRef = inVertices[i];
		
		for (U32 j=0; j<4; ++j)
		{
			if (vertRef.Get(j) < outMin.Get(j))
			{
			    outMin.Set(vertRef.Get(j), j);
			}
			if (vertRef.Get(j) > outMax.Get(j))
			{
			    outMax.Set(vertRef.Get(j), j);
			}
		}
	}
}

void
MushMeshTools::FacetToTextureTransformMake(MushMesh4TextureTile& ioTile, const tFacetVertices& inVertices)
{
	U32 longestEdge = MushMeshTools::LongestEdgeSelect(inVertices);
	
	t4Val p0 = inVertices[longestEdge];

	t4Val longestEdgeVec = EdgeFromVertices(inVertices, longestEdge);
	// longestEdgeVec starts at p0 and ends at p0+longestEdgeVec
	
	U32 orthoEdge = MushMeshTools::MostOrthogonalEdgeSelect(inVertices, longestEdgeVec);
	
	t4Val orthoEdgeVec = EdgeFromVertices(inVertices, orthoEdge);
	
	tQValPair qR = QuaternionRotateVectorPairToXYPlane(longestEdgeVec, orthoEdgeVec);
	
	tFacetVertices rotatedVertices(inVertices);
	
	for (U32 i=0; i<rotatedVertices.size(); ++i)
	{
		rotatedVertices[i] -= p0;
		qR.VectorRotate(rotatedVertices[i]);	
	}
	
	t4Val minVec, maxVec;
	BoundingVectorsMake(minVec, maxVec, rotatedVertices);
	
	t4Val spanVec = maxVec - minVec;
	
	if (spanVec.X() <= 0 || spanVec.Y() <= 0)
	{
		/* Degenerate facet which will not be rendered.  Use default values to
		 * prevent division by zero
		 */
		spanVec.XSet(1);
		spanVec.YSet(1);
	}
	
#ifdef MUSHCORE_DEBUG
	/* If the facet is planar the rotation should map all vertices to the xy plane.
	 * If extent in z or w is more than 10% of extent in x and y, generate a warning
	 */
	if (std::fabs(spanVec.X()) + std::fabs(spanVec.Y()) < 0.1 * std::fabs(spanVec.Z()) + std::fabs(spanVec.W()))
	{
		MushcoreLog::Sgl().WarningLog() << "Significantly non-planar facet passed to MushMeshTools::FacetToTextureTransformMake" << endl;
	}
#endif
	
	const t2BoxVal& tileBox = ioTile.TileBox();
	t2Val tileSize = tileBox.Size();
	
	t4Val vS = ioTile.SK() * t4Val(tileSize.X() / spanVec.X(), tileSize.Y() / spanVec.Y(), 1, 1);

	if (vS.X() <= 0 || vS.Y() <= 0)
	{
		throw MushcoreDataFail("Degenerate tile passed to FacetToTextureTransformMake");
	}
	
	t4Val vT = t4Val( (tileBox.Start().X() + tileBox.End().X() - vS.X() * (minVec.X() + maxVec.X())) / 2,
					  (tileBox.Start().Y() + tileBox.End().Y() - vS.Y() * (minVec.Y() + maxVec.Y())) / 2,
					  0,0);
	vT -= vS.ElementwiseProduct(qR.RotatedVector(p0));
	
	ioTile.QRSet(qR);
	ioTile.VSSet(vS);
	ioTile.VTSet(vT);
	
	ioTile.QRInverseSet(qR.Conjugate());
	ioTile.VSInverseSet(t4Val(1 / vS.X(), 1 / vS.Y(), 1, 1));
	ioTile.FacetTransformValidSet(true);
}

void
MushMeshTools::VerticesForFacet(std::vector<Mushware::t4Val>& outVertices, const MushMesh4Mesh& inMesh,
								Mushware::U32 inFaceNum, Mushware::U32 inFacetNum)
{
    const MushMesh4Face& faceRef = inMesh.Face(inFaceNum);
	const MushMesh4Face::tVertexList& vertexList = faceRef.VertexList();
    const MushMesh4Mesh::tVertices& vertices = inMesh.Vertices();
	
    U32 facetStart, facetEnd;
	faceRef.FacetLimitsGet(facetStart, facetEnd, inFacetNum);
	
	outVertices.resize(0);
	
	MUSHCOREASSERT(facetEnd <= vertexList.size());
	
	for (U32 i=facetStart; i < facetEnd; ++i)
	{
		U32 vertexNum = vertexList[i];
		MUSHCOREASSERT(vertexNum <= vertices.size());
		
		outVertices.push_back(vertices[vertexNum]);
	}
}

void
MushMeshTools::TextureCoordsForFacet(std::vector<Mushware::t4Val>& outTexCoords, const MushMesh4Mesh& inMesh,
   									 Mushware::U32 inFaceNum, Mushware::U32 inFacetNum)
{
    const MushMesh4Face& faceRef = inMesh.Face(inFaceNum);
	const MushMesh4Face::tTexCoordList& texCoordList = faceRef.TexCoordList();
    const MushMesh4Mesh::tTexCoords& texCoords = inMesh.TexCoords();

    U32 facetStart, facetEnd;
	faceRef.FacetLimitsGet(facetStart, facetEnd, inFacetNum);
	
	outTexCoords.resize(0);
	
	MUSHCOREASSERT(facetEnd <= texCoordList.size());
				   
	for (U32 i=facetStart; i < facetEnd; ++i)
	{
		U32 texCoordNum = texCoordList[i];
		MUSHCOREASSERT(texCoordNum <= texCoords.size());
		
		outTexCoords.push_back(texCoords[texCoordNum]);
	}
}


