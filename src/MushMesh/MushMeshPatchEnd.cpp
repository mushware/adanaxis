//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshPatchEnd.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } koaMdD8Sbr37+5s2etXK8Q


#include "MushMeshPatchEnd.h"

#include "MushMeshSTL.h"
#include "MushMeshSubdivide.h"


using namespace Mushware;
using namespace std;

const Mushware::tGeometryArray&
MushMeshPatchEnd::GeometryGet(void)
{
    return m_geometry.BaseGet();
}

void
MushMeshPatchEnd::GeometrySet(const tGeometryArray& inArray)
{
    Touch();
    StorageTouch();
    m_activeBox = t2BoxU32(t2U32(1,1), inArray.SizeGet() - 1);
    if (m_geometry.BaseGet().SizeGet() != inArray.SizeGet())
    {
        EdgeDefsGenerate();
    }

    m_geometry.BaseWRefGet() = inArray;
}

const Mushware::tTexCoordArray&
MushMeshPatchEnd::TexCoordGet(Mushware::U32 inIndex)
{
    if (inIndex >= m_texCoords.BaseGet().size())
    {
        ostringstream message;
        message << "TexCoordGet index too high (" << inIndex << " >= " << m_texCoords.BaseWRefGet().size() << ")";
        throw MushcoreReferenceFail(message.str());
    }
    return m_texCoords.BaseGet()[inIndex];
}


void
MushMeshPatchEnd::TexCoordSet(const tTexCoordArray& inArray, Mushware::U32 inIndex)
{
    Touch();
    StorageTouch();
    if (m_texCoords.BaseWRefGet().size() <= inIndex)
    {
        m_texCoords.BaseWRefGet().resize(inIndex + 1);
    }

    m_texCoords.BaseWRefGet()[inIndex] = inArray;
}

void
MushMeshPatchEnd::EdgeDefsGenerate(void)
{
    /* This lot needs storing centrally, but calculate for each patch for now.
     * It's about 320 bytes
     *
     * Don't really need this optimisation.  Edge definition fetches are rare
     */
    m_edgeDefs.resize(MushMeshPatch::kNumEdgeSelectors);

    m_edgeDefs[kEdgeLeft].start = m_activeBox.StartGet();
    m_edgeDefs[kEdgeLeft].stride = t2U32(0, 1);
    m_edgeDefs[kEdgeLeft].size = m_activeBox.SizeGet().Y();

    m_edgeDefs[kEdgeRight].start = t2U32(m_activeBox.EndGet().X() - 1, m_activeBox.StartGet().Y());
    m_edgeDefs[kEdgeRight].stride = t2U32(0, 1);
    m_edgeDefs[kEdgeRight].size = m_activeBox.SizeGet().Y();

    m_edgeDefs[kEdgeBottom].start = m_activeBox.StartGet();
    m_edgeDefs[kEdgeBottom].stride = t2U32(1, 0);
    m_edgeDefs[kEdgeBottom].size = m_activeBox.SizeGet().X();

    m_edgeDefs[kEdgeTop].start = t2U32(m_activeBox.StartGet().X(), m_activeBox.EndGet().Y() - 1);
    m_edgeDefs[kEdgeTop].stride = t2U32(1, 0);
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
    m_neighbourDefs[kEdgeLeft].stride = t2U32(0, 1);
    m_neighbourDefs[kEdgeLeft].size = m_activeBox.SizeGet().Y();

    m_neighbourDefs[kEdgeRight].start = t2U32(m_activeBox.EndGet().X(), m_activeBox.StartGet().Y());
    m_neighbourDefs[kEdgeRight].stride = t2U32(0, 1);
    m_neighbourDefs[kEdgeRight].size = m_activeBox.SizeGet().Y();

    m_neighbourDefs[kEdgeBottom].start = m_activeBox.StartGet() - t2U32(0, 1);
    m_neighbourDefs[kEdgeBottom].stride = t2U32(1, 0);
    m_neighbourDefs[kEdgeBottom].size = m_activeBox.SizeGet().X();

    m_neighbourDefs[kEdgeTop].start = t2U32(m_activeBox.StartGet().X(), m_activeBox.EndGet().Y());
    m_neighbourDefs[kEdgeTop].stride = t2U32(1, 0);
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
MushMeshPatchEnd::EdgeGet(MushMeshStitchable& outStitchable, tEdgeSelector inEdge)
{
    MUSHCOREASSERT(inEdge < kNumEdgeSelectors);
    outStitchable.SourceSet(&m_geometry.BaseGet(), &m_texCoords.BaseGet(), &m_activeBox);
    outStitchable.SelectionSet(m_edgeDefs[inEdge]);
}

void
MushMeshPatchEnd::NeighbourSet(const MushMeshStitchable& inStitchable, tEdgeSelector inEdge)
{
    MUSHCOREASSERT(inEdge < kNumEdgeSelectors);
    U32 size = m_neighbourDefs[inEdge].size;
    if (size != inStitchable.SelectionGet().size)
    {
        throw MushcoreDataFail("Different edge sizes in connected patches");
    }
    U32 numTextures = inStitchable.TexCoordGet().size();
    if (numTextures != m_texCoords.BaseGet().size())
    {
        throw MushcoreDataFail("Different number of textures in connected patches");
    }

    t2U32 readPos = inStitchable.SelectionGet().start;
    t2U32 writePos = m_neighbourDefs[inEdge].start;
    t2U32 readStride = inStitchable.SelectionGet().stride;
    t2U32 writeStride = m_neighbourDefs[inEdge].stride;

    for (U32 i=0; i<size; ++i)
    {
        m_geometry.BaseWRefGet().Set(inStitchable.GeometryGet().Get(readPos), writePos);
        for (U32 j=0; j<numTextures; ++j)
        {
            m_texCoords.BaseWRefGet()[j].Set(inStitchable.TexCoordGet()[j].Get(readPos), writePos);
        }
        readPos += readStride;
        writePos += writeStride;
    }
}

void
MushMeshPatchEnd::Subdivide(tVal inLevel)
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
        MushMeshSubdivide<tGeometryVector>::TriangularSubdivide(
            m_geometry.CurrentWRefGet(),
            m_geometry.PreviousGet(),
            m_activeBox,
            proportion,
            m_order);

        m_texCoords.Swap();
        for (U32 i=0; i<m_texCoords.BaseGet().size(); ++i)
        {
            MushMeshSubdivide<tTexCoordVector>::TriangularSubdivide(
                m_texCoords.CurrentWRefGet()[i],
                m_texCoords.PreviousGet()[i],
                m_activeBox,
                proportion,
                m_order);
        }
    }
}

//%outOfLineFunctions {
void
MushMeshPatchEnd::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "geometry=" << m_geometry << ", ";
    ioOut << "texCoords=" << m_texCoords << ", ";
    ioOut << "activeBox=" << m_activeBox << ", ";
    ioOut << "order=" << m_order << ", ";
    ioOut << "edgeDefs=" << m_edgeDefs << ", ";
    ioOut << "neighbourDefs=" << m_neighbourDefs;
    ioOut << "]";
}
//%outOfLineFunctions } ys6Tm/G/NVjeFJ62/Lps4Q
