//%includeGuardStart {
#ifndef MUSHPIEPOSITION_H
#define MUSHPIEPOSITION_H
//%includeGuardStart } iDrnhb3v9WwAjgrJfJ3ImQ
//%Header {
/*****************************************************************************
 *
 * File: src/MushPie/MushPiePosition.h
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
//%Header } Bf7vrZHj1Vgo3GL6mlqY0Q
/*
 * $Id: MushPiePosition.h,v 1.6 2006/05/11 10:43:16 southa Exp $
 * $Log: MushPiePosition.h,v $
 * Revision 1.6  2006/05/11 10:43:16  southa
 * Project updates
 *
 * Revision 1.5  2005/07/02 00:42:38  southa
 * Conditioning tweaks
 *
 * Revision 1.4  2005/05/19 13:02:13  southa
 * Mac release work
 *
 * Revision 1.3  2005/02/10 12:34:15  southa
 * Template fixes
 *
 * Revision 1.2  2004/01/06 00:34:56  southa
 * MushPie testing
 *
 * Revision 1.1  2004/01/04 17:02:30  southa
 * MushPie extras and MushcoreIO fixes
 *
 */

#include "MushPieStandard.h"

//:generate nonvirtual ostream
class MushPiePosition
{
public:
    MushPiePosition() {}
    
    Mushware::tQVal angPos;
    Mushware::t3Val pos;

//%classPrototypes {
public:
    void AutoPrint(std::ostream& ioOut) const;
//%classPrototypes } igNZsqh+Ffme42HZCDZW6Q
};

void
operator>>(MushcoreXMLIStream& ioIn, MushPiePosition& outObj);

MushcoreXMLOStream&
operator<<(MushcoreXMLOStream& ioOut, const MushPiePosition& inObj);

//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushPiePosition& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } d8HdhqjTeBKhSuh3Oc/qcQ
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
