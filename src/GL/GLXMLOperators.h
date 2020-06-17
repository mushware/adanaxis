//%includeGuardStart {
#ifndef GLXMLOPERATORS_H
#define GLXMLOPERATORS_H
//%includeGuardStart } VmHinfJK7FiML780R1+NgA
//%Header {
/*****************************************************************************
 *
 * File: src/GL/GLXMLOperators.h
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
//%Header } E1OHdpEkdcABnEF8y2csqA
/*
 * $Id: GLXMLOperators.h,v 1.7 2006/06/16 12:11:03 southa Exp $
 * $Log: GLXMLOperators.h,v $
 * Revision 1.7  2006/06/16 12:11:03  southa
 * Ruby subclasses
 *
 * Revision 1.6  2006/06/01 15:38:55  southa
 * DrawArray verification and fixes
 *
 * Revision 1.5  2005/05/19 13:02:01  southa
 * Mac release work
 *
 * Revision 1.4  2005/03/30 23:33:56  southa
 * win32 and gcc 2.95 fixes
 *
 * Revision 1.3  2005/02/03 21:02:52  southa
 * Build fixes
 *
 * Revision 1.2  2004/09/27 22:42:08  southa
 * MSVC compilation fixes
 *
 * Revision 1.1  2004/01/10 20:29:34  southa
 * Form and rendering work
 *
 */

#include "GLStandard.h"

#if 0

inline void
operator>>(MushcoreXMLIStream& ioIn, GLenum& outObj)
{
    Mushware::tXMLVal xmlVal;
    ioIn.ObjectRead(xmlVal);
    outObj = static_cast<GLenum>(xmlVal);
}

#endif

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
