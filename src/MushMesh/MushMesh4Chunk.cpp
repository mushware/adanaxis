//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMesh4Chunk.cpp
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
//%Header } FaZzlC8FBT0ByV0McMoFjQ
/*
 * $Id: MushMesh4Chunk.cpp,v 1.1 2005/07/19 13:44:26 southa Exp $
 * $Log: MushMesh4Chunk.cpp,v $
 * Revision 1.1  2005/07/19 13:44:26  southa
 * MushMesh4Chunk work
 *
 */

#include "MushMesh4Chunk.h"

#include "MushMeshMushcoreIO.h"

MushMesh4Chunk::MushMesh4Chunk() :
    m_boundingType(0)
{
    AllTouch();
}

void
MushMesh4Chunk::VerticesTouch(void)
{
    m_uniqueVertexListValid = false;
    m_boundingRadiusValid = false;
    m_centroidValid = false;
}

void
MushMesh4Chunk::AllTouch(void)
{
    VerticesTouch();
}
//%outOfLineFunctions {

const char *MushMesh4Chunk::AutoName(void) const
{
    return "MushMesh4Chunk";
}

MushcoreVirtualObject *MushMesh4Chunk::AutoClone(void) const
{
    return new MushMesh4Chunk(*this);
}

MushcoreVirtualObject *MushMesh4Chunk::AutoCreate(void) const
{
    return new MushMesh4Chunk;
}

MushcoreVirtualObject *MushMesh4Chunk::AutoVirtualFactory(void)
{
    return new MushMesh4Chunk;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushMesh4Chunk", MushMesh4Chunk::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushMesh4Chunk::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "boundingType=" << m_boundingType << ", ";
    ioOut << "faceList=" << m_faceList << ", ";
    ioOut << "uniqueVertexList=" << m_uniqueVertexList << ", ";
    ioOut << "boundingRadius=" << m_boundingRadius << ", ";
    ioOut << "centroid=" << m_centroid << ", ";
    ioOut << "uniqueVertexListValid=" << m_uniqueVertexListValid << ", ";
    ioOut << "boundingRadiusValid=" << m_boundingRadiusValid << ", ";
    ioOut << "centroidValid=" << m_centroidValid;
    ioOut << "]";
}
bool
MushMesh4Chunk::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "boundingType")
    {
        ioIn >> m_boundingType;
    }
    else if (inTagStr == "faceList")
    {
        ioIn >> m_faceList;
    }
    else if (inTagStr == "uniqueVertexList")
    {
        ioIn >> m_uniqueVertexList;
    }
    else if (inTagStr == "boundingRadius")
    {
        ioIn >> m_boundingRadius;
    }
    else if (inTagStr == "centroid")
    {
        ioIn >> m_centroid;
    }
    else if (inTagStr == "uniqueVertexListValid")
    {
        ioIn >> m_uniqueVertexListValid;
    }
    else if (inTagStr == "boundingRadiusValid")
    {
        ioIn >> m_boundingRadiusValid;
    }
    else if (inTagStr == "centroidValid")
    {
        ioIn >> m_centroidValid;
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushMesh4Chunk::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("boundingType");
    ioOut << m_boundingType;
    ioOut.TagSet("faceList");
    ioOut << m_faceList;
    ioOut.TagSet("uniqueVertexList");
    ioOut << m_uniqueVertexList;
    ioOut.TagSet("boundingRadius");
    ioOut << m_boundingRadius;
    ioOut.TagSet("centroid");
    ioOut << m_centroid;
    ioOut.TagSet("uniqueVertexListValid");
    ioOut << m_uniqueVertexListValid;
    ioOut.TagSet("boundingRadiusValid");
    ioOut << m_boundingRadiusValid;
    ioOut.TagSet("centroidValid");
    ioOut << m_centroidValid;
}
//%outOfLineFunctions } XmdzZodYZka0S1FiAq/wpQ
