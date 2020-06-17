//%includeGuardStart {
#ifndef MUSHCOREAUTOBOOL_H
#define MUSHCOREAUTOBOOL_H
//%includeGuardStart } Zp59GQ28qUO3RJseIUoDFA
//%Header {
/*****************************************************************************
 *
 * File: src/Mushcore/MushcoreAutoBool.h
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
//%Header } jpy/OdRwTq6gHr5qfiYWLA
/*
 * $Id: MushcoreAutoBool.h,v 1.3 2006/06/01 15:39:41 southa Exp $
 * $Log: MushcoreAutoBool.h,v $
 * Revision 1.3  2006/06/01 15:39:41  southa
 * DrawArray verification and fixes
 *
 * Revision 1.2  2005/07/29 08:27:47  southa
 * Collision work
 *
 * Revision 1.1  2005/06/13 14:25:45  southa
 * Pipe and ordered data work
 *
 */

#include "MushcoreStandard.h"

class MushcoreAutoBool
{
public:
    MushcoreAutoBool(bool &inBool) : m_pBool(&inBool) { *m_pBool = true; }
    ~MushcoreAutoBool() { *m_pBool = false; }
private:
    MushcoreAutoBool(const MushcoreAutoBool& inBool) : m_pBool(inBool.m_pBool) {}
    const MushcoreAutoBool& operator=(MushcoreAutoBool&) { return *this; }
    
    bool *m_pBool;
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
