//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshPatchPipe.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } BLqXz2QPeS3u0FChdbo3Ow


#include "MushMeshPatchPipe.h"

#include "MushMeshSubdivide.h"

using namespace Mushware;
using namespace std;

void
MushMeshPatchPipe::GeometrySet(const tGeometryArray& inArray)
{
    m_geometry.BaseWRefGet() = inArray;
}


void
MushMeshPatchPipe::TexCoordSet(const tTexCoordArray& inArray, Mushware::U32 inIndex)
{
    if (m_texCoords.BaseWRefGet().size() <= inIndex)
    {
        m_texCoords.BaseWRefGet().resize(inIndex + 1);
    }
    m_texCoords.BaseWRefGet()[inIndex] = inArray;
}

void
MushMeshPatchPipe::Subdivide(tVal inLevel)
{
    m_geometry.BaseToCurrentCopy();

    for (tVal level=0; level + 0.001 < inLevel; ++level)
    {
        tVal proportion = inLevel - level;

        if (proportion > 1)
        {
            proportion = 1;
        }

        m_geometry.Swap();
        MushMeshSubdivide<tGeometryVector>::RectangularSubdivide(
            m_geometry.CurrentWRefGet(),
            m_geometry.PreviousWRefGet(),
            m_activeBox,
            proportion);

        // ActiveBoxDouble();
    }
}



//%outOfLineFunctions {
void
MushMeshPatchPipe::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "geometry=" << m_geometry << ", ";
    ioOut << "texCoords=" << m_texCoords << ", ";
    ioOut << "activeBox=" << m_activeBox;
    ioOut << "]";
}
//%outOfLineFunctions } HCMAhtac7LvUejyKlxdzqA
