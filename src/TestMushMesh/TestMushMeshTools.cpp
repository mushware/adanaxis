//%Header {
/*****************************************************************************
 *
 * File: src/TestMushMesh/TestMushMeshTools.cpp
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
//%Header } Z5M+0kNmdF0ldv1BT2B0fQ
/*
 * $Id: TestMushMeshTools.cpp,v 1.1 2006/06/08 20:17:32 southa Exp $
 * $Log: TestMushMeshTools.cpp,v $
 * Revision 1.1  2006/06/08 20:17:32  southa
 * Texture tile generation method 2
 *
 */

#include "TestMushMeshTools.h"

using namespace Mushware;
using namespace std;

MushcoreInstaller TestMushMeshToolsInstaller(TestMushMeshTools::Install);

bool
TestMushMeshTools::ApproxEquals(Mushware::t4Val inVec1, Mushware::t4Val inVec2)
{
    bool retVal = true;
    for (U32 i=0; i<4; ++i)
    {
        if (std::fabs(inVec1[i] - inVec2[i]) > 1e-4)
        {
            retVal = false;   
        }
    }
    return retVal;
}

void
TestMushMeshTools::TestFacetTransform(void)
{
	for (U32 i=0; i<100; ++i)
	{	
		MushMeshTools::tFacetVertices vertices;
		vertices.push_back(t4Val(3,4,0,0)); // edge 0 = (-1,-3, 0, 0)
		vertices.push_back(t4Val(2,1,0,0)); // edge 1 = (-1, 0, 0, 0)
		vertices.push_back(t4Val(1,1,0,0)); // edge 2 = ( 0, 2, 0, 0)
		vertices.push_back(t4Val(1,3,0,0)); // edge 3 = ( 2, 1, 0, 0)
		
		if (i == 0)
		{
			t4Val minVec, maxVec;
			
			MushMeshTools::BoundingVectorsMake(minVec, maxVec, vertices);
			
			if (minVec != t4Val(1,1,0,0) || maxVec != t4Val(3,4,0,0))
			{
				std::ostringstream message;
				message << "BoundingVectorsMake failed: calculated bounds were " << minVec << "," << maxVec << " from vertex list " << vertices;
				throw MushcoreCommandFail(message.str());
			}
			
		}
		else
		{
			tQValPair rotation = MushMeshTools::RandomOrientation();
		
			for (U32 j=0; j<vertices.size(); ++j)
			{
				rotation.VectorRotate(vertices[j]);
			}
		}
		
		U32 longestEdge = MushMeshTools::LongestEdgeSelect(vertices);
		
		if (longestEdge != 0)
		{
			std::ostringstream message;
			message << "LongestEdgeSelect failed: selected edge " << longestEdge << " from vertex list " << vertices;
			throw MushcoreCommandFail(message.str());
		}
		
		t4Val longestEdgeVec = vertices[ (longestEdge + 1) % vertices.size() ] - vertices[longestEdge];
		
		U32 mostOrthoEdge = MushMeshTools::MostOrthogonalEdgeSelect(vertices, longestEdgeVec);

		if (mostOrthoEdge != 3)
		{
			std::ostringstream message;
			message << "MostOrthogonalEdgeSelect failed: selected edge " << mostOrthoEdge << " from vertex list " << vertices;
			throw MushcoreCommandFail(message.str());
		}
		
	}
	
	for (U32 i=0; i<5; ++i)
	{
		MushMesh4TextureTile texTile;
		
		t2Val boxSize(MushMeshTools::Random(0.1,1), MushMeshTools::Random(0.1,1));
		t2Val boxStart(MushMeshTools::Random(0, 1-boxSize.X()), MushMeshTools::Random(0, 1-boxSize.Y()));
		t2Val boxEnd = boxStart+boxSize;
		
		texTile.TileBoxSet(t2BoxVal(boxStart, boxEnd));
		
		MushMeshTools::tFacetVertices vertices;
		vertices.push_back(t4Val(MushMeshTools::Random(-10,10),MushMeshTools::Random(-10,10),0,0));
		vertices.push_back(t4Val(MushMeshTools::Random(-10,10),MushMeshTools::Random(-10,10),0,0));
		vertices.push_back(t4Val(MushMeshTools::Random(-10,10),MushMeshTools::Random(-10,10),0,0));
		vertices.push_back(t4Val(MushMeshTools::Random(-10,10),MushMeshTools::Random(-10,10),0,0));
		U32 numVertices = vertices.size();
		
		{
			tQValPair rotation = MushMeshTools::RandomOrientation();
			
			for (U32 j=0; j<vertices.size(); ++j)
			{
				rotation.VectorRotate(vertices[j]);
			}
		}
		
		MushMeshTools::FacetToTextureTransformMake(texTile, vertices);
		
		std::vector<Mushware::t2Val> transVert(numVertices);
		std::vector<Mushware::t4Val> trans4Vert(numVertices);
		
		for (Mushware::U32 j=0; j<numVertices; ++j)
		{
			texTile.FacetToTexture(transVert[j], vertices[j]);
			t4Val reverseVec;
			texTile.TextureToFacet(reverseVec, transVert[j]);
			
			if (!ApproxEquals(reverseVec, vertices[j]))
			{
				std::ostringstream message;
				message << "FacetToTextureToFacet failed: expected " << vertices[j] << ", got " << reverseVec <<
					"(texture position " << transVert[j] << ")";
				throw MushcoreCommandFail(message.str());
			}
			trans4Vert[j] = t4Val(transVert[j].X(), transVert[j].Y(), 0, 0);
		}
		
		t4Val minVec, maxVec;
		
		MushMeshTools::BoundingVectorsMake(minVec, maxVec, trans4Vert);

		if (!ApproxEquals(minVec, t4Val(boxStart.X(), boxStart.Y(), 0, 0)))
		{
			std::ostringstream message;
			message << "Tile minimum mismatch: expected " << boxStart << ", got " << minVec;
			throw MushcoreCommandFail(message.str());
		}
			
		if (!ApproxEquals(maxVec, t4Val(boxEnd.X(), boxEnd.Y(), 0, 0)))
		{
			std::ostringstream message;
			message << "Tile minimum mismatch: expected " << boxEnd << ", got " << maxVec;
			throw MushcoreCommandFail(message.str());
		}
	}
}

MushcoreScalar
TestMushMeshTools::TestTools(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
	const tVal limit=0.001;
	
    for (U32 i=0; i<100; ++i)
    {
		const t4Val initialVec1 = MushMeshTools::RandomVector(1, 10);

		tQValPair rotation1 = MushMeshTools::QuaternionRotateToXAxis(initialVec1);
		
		t4Val resultVec = rotation1.RotatedVector(initialVec1);
		
		if (std::fabs(resultVec.X()) < 1 ||
			std::fabs(resultVec.Y()) > limit ||
			std::fabs(resultVec.Z()) > limit ||
			std::fabs(resultVec.W()) > limit)
		{
			std::ostringstream message;
			message << "RotateToXAxis failed: input=" << initialVec1 << ", output=" << resultVec;
			throw MushcoreCommandFail(message.str());
		}
		
		t4Val initialVec2;
		
		// Find a non-colinear vector
		do
		{
			initialVec2 = MushMeshTools::RandomVector(1, 10);
		} while (initialVec1 * initialVec2 < 0.1);
		
	    t4Val otherVec = rotation1.RotatedVector(initialVec2);
		
		tQValPair rotation2 = MushMeshTools::QuaternionRotateToXYPlane(otherVec);
		
		resultVec = rotation2.RotatedVector(otherVec);
		
		if (std::fabs(resultVec.X()) + std::fabs(resultVec.Y()) < 1 ||
			std::fabs(resultVec.Z()) > limit ||
			std::fabs(resultVec.W()) > limit)
		{
			std::ostringstream message;
			message << "RotateToXYPlane failed: input=" << initialVec2 << ", output=" << resultVec;
			throw MushcoreCommandFail(message.str());
		}
	
		tQValPair finalR;
		
		if (i % 2 == 0)
		{
			finalR = rotation1;
			finalR.OuterMultiplyBy(rotation2);
		}
		else
		{
			finalR = MushMeshTools::QuaternionRotateVectorPairToXYPlane(initialVec1, initialVec2);
		}
		
		t4Val finalVec1 = finalR.RotatedVector(initialVec1);
		t4Val finalVec2 = finalR.RotatedVector(initialVec2);
		
		if (std::fabs(finalVec1.X()) < 1 ||
			std::fabs(finalVec1.Y()) > limit ||
			std::fabs(finalVec1.Z()) > limit ||
			std::fabs(finalVec1.W()) > limit)
		{
			std::ostringstream message;
			message << "RotateToPlane failed in x: input=" << initialVec1 << ", output=" << finalVec1;
			throw MushcoreCommandFail(message.str());
		}

		if (std::fabs(finalVec2.X()) + std::fabs(finalVec2.Y()) < 1 ||
			std::fabs(finalVec2.Z()) > limit ||
			std::fabs(finalVec2.W()) > limit)
		{
			std::ostringstream message;
			message << "RotateToPlane failed in xy: input=" << initialVec2 << ", output=" << finalVec2;
			throw MushcoreCommandFail(message.str());
		}
		
		for (U32 j=0; j<10; ++j)
		{
		    t4Val anotherVec = MushMeshTools::Random(-10,10) * initialVec1 +
				MushMeshTools::Random(-10,10) * initialVec2;
			
			t4Val finalAnotherVec = finalR.RotatedVector(anotherVec);

			if (std::fabs(finalAnotherVec.X()) + std::fabs(finalAnotherVec.Y()) < 1 ||
				std::fabs(finalAnotherVec.Z()) > limit ||
				std::fabs(finalAnotherVec.W()) > limit)
			{
				std::ostringstream message;
				message << "RotateToPlane failed for combination: input=" << anotherVec << ", output=" << finalAnotherVec;
				throw MushcoreCommandFail(message.str());
			}
		}
    }
	
	TestFacetTransform();
	
    return MushcoreScalar(0);
}

void
TestMushMeshTools::Install(void)
{
    MushcoreInterpreter::Sgl().HandlerAdd("testmushmeshtools", TestTools);
}
