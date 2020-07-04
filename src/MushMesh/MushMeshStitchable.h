//%includeGuardStart {
#ifndef MUSHMESHSTITCHABLE_H
#define MUSHMESHSTITCHABLE_H
//%includeGuardStart } aYdUXjykoRCdCOUILW3tHg
//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshStitchable.h
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
//%Header } 3YaFJSTT6P9glkYxaU16Kw
/*
 * $Id: MushMeshStitchable.h,v 1.11 2006/06/01 15:39:32 southa Exp $
 * $Log: MushMeshStitchable.h,v $
 * Revision 1.11  2006/06/01 15:39:32  southa
 * DrawArray verification and fixes
 *
 * Revision 1.10  2005/08/01 17:58:25  southa
 * Object explosion
 *
 * Revision 1.9  2005/07/02 00:42:38  southa
 * Conditioning tweaks
 *
 * Revision 1.8  2005/06/30 12:34:59  southa
 * Mesh and source conditioner work
 *
 * Revision 1.7  2005/05/19 13:02:11  southa
 * Mac release work
 *
 * Revision 1.6  2005/02/10 12:34:07  southa
 * Template fixes
 *
 * Revision 1.5  2004/09/27 22:42:09  southa
 * MSVC compilation fixes
 *
 * Revision 1.4  2004/01/02 21:13:11  southa
 * Source conditioning
 *
 * Revision 1.3  2003/10/20 13:02:54  southa
 * Patch fixes and testing
 *
 * Revision 1.2  2003/10/19 15:59:34  southa
 * Edge manipulation
 *
 * Revision 1.1  2003/10/19 12:41:42  southa
 * Connectors
 *
 */

#include "MushMeshStandard.h"

#include "MushMeshBox.h"
#include "MushMeshPatchTypes.h"
#include "MushMeshSelection.h"

//:generate nonvirtual ostream
class MushMeshStitchable
{
public:
    MushMeshStitchable();

    const Mushware::tGeometryArray& GeometryGet(void) const { MUSHCOREASSERT(m_pGeometry != NULL); return *m_pGeometry; } 
    const Mushware::tTexCoordArrayVector& TexCoordGet(void) const { MUSHCOREASSERT(m_pTexVector != NULL); return *m_pTexVector; } 
    const MushMeshSelection& SelectionGet() const { return m_selection; }

    void SourceSet(const Mushware::tGeometryArray *inpGeometry,
        const Mushware::tTexCoordArrayVector *inpTexVector,
        const Mushware::t2BoxU32 *inpActiveBox)
    {
         m_pGeometry = inpGeometry;
         m_pTexVector = inpTexVector;
         m_pActiveBox = inpActiveBox;
    }
    void SelectionSet(const MushMeshSelection& inSelection) { m_selection = inSelection; }

private:
    const Mushware::tGeometryArray *m_pGeometry;
    const Mushware::tTexCoordArrayVector *m_pTexVector; //:ignore
    const Mushware::t2BoxU32 *m_pActiveBox;
    MushMeshSelection m_selection;
//%classPrototypes {
public:
    void AutoPrint(std::ostream& ioOut) const;
//%classPrototypes } igNZsqh+Ffme42HZCDZW6Q
};

inline
MushMeshStitchable::MushMeshStitchable() :
    m_pGeometry(NULL),
    m_pTexVector(NULL),
    m_pActiveBox(NULL)
{
}
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushMeshStitchable& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } Wx3nk1y5jLk1s+0OauoKGQ

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
