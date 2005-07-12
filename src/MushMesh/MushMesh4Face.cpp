//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMesh4Face.cpp
 *
 * Author: Andy Southgate 2002-2005
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
//%Header } zQQ0t0djv+gKXVED+/n+hw
/*
 * $Id: MushMesh4Face.cpp,v 1.3 2005/07/02 00:42:38 southa Exp $
 * $Log: MushMesh4Face.cpp,v $
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
    m_renderable(true)
{
    VerticesTouch();
}

MushMesh4Face::~MushMesh4Face()
{
}

void
MushMesh4Face::VerticesTouch(void)
{
    m_uniqueVertexListValid = false;
    m_faceCentroidValid = false;
    m_boundingRadiusValid = false;
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
    m_uniqueVertexListValid = true;
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
    ioOut << "faceMaterialRef=" << m_faceMaterialRef << ", ";
    ioOut << "edgeSmoothness=" << m_edgeSmoothness << ", ";
    ioOut << "renderable=" << m_renderable << ", ";
    ioOut << "uniqueVertexList=" << m_uniqueVertexList << ", ";
    ioOut << "faceCentroid=" << m_faceCentroid << ", ";
    ioOut << "boundingRadius=" << m_boundingRadius << ", ";
    ioOut << "uniqueVertexListValid=" << m_uniqueVertexListValid << ", ";
    ioOut << "faceCentroidValid=" << m_faceCentroidValid << ", ";
    ioOut << "boundingRadiusValid=" << m_boundingRadiusValid;
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
    else if (inTagStr == "faceMaterialRef")
    {
        ioIn >> m_faceMaterialRef;
    }
    else if (inTagStr == "edgeSmoothness")
    {
        ioIn >> m_edgeSmoothness;
    }
    else if (inTagStr == "renderable")
    {
        ioIn >> m_renderable;
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
    ioOut.TagSet("faceMaterialRef");
    ioOut << m_faceMaterialRef;
    ioOut.TagSet("edgeSmoothness");
    ioOut << m_edgeSmoothness;
    ioOut.TagSet("renderable");
    ioOut << m_renderable;
    ioOut.TagSet("uniqueVertexList");
    ioOut << m_uniqueVertexList;
    ioOut.TagSet("faceCentroid");
    ioOut << m_faceCentroid;
    ioOut.TagSet("boundingRadius");
    ioOut << m_boundingRadius;
    ioOut.TagSet("uniqueVertexListValid");
    ioOut << m_uniqueVertexListValid;
    ioOut.TagSet("faceCentroidValid");
    ioOut << m_faceCentroidValid;
    ioOut.TagSet("boundingRadiusValid");
    ioOut << m_boundingRadiusValid;
}
//%outOfLineFunctions } EuOWF9S0cHsxH/5vvhNW7w
