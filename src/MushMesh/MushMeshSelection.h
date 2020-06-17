//%includeGuardStart {
#ifndef MUSHMESHSELECTION_H
#define MUSHMESHSELECTION_H
//%includeGuardStart } ZwTd1vkAqduCcDFhFqDyGw
//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshSelection.h
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
//%Header } qQDJO7f1dpVj75uGC4s97A
/*
 * $Id: MushMeshSelection.h,v 1.8 2006/06/01 15:39:32 southa Exp $
 * $Log: MushMeshSelection.h,v $
 * Revision 1.8  2006/06/01 15:39:32  southa
 * DrawArray verification and fixes
 *
 * Revision 1.7  2005/08/01 17:58:25  southa
 * Object explosion
 *
 * Revision 1.6  2005/07/02 00:42:38  southa
 * Conditioning tweaks
 *
 * Revision 1.5  2005/05/19 13:02:11  southa
 * Mac release work
 *
 * Revision 1.4  2005/02/10 12:34:07  southa
 * Template fixes
 *
 * Revision 1.3  2004/09/27 22:42:09  southa
 * MSVC compilation fixes
 *
 * Revision 1.2  2004/01/02 21:13:11  southa
 * Source conditioning
 *
 * Revision 1.1  2003/10/20 13:05:57  southa
 * Created
 *
 */

#include "MushMeshStandard.h"
#include "MushMeshVector.h"

//:generate nonvirtual ostream
class MushMeshSelection
{
public:

    Mushware::t2U32 start;
    Mushware::t2U32 stride;
    Mushware::U32 size;
//%classPrototypes {
public:
    void AutoPrint(std::ostream& ioOut) const;
//%classPrototypes } igNZsqh+Ffme42HZCDZW6Q
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushMeshSelection& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } hY/T98Ru1YtnD32lhEtIpA
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
