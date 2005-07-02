//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMesh4Library.cpp
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
//%Header } U7p/xUoHUXuIfNSiEWFaVQ
/*
 * $Id: MushMesh4Library.cpp,v 1.1 2005/06/30 12:04:55 southa Exp $
 * $Log: MushMesh4Library.cpp,v $
 * Revision 1.1  2005/06/30 12:04:55  southa
 * Mesh work
 *
 */

#include "MushMesh4Library.h"

using namespace Mushware;
using namespace std;

MUSHCORE_SINGLETON_INSTANCE(MushMesh4Library);

void
MushMesh4Library::UnitTesseractCreate(MushMesh4Mesh& outMesh) const
{
    tVal scale = 0.5;

    MushMesh4Mesh::tVertices& verticesRef = outMesh.VerticesWRef();
    MushMesh4Mesh::tFaces& facesRef = outMesh.FacesWRef();
    
    // Vertices
    for (U32 i=0; i<16; ++i)
    {
        verticesRef.push_back(MushMesh4Mesh::tVertex());
        MushMesh4Mesh::tVertex& vertex = verticesRef.back();
        
        vertex.XSet(((i & 1) == 0)?-scale:scale);
        vertex.YSet(((i & 2) == 0)?-scale:scale);
        vertex.ZSet(((i & 4) == 0)?-scale:scale);
        vertex.WSet(((i & 8) == 0)?-scale:scale);
    }

    U32 fixedAxis = 8;
    
    // Faces
    for (U32 i=0; i<8 && fixedAxis > 0; ++i)
    {
        facesRef.push_back(MushMesh4Mesh::tFace());
        MushMesh4Mesh::tFace& face = facesRef.back();

        MushMesh4Mesh::tFace::tVertexList& vertexList = face.VertexListWRef();
        MushMesh4Mesh::tFace::tVertexGroupSize& vertexGroupSize = face.VertexGroupSizeWRef();
        
        // fixedAxis: 1->x, 2->y, 4->z, 8->w
        
        // fixedAxisOffset: 0->fixed to -scale, fixedAxis->fixed to +scale
        U32 fixedAxisOffset;
        if ((i % 2) == 1)
        {
            fixedAxisOffset = 0;
        }
        else
        {
            fixedAxisOffset = fixedAxis;
        }

        /* The vertex set for each face is determined by fixing one value
         * x,y,z or w at -scale or +scale. Sets for w=-scale are
         * xy,z=-scale 0,1,3,2
         * xz,y=-scale 0,1,5,4
         * yz,x=-scale 0,2,6,4
         * xy,z=+scale 4,5,7,6
         * xz,y=+scale 2,3,7,6
         * yz,x=+scale 1,3,7,5
         * Face normal will be defined by 0, 1, 3, 4, i.e. the two vertices
         * on either side of 0, and the replacment for 0 in the next facet
         */
        
        U32 planeAxis = 8;

        // Facets
        for (U32 j=0; j<6; ++j)
        {
            if (planeAxis == fixedAxis)
            {
                MUSHCOREASSERT(fixedAxis > 0 && planeAxis > 0);
                planeAxis /= 2;
            }
            
            U32 planeAxisOffset;
            if ((j % 2) == 1)
            {
                planeAxisOffset = 0;
            }
            else
            {
                planeAxisOffset = planeAxis;
            }
            
            U32 lowAxis = 1;
            while (lowAxis == fixedAxis || lowAxis == planeAxis)
            {
                lowAxis *= 2;
            }
            
            U32 highAxis = lowAxis * 2;
            while (highAxis == fixedAxis || highAxis == planeAxis)
            {
                highAxis *= 2;
            }
            
            U32 baseOffset = fixedAxisOffset + planeAxisOffset;
            
            vertexList.push_back(baseOffset);
            vertexList.push_back(baseOffset + lowAxis);
            vertexList.push_back(baseOffset + lowAxis + highAxis);
            vertexList.push_back(baseOffset + highAxis);
            
            vertexGroupSize.push_back(4);

            if ((j % 2) == 1)
            {
                planeAxis /= 2;
            }
        }
        if ((i % 2) == 1)
        {
            fixedAxis /= 2;
        }
    }
}

//%outOfLineFunctions {

const char *MushMesh4Library::AutoName(void) const
{
    return "MushMesh4Library";
}

MushcoreVirtualObject *MushMesh4Library::AutoClone(void) const
{
    return new MushMesh4Library(*this);
}

MushcoreVirtualObject *MushMesh4Library::AutoCreate(void) const
{
    return new MushMesh4Library;
}

MushcoreVirtualObject *MushMesh4Library::AutoVirtualFactory(void)
{
    return new MushMesh4Library;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushMesh4Library", MushMesh4Library::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushMesh4Library::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "]";
}
bool
MushMesh4Library::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushMesh4Library::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
}
//%outOfLineFunctions } 46bunZr3mWoIQD27zj9fyw
