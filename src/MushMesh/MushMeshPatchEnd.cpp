//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshPatchEnd.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } qDq5YKmhlGfUEBa+UIK6Fw


#include "MushMeshPatchEnd.h"

#include "MushMeshMushcoreIO.h"
#include "MushMeshSTL.h"
#include "MushMeshSubdivide.h"


using namespace Mushware;
using namespace std;

void
MushMeshPatchEnd::OrderSet(U32 inOrder)
{
    if (inOrder < 2)
    {
        throw MushcoreDataFail("MushMeshPatchEnd order cannot be less than 2");
    }
    
    m_order = inOrder;
}

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
    m_activeBox = t2BoxU32(t2U32(0,0), inArray.SizeGet() - t2U32(1, 0));

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
MushMeshPatchEnd::NeighbourSelectionGet(MushMeshSelection& outSelection, tEdgeSelector inEdge)
{
    switch  (inEdge)
    {   
    case kEdgeRight:
        outSelection.start = t2U32(m_activeBox.EndGet().X(), m_activeBox.StartGet().Y());
        outSelection.stride = t2U32(0, 1);
        outSelection.size = m_activeBox.SizeGet().Y();
        break;
        

    case kPointBottomRight:
    case kPointTopRight:
        // Silently ignore these
        outSelection.size = 0;
        break;

    default:
        throw MushcoreDataFail("Only kEdgeRight, kPointBottomLeft and kPointBottomRight are valid PatchEnd edges");        
    }
}

void
MushMeshPatchEnd::EdgeStitchableGet(MushMeshStitchable& outStitchable, tEdgeSelector inEdge)
{
    MUSHCOREASSERT(inEdge < kNumEdgeSelectors);
    outStitchable.SourceSet(&m_geometry.BaseGet(), &m_texCoords.BaseGet(), &m_activeBox);

    MushMeshSelection selection;
    
    switch (inEdge)
    {        
    case kEdgeRight:
        selection.start = t2U32(m_activeBox.EndGet().X() - 2, m_activeBox.StartGet().Y());
        selection.stride = t2U32(0, 1);
        selection.size = m_activeBox.SizeGet().Y();
        break;
        
    case kPointBottomRight:
        // Points wrap around, so this is the top right data point
        selection.start = m_activeBox.EndGet() - t2U32(2, 1);
        selection.stride = t2U32(0, 0);
        selection.size = 1;
        break;
        
    case kPointTopRight:
        // Points wrap around, so this is the bottom right data point
        selection.start = t2U32(m_activeBox.EndGet().X() - 2, m_activeBox.StartGet().Y());
        selection.stride = t2U32(0, 0);
        selection.size = 1;
        break;
        
    default:
        throw MushcoreDataFail("Only kEdgeRight, kPointBottomLeft and kPointBottomRight are valid PatchEnd neighbours");
        
    }
    outStitchable.SelectionSet(selection);
}

void
MushMeshPatchEnd::NeighbourSet(const MushMeshStitchable& inStitchable, tEdgeSelector inEdge)
{
    MUSHCOREASSERT(inEdge < kNumEdgeSelectors);
    MushMeshSelection neighbourSelection;
    NeighbourSelectionGet(neighbourSelection, inEdge);

    U32 size = neighbourSelection.size;
    if (size > 0)
    {
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
        t2U32 writePos = neighbourSelection.start;
        t2U32 readStride = inStitchable.SelectionGet().stride;
        t2U32 writeStride = neighbourSelection.stride;
        
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
}

void
MushMeshPatchEnd::Subdivide(tVal inLevel)
{
    if (m_order < 3)
    {
        throw MushcoreLogicFail("Attempt to subdivide end patch without setting order");
    }
    
    // FIXME: need to copy active box area only
    m_geometry.BaseToCurrentCopy();

    for (tVal level=0; level <= inLevel; ++level)
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
            m_order,
            proportion);

        m_texCoords.Swap();
        for (U32 i=0; i<m_texCoords.BaseGet().size(); ++i)
        {
            MushMeshSubdivide<tTexCoordVector>::TriangularSubdivide(
                m_texCoords.CurrentWRefGet()[i],
                m_texCoords.PreviousGet()[i],
                m_activeBox,
                m_order,
                proportion);
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
