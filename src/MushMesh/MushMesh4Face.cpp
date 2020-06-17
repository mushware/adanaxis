//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMesh4Face.cpp
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
//%Header } l3llrCnaY9r6hefLfHK3yA
/*
 * $Id: MushMesh4Face.cpp,v 1.11 2006/12/18 15:39:35 southa Exp $
 * $Log: MushMesh4Face.cpp,v $
 * Revision 1.11  2006/12/18 15:39:35  southa
 * Palette changes
 *
 * Revision 1.10  2006/12/14 00:33:49  southa
 * Control fix and audio pacing
 *
 * Revision 1.9  2006/06/19 15:57:17  southa
 * Materials
 *
 * Revision 1.8  2006/06/01 15:39:28  southa
 * DrawArray verification and fixes
 *
 * Revision 1.7  2005/07/14 12:50:31  southa
 * Extrusion work
 *
 * Revision 1.6  2005/07/13 20:35:48  southa
 * Extrusion work
 *
 * Revision 1.5  2005/07/13 16:45:05  southa
 * Extrusion work
 *
 * Revision 1.4  2005/07/12 20:39:04  southa
 * Mesh library work
 *
 * Revision 1.3  2005/07/02 00:42:38  southa
 * Conditioning tweaks
 *
 * Revision 1.2  2005/06/30 12:34:59  southa
 * Mesh and source conditioner work
 *
 * Revision 1.1  2005/06/30 12:04:55  southa
 * Mesh work
 *
 */

#include "MushMesh4Face.h"

#include "MushMeshMushcoreIO.h"
#include "MushMeshSTL.h"

using namespace Mushware;
using namespace std;

MushMesh4Face::MushMesh4Face() :
    m_faceType(kFaceTypeNone),
    m_internal(false)
{
    AllTouch();
}

MushMesh4Face::~MushMesh4Face()
{
}

void
MushMesh4Face::VerticesTouch(void)
{
    m_faceCentroidValid = false;
    m_boundingRadiusValid = false;
}

void
MushMesh4Face::AllTouch(void)
{
    VerticesTouch();
    m_uniqueVertexListValid = false;
    m_faceConnectivityValid = false;
    m_vertexConnectivityValid = false;
}

void
MushMesh4Face::Purge(void)
{
    // Extrusion data may be required for animation
    m_extrusionMap.clear();
    m_extrudedFaces.resize(0);
    m_extrusionTransformList.resize(0);
    
    m_uniqueVertexListValid = false;
    m_uniqueVertexList.resize(0);
    m_faceConnectivityValid = false;
    m_faceConnectivity.resize(0);
    m_vertexConnectivityValid = false;
    m_vertexConnectivity.clear();
}

void
MushMesh4Face::FacetLimitsGet(Mushware::U32& outStart, Mushware::U32& outEnd, Mushware::U32 inFacetNum) const
{
    U32 start = 0;
    MushcoreUtil::BoundsCheck(inFacetNum, m_vertexGroupSize.size());
    
    for (U32 i=0; i < inFacetNum; ++i)
    {
        start += m_vertexGroupSize[i];
    }
    outStart = start;
    outEnd = start + m_vertexGroupSize[inFacetNum];
    U32 vertexListSize = m_vertexList.size();
    if (outStart >= vertexListSize || outEnd > vertexListSize)
    {
        throw MushcoreDataFail("Bad facet limits");
    }
}

bool
MushMesh4Face::ConnectedVertexInFacetFind(Mushware::U32& outNum, Mushware::U32 inFacetNum, Mushware::U32 inVertNum) const
{
    // Return a vertex (if any) which is in the facet and connected to the vertex
    
    bool success = false;
    
    // Build vertex connectivity
    VertexConnectivity();
    
    tVertexConnectivity::iterator vertexConnection = m_vertexConnectivity.find(inVertNum);
    if (vertexConnection == m_vertexConnectivity.end())
    {
        ostringstream message;
        message << "Request for connected vertex " << inVertNum << " not in face";
        throw MushcoreDataFail(message.str());
    }
    
    U32 start, end;
    FacetLimitsGet(start, end, inFacetNum);
    
    for (U32 i=start; !success && i<end; ++i)
    {
        MUSHCOREASSERT(i < m_vertexList.size());
        U32 testVertNum = m_vertexList[i];
        if (testVertNum == inVertNum)
        {
            ostringstream message;
            message << "Request for connected vertex " << inVertNum << " within facet " << inFacetNum;
            throw MushcoreDataFail(message.str());
        }
        
        if (std::find(vertexConnection->second.begin(),
                      vertexConnection->second.end(),
                      testVertNum) != vertexConnection->second.end())
        {
            outNum = testVertNum;
            success = true;
        }
    }
    return success;
}


void
MushMesh4Face::UniqueVertexListBuild(void) const
{
    m_uniqueVertexList.resize(0);
    U32 vertexListSize = m_vertexList.size();
    for (U32 i=0; i<vertexListSize; ++i)
    {
        Mushware::U32 vertexNum = m_vertexList[i];
        
        if (std::find(m_uniqueVertexList.begin(),
                      m_uniqueVertexList.end(),
                      vertexNum) == m_uniqueVertexList.end())
        {
            m_uniqueVertexList.push_back(vertexNum);
        }
    }
    
    std::sort(m_uniqueVertexList.begin(), m_uniqueVertexList.end());

    m_uniqueVertexListValid = true;
}

void
MushMesh4Face::VertexConnectivityBuild(void) const
{
    m_numVertexConnections = 0;
    
    // Build the unique vertex list
    UniqueVertexList();

    m_vertexConnectivity.clear();
    
    U32 listIndex = 0;
    for (U32 j=0; j<m_vertexGroupSize.size(); ++j)
    {
        U32 vertexGroupSize = m_vertexGroupSize[j];
        if (vertexGroupSize > 1)
        {
            for (U32 k=0; k<vertexGroupSize; ++k)
            {
                U32 vertIndex = listIndex+k;
                U32 otherVertIndex;
                if (k+1 < vertexGroupSize)
                {
                    otherVertIndex = listIndex+k+1;
                }
                else
                {
                    otherVertIndex = listIndex;
                }
                
                MUSHCOREASSERT(vertIndex < m_vertexList.size());
                MUSHCOREASSERT(otherVertIndex < m_vertexList.size());
                
                U32 vertNum = m_vertexList[vertIndex];
                U32 otherVertNum = m_vertexList[otherVertIndex];
                
                tVertexConnection& vertexConnection = m_vertexConnectivity[vertNum];
                tVertexConnection& otherVertexConnection = m_vertexConnectivity[otherVertNum];
                
                if (std::find(vertexConnection.begin(),
                              vertexConnection.end(),
                              otherVertNum) == vertexConnection.end())
                {
                    vertexConnection.push_back(otherVertNum);
                    ++m_numVertexConnections;
                }
                if (std::find(otherVertexConnection.begin(),
                              otherVertexConnection.end(),
                              vertNum) == otherVertexConnection.end())
                {
                    otherVertexConnection.push_back(vertNum);
                    ++m_numVertexConnections;
                }
            }
        }
        listIndex += vertexGroupSize;
    }
    
    tVertexConnectivity::iterator iterEnd = m_vertexConnectivity.end();
    for (tVertexConnectivity::iterator p = m_vertexConnectivity.begin();
         p != iterEnd; ++p)
    {
        std::sort(p->second.begin(), p->second.end());
    }  
    
    // Each connection counted twice (once from each end), so divide
    m_numVertexConnections /= 2;
    
    m_vertexConnectivityValid = true;
}

//%outOfLineFunctions {

const char *MushMesh4Face::AutoName(void) const
{
    return "MushMesh4Face";
}

MushcoreVirtualObject *MushMesh4Face::AutoClone(void) const
{
    return new MushMesh4Face(*this);
}

MushcoreVirtualObject *MushMesh4Face::AutoCreate(void) const
{
    return new MushMesh4Face;
}

MushcoreVirtualObject *MushMesh4Face::AutoVirtualFactory(void)
{
    return new MushMesh4Face;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushMesh4Face", MushMesh4Face::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushMesh4Face::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushMeshFace::AutoPrint(ioOut);
    ioOut << "faceType=" << m_faceType << ", ";
    ioOut << "vertexList=" << m_vertexList << ", ";
    ioOut << "vertexGroupSize=" << m_vertexGroupSize << ", ";
    ioOut << "texCoordList=" << m_texCoordList << ", ";
    ioOut << "materialNum=" << m_materialNum << ", ";
    ioOut << "edgeSmoothness=" << m_edgeSmoothness << ", ";
    ioOut << "internal=" << m_internal << ", ";
    ioOut << "extrusionMap=" << m_extrusionMap << ", ";
    ioOut << "extrudedFaces=" << m_extrudedFaces << ", ";
    ioOut << "extrusionTransformList=" << m_extrusionTransformList << ", ";
    ioOut << "uniqueVertexList=" << m_uniqueVertexList << ", ";
    ioOut << "faceCentroid=" << m_faceCentroid << ", ";
    ioOut << "boundingRadius=" << m_boundingRadius << ", ";
    ioOut << "faceConnectivity=" << m_faceConnectivity << ", ";
    ioOut << "vertexConnectivity=" << m_vertexConnectivity << ", ";
    ioOut << "uniqueVertexListValid=" << m_uniqueVertexListValid << ", ";
    ioOut << "faceCentroidValid=" << m_faceCentroidValid << ", ";
    ioOut << "boundingRadiusValid=" << m_boundingRadiusValid << ", ";
    ioOut << "faceConnectivityValid=" << m_faceConnectivityValid << ", ";
    ioOut << "vertexConnectivityValid=" << m_vertexConnectivityValid << ", ";
    ioOut << "numVertexConnections=" << m_numVertexConnections;
    ioOut << "]";
}
bool
MushMesh4Face::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "faceType")
    {
        ioIn >> m_faceType;
    }
    else if (inTagStr == "vertexList")
    {
        ioIn >> m_vertexList;
    }
    else if (inTagStr == "vertexGroupSize")
    {
        ioIn >> m_vertexGroupSize;
    }
    else if (inTagStr == "texCoordList")
    {
        ioIn >> m_texCoordList;
    }
    else if (inTagStr == "materialNum")
    {
        ioIn >> m_materialNum;
    }
    else if (inTagStr == "edgeSmoothness")
    {
        ioIn >> m_edgeSmoothness;
    }
    else if (inTagStr == "internal")
    {
        ioIn >> m_internal;
    }
    else if (inTagStr == "extrusionMap")
    {
        ioIn >> m_extrusionMap;
    }
    else if (inTagStr == "extrudedFaces")
    {
        ioIn >> m_extrudedFaces;
    }
    else if (inTagStr == "extrusionTransformList")
    {
        ioIn >> m_extrusionTransformList;
    }
    else if (inTagStr == "uniqueVertexList")
    {
        ioIn >> m_uniqueVertexList;
    }
    else if (inTagStr == "faceCentroid")
    {
        ioIn >> m_faceCentroid;
    }
    else if (inTagStr == "boundingRadius")
    {
        ioIn >> m_boundingRadius;
    }
    else if (inTagStr == "faceConnectivity")
    {
        ioIn >> m_faceConnectivity;
    }
    else if (inTagStr == "vertexConnectivity")
    {
        ioIn >> m_vertexConnectivity;
    }
    else if (inTagStr == "uniqueVertexListValid")
    {
        ioIn >> m_uniqueVertexListValid;
    }
    else if (inTagStr == "faceCentroidValid")
    {
        ioIn >> m_faceCentroidValid;
    }
    else if (inTagStr == "boundingRadiusValid")
    {
        ioIn >> m_boundingRadiusValid;
    }
    else if (inTagStr == "faceConnectivityValid")
    {
        ioIn >> m_faceConnectivityValid;
    }
    else if (inTagStr == "vertexConnectivityValid")
    {
        ioIn >> m_vertexConnectivityValid;
    }
    else if (inTagStr == "numVertexConnections")
    {
        ioIn >> m_numVertexConnections;
    }
    else if (MushMeshFace::AutoXMLDataProcess(ioIn, inTagStr))
    {
        // Tag consumed by base class
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushMesh4Face::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushMeshFace::AutoXMLPrint(ioOut);
    ioOut.TagSet("faceType");
    ioOut << m_faceType;
    ioOut.TagSet("vertexList");
    ioOut << m_vertexList;
    ioOut.TagSet("vertexGroupSize");
    ioOut << m_vertexGroupSize;
    ioOut.TagSet("texCoordList");
    ioOut << m_texCoordList;
    ioOut.TagSet("materialNum");
    ioOut << m_materialNum;
    ioOut.TagSet("edgeSmoothness");
    ioOut << m_edgeSmoothness;
    ioOut.TagSet("internal");
    ioOut << m_internal;
    ioOut.TagSet("extrusionMap");
    ioOut << m_extrusionMap;
    ioOut.TagSet("extrudedFaces");
    ioOut << m_extrudedFaces;
    ioOut.TagSet("extrusionTransformList");
    ioOut << m_extrusionTransformList;
    ioOut.TagSet("uniqueVertexList");
    ioOut << m_uniqueVertexList;
    ioOut.TagSet("faceCentroid");
    ioOut << m_faceCentroid;
    ioOut.TagSet("boundingRadius");
    ioOut << m_boundingRadius;
    ioOut.TagSet("faceConnectivity");
    ioOut << m_faceConnectivity;
    ioOut.TagSet("vertexConnectivity");
    ioOut << m_vertexConnectivity;
    ioOut.TagSet("uniqueVertexListValid");
    ioOut << m_uniqueVertexListValid;
    ioOut.TagSet("faceCentroidValid");
    ioOut << m_faceCentroidValid;
    ioOut.TagSet("boundingRadiusValid");
    ioOut << m_boundingRadiusValid;
    ioOut.TagSet("faceConnectivityValid");
    ioOut << m_faceConnectivityValid;
    ioOut.TagSet("vertexConnectivityValid");
    ioOut << m_vertexConnectivityValid;
    ioOut.TagSet("numVertexConnections");
    ioOut << m_numVertexConnections;
}
//%outOfLineFunctions } a9fTTBiJdyFWz2iy30PGPg
