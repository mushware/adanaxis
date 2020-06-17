//%Header {
/*****************************************************************************
 *
 * File: src/TestMushcore/TestMushcoreCounter.cpp
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
//%Header } W3hJ0KfGbJZcYfzRZ/qv/A
/*
 * $Id: TestMushcoreCounter.cpp,v 1.3 2006/06/01 15:40:04 southa Exp $
 * $Log: TestMushcoreCounter.cpp,v $
 * Revision 1.3  2006/06/01 15:40:04  southa
 * DrawArray verification and fixes
 *
 * Revision 1.2  2005/07/29 18:51:28  southa
 * Maptor tweaks
 *
 * Revision 1.1  2005/06/13 14:25:46  southa
 * Pipe and ordered data work
 *
 */


#include "TestMushcoreCounter.h"

//%outOfLineFunctions {
void
TestMushcoreCounter::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    if (m_pCount == NULL)
    {
        ioOut << "pCount=NULL" ;
    }
    else
    {
        ioOut << "pCount=" << *m_pCount;
    }
    ioOut << "]";
}
//%outOfLineFunctions } QRyICuAGxR/CwyXbo+TjWA
