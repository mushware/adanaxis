//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshPatchPipe.cpp
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
//%Header } Vx3dzf+yD9Puv/aYy6g3GQ


#include "MushMeshPatchPipe.h"

#include "MushMeshMushcoreIO.h"
#include "MushMeshSTL.h"
#include "MushMeshSubdivide.h"


using namespace Mushware;
using namespace std;

const Mushware::tGeometryArray&
MushMeshPatchPipe::GeometryGet(void)
{
    return m_geometry.BaseGet();
}

void
MushMeshPatchPipe::GeometrySet(const tGeometryArray& inArray)
{
    Touch();
    StorageTouch();
    m_activeBox = t2BoxU32(t2U32(1,1), inArray.SizeGet() - 1);

    m_geometry.BaseWRefGet() = inArray;
}

const Mushware::tTexCoordArray&
MushMeshPatchPipe::TexCoordGet(Mushware::U32 inIndex)
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
MushMeshPatchPipe::TexCoordSet(const tTexCoordArray& inArray, Mushware::U32 inIndex)
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
MushMeshPatchPipe::NeighbourSelectionGet(MushMeshSelection& outSelection, tEdgeSelector inEdge)
{
    switch  (inEdge)
    {
    case kEdgeLeft:
        outSelection.start = m_activeBox.Start() - t2U32(1, 0);
        outSelection.stride = t2U32(0, 1);
        outSelection.size = m_activeBox.SizeGet().Y();
        break;
        
    case kEdgeRight:
        outSelection.start = t2U32(m_activeBox.End().X(), m_activeBox.Start().Y());
        outSelection.stride = t2U32(0, 1);
        outSelection.size = m_activeBox.SizeGet().Y();
        break;
        
    case kEdgeBottom: outSelection.start = m_activeBox.Start() - t2U32(0, 1);
        outSelection.stride = t2U32(1, 0);
        outSelection.size = m_activeBox.SizeGet().X();
        break;
        
    case kEdgeTop:
        outSelection.start = t2U32(m_activeBox.Start().X(), m_activeBox.End().Y());
        outSelection.stride = t2U32(1, 0);
        outSelection.size = m_activeBox.SizeGet().X();
        break;
        
    case kPointBottomLeft:
        outSelection.start = m_activeBox.Start() - t2U32(1, 1);
        outSelection.stride = t2U32(0, 0);
        outSelection.size = 1;
        break;
        
    case kPointBottomRight:
        outSelection.start = t2U32(m_activeBox.End().X(), m_activeBox.Start().Y() - 1);
        outSelection.stride = t2U32(0, 0);
        outSelection.size = 1;
        break;
        
    case kPointTopLeft:
        outSelection.start = t2U32(m_activeBox.Start().X() - 1, m_activeBox.End().Y());
        outSelection.stride = t2U32(0, 0);
        outSelection.size = 1;
        break;
        
    case kPointTopRight:
        outSelection.start = m_activeBox.End();
        outSelection.stride = t2U32(0, 0);
        outSelection.size = 1;
        break;
        
    default:
        throw MushcoreDataFail("Bad edge value");        
    }
}

void
MushMeshPatchPipe::EdgeStitchableGet(MushMeshStitchable& outStitchable, tEdgeSelector inEdge)
{
    MUSHCOREASSERT(inEdge < kNumEdgeSelectors);
    outStitchable.SourceSet(&m_geometry.BaseGet(), &m_texCoords.BaseGet(), &m_activeBox);

    MushMeshSelection selection;
    
    switch (inEdge)
    {
    case kEdgeLeft:
        selection.start = m_activeBox.Start() + t2U32(1, 0);
        selection.stride = t2U32(0, 1);
        selection.size = m_activeBox.SizeGet().Y();
        break;
        
    case kEdgeRight:
        selection.start = t2U32(m_activeBox.End().X() - 2, m_activeBox.Start().Y());
        selection.stride = t2U32(0, 1);
        selection.size = m_activeBox.SizeGet().Y();
        break;
        
    case kEdgeBottom:
        selection.start = m_activeBox.Start() + t2U32(0, 1);
        selection.stride = t2U32(1, 0);
        selection.size = m_activeBox.SizeGet().X();
        break;
        
    case kEdgeTop:
        selection.start = t2U32(m_activeBox.Start().X(), m_activeBox.End().Y() - 2);
        selection.stride = t2U32(1, 0);
        selection.size = m_activeBox.SizeGet().X();
        break;
        
    case kPointBottomLeft:
        selection.start = m_activeBox.Start() + t2U32(1,1);
        selection.stride = t2U32(0, 0);
        selection.size = 1;
        break;

    case kPointBottomRight:
        selection.start = t2U32(m_activeBox.End().X() - 2, m_activeBox.Start().Y() + 1);
        selection.stride = t2U32(0, 0);
        selection.size = 1;
        break;
        
    case kPointTopLeft:
        selection.start = t2U32(m_activeBox.Start().X() + 1, m_activeBox.End().Y() - 2);
        selection.stride = t2U32(0, 0);
        selection.size = 1;
        break;
        
    case kPointTopRight:
        selection.start = m_activeBox.End() - t2U32(2, 2);
        selection.stride = t2U32(0, 0);
        selection.size = 1;
        break;
        
    default:
        throw MushcoreDataFail("Bad edge value");
        
    }
    outStitchable.SelectionSet(selection);
}

void
MushMeshPatchPipe::NeighbourSet(const MushMeshStitchable& inStitchable, tEdgeSelector inEdge)
{
    MUSHCOREASSERT(inEdge < kNumEdgeSelectors);
    MushMeshSelection neighbourSelection;
    NeighbourSelectionGet(neighbourSelection, inEdge);

    U32 size = neighbourSelection.size;
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

void
MushMeshPatchPipe::Subdivide(tVal inLevel)
{
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
        MushMeshSubdivide<tGeometryVector>::RectangularSubdivide(
            m_geometry.CurrentWRefGet(),
            m_geometry.PreviousGet(),
            m_activeBox,
            proportion);

        m_texCoords.Swap();
        for (U32 i=0; i<m_texCoords.BaseGet().size(); ++i)
        {
            MushMeshSubdivide<tTexCoordVector>::RectangularSubdivide(
                m_texCoords.CurrentWRefGet()[i],
                m_texCoords.PreviousGet()[i],
                m_activeBox,
                proportion);
        }
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
