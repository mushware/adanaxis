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
 * $Id$
 * $Log$
 */

#include "MushMesh4Face.h"

#include "MushMeshMushcoreIO.h"

MushMesh4Face::MushMesh4Face() :
    m_faceType(kFaceTypeNone),
    m_centroidValid(false),
    m_boundingRadiusValid(false)
{
}

MushMesh4Face::~MushMesh4Face()
{
}

void
MushMesh4Face::CentroidBuild(void) const
{
    m_centroidValid = true;
}

void
MushMesh4Face::BoundingRadiusBuild(void) const
{
    m_boundingRadiusValid = true;
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
    ioOut << "edgeSmoothness=" << m_edgeSmoothness;
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
}
//%outOfLineFunctions } mCGBGIxLSvWeuozc2tqBJA
