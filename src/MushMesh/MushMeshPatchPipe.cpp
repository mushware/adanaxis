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
    Touch();
    m_activeBox = t2BoxU32(t2U32(1,1), inArray.SizeGet() - 1);
    if (m_geometry.BaseGet().SizeGet() != inArray.SizeGet())
    {
        EdgeDefsGenerate();
    }
    m_geometry.BaseWRefGet() = inArray;
}


void
MushMeshPatchPipe::TexCoordSet(const tTexCoordArray& inArray, Mushware::U32 inIndex)
{
    Touch();
    if (m_texCoords.BaseWRefGet().size() <= inIndex)
    {
        m_texCoords.BaseWRefGet().resize(inIndex + 1);
    }
    m_texCoords.BaseWRefGet()[inIndex] = inArray;
}

void
MushMeshPatchPipe::EdgeDefsGenerate(void)
{
    m_edgeDefs.resize(MushMeshPatch::kNumEdgeSelectors);

    m_edgeDefs[kEdgeLeft].start = m_activeBox.StartGet();
    m_edgeDefs[kEdgeLeft].stride = t2U32(1, 0);
    m_edgeDefs[kEdgeLeft].size = m_activeBox.SizeGet().Y();

    m_edgeDefs[kEdgeRight].start = t2U32(m_activeBox.EndGet().X() - 1, m_activeBox.StartGet().Y());
    m_edgeDefs[kEdgeRight].stride = t2U32(1, 0);
    m_edgeDefs[kEdgeRight].size = m_activeBox.SizeGet().Y();

    m_edgeDefs[kEdgeBottom].start = m_activeBox.StartGet();
    m_edgeDefs[kEdgeBottom].stride = t2U32(0, 1);
    m_edgeDefs[kEdgeBottom].size = m_activeBox.SizeGet().X();

    m_edgeDefs[kEdgeTop].start = t2U32(m_activeBox.StartGet().X(), m_activeBox.EndGet().Y() - 1);
    m_edgeDefs[kEdgeTop].stride = t2U32(0, 1);
    m_edgeDefs[kEdgeTop].size = m_activeBox.SizeGet().X();

    m_edgeDefs[kPointBottomLeft].start = m_activeBox.StartGet();
    m_edgeDefs[kPointBottomLeft].stride = t2U32(0, 0);
    m_edgeDefs[kPointBottomLeft].size = 1;

    m_edgeDefs[kPointBottomRight].start = t2U32(m_activeBox.EndGet().X() - 1, m_activeBox.StartGet().Y());
    m_edgeDefs[kPointBottomRight].stride = t2U32(0, 0);
    m_edgeDefs[kPointBottomRight].size = 1;

    m_edgeDefs[kPointTopLeft].start = t2U32(m_activeBox.StartGet().X(), m_activeBox.EndGet().Y() - 1);
    m_edgeDefs[kPointTopLeft].stride = t2U32(0, 0);
    m_edgeDefs[kPointTopLeft].size = 1;

    m_edgeDefs[kPointTopRight].start = m_activeBox.EndGet() - t2U32(1, 1);
    m_edgeDefs[kPointTopRight].stride = t2U32(0, 0);
    m_edgeDefs[kPointTopRight].size = 1;

    
    m_neighbourDefs.resize(MushMeshPatch::kNumEdgeSelectors);

    m_neighbourDefs[kEdgeLeft].start = m_activeBox.StartGet() - t2U32(1, 0);
    m_neighbourDefs[kEdgeLeft].stride = t2U32(1, 0);
    m_neighbourDefs[kEdgeLeft].size = m_activeBox.SizeGet().Y();

    m_neighbourDefs[kEdgeRight].start = t2U32(m_activeBox.EndGet().X(), m_activeBox.StartGet().Y());
    m_neighbourDefs[kEdgeRight].stride = t2U32(1, 0);
    m_neighbourDefs[kEdgeRight].size = m_activeBox.SizeGet().Y();

    m_neighbourDefs[kEdgeBottom].start = m_activeBox.StartGet() - t2U32(0, 1);
    m_neighbourDefs[kEdgeBottom].stride = t2U32(0, 1);
    m_neighbourDefs[kEdgeBottom].size = m_activeBox.SizeGet().X();

    m_neighbourDefs[kEdgeTop].start = t2U32(m_activeBox.StartGet().X(), m_activeBox.EndGet().Y());
    m_neighbourDefs[kEdgeTop].stride = t2U32(0, 1);
    m_neighbourDefs[kEdgeTop].size = m_activeBox.SizeGet().X();

    m_neighbourDefs[kPointBottomLeft].start = m_activeBox.StartGet() - t2U32(1, 1);
    m_neighbourDefs[kPointBottomLeft].stride = t2U32(0, 0);
    m_neighbourDefs[kPointBottomLeft].size = 1;

    m_neighbourDefs[kPointBottomRight].start = t2U32(m_activeBox.EndGet().X(), m_activeBox.StartGet().Y() - 1);
    m_neighbourDefs[kPointBottomRight].stride = t2U32(0, 0);
    m_neighbourDefs[kPointBottomRight].size = 1;

    m_neighbourDefs[kPointTopLeft].start = t2U32(m_activeBox.StartGet().X() - 1, m_activeBox.EndGet().Y());
    m_neighbourDefs[kPointTopLeft].stride = t2U32(0, 0);
    m_neighbourDefs[kPointTopLeft].size = 1;

    m_neighbourDefs[kPointTopRight].start = m_activeBox.EndGet();
    m_neighbourDefs[kPointTopRight].stride = t2U32(0, 0);
    m_neighbourDefs[kPointTopRight].size = 1;
}

void
MushMeshPatchPipe::EdgeGet(MushMeshStitchable& outStitchable, tEdgeSelector inEdge)
{
    MUSHCOREASSERT(inEdge < kNumEdgeSelectors);
    outStitchable.SourceSet(&m_geometry.BaseGet(), &m_texCoords.BaseGet(), &m_activeBox);
    outStitchable.SelectionSet(m_edgeDefs[inEdge]);
}

void
MushMeshPatchPipe::NeighbourSet(const MushMeshStitchable& inStitchable, tEdgeSelector inEdge)
{

}

void
MushMeshPatchPipe::Subdivide(tVal inLevel)
{
    // FIXME: need to copy active box area only
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
    ioOut << "activeBox=" << m_activeBox << ", ";
    ioOut << "edgeDefs=" << m_edgeDefs << ", ";
    ioOut << "neighbourDefs=" << m_neighbourDefs;
    ioOut << "]";
}
//%outOfLineFunctions } UOFgRhr8RwHtroH0O4fFxg
