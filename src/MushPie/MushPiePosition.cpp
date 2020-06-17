//%Header {
/*****************************************************************************
 *
 * File: src/MushPie/MushPiePosition.cpp
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
//%Header } wrO4BoUJfVkG+IKislPH/A
/*
 * $Id: MushPiePosition.cpp,v 1.3 2006/05/11 10:43:16 southa Exp $
 * $Log: MushPiePosition.cpp,v $
 * Revision 1.3  2006/05/11 10:43:16  southa
 * Project updates
 *
 * Revision 1.2  2005/05/19 13:02:13  southa
 * Mac release work
 *
 * Revision 1.1  2004/01/04 17:02:30  southa
 * MushPie extras and MushcoreIO fixes
 *
 */

#include "MushPiePosition.h"
using namespace Mushware;

void
operator>>(MushcoreXMLIStream& ioIn, MushPiePosition& outObj)
{
    ioIn >> outObj.angPos;
    ioIn >> outObj.pos;
}

MushcoreXMLOStream&
operator<<(MushcoreXMLOStream& ioOut, const MushPiePosition& inObj)
{
    ioOut << inObj.angPos;
    ioOut << inObj.pos;
    return ioOut;
}

//%outOfLineFunctions {
void
MushPiePosition::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "angPos=" << angPos << ", ";
    ioOut << "pos=" << pos;
    ioOut << "]";
}
//%outOfLineFunctions } WFq1ktxUHFScHKfNgCOLig
