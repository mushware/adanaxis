//%includeGuardStart {
#ifndef MUSHGLCLAIMER_H
#define MUSHGLCLAIMER_H
//%includeGuardStart } 4OgFyVD5b4MruLBSe1Mx6A
//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLClaimer.h
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
//%Header } LbVMpuqOua7cHnGDFqVOjQ
/*
 * $Id: MushGLClaimer.h,v 1.2 2006/06/01 15:39:17 southa Exp $
 * $Log: MushGLClaimer.h,v $
 * Revision 1.2  2006/06/01 15:39:17  southa
 * DrawArray verification and fixes
 *
 * Revision 1.1  2005/07/04 11:10:43  southa
 * Rendering pipeline
 *
 */

#include "MushGLStandard.h"

#include "MushGLBuffers.h"

template<class T>
class MushGLClaimer
{
public:
    enum
    {
        kOwnerInvalid,
        kOwnerNone,
        kOwnerMushGL,
        kOwnerOther
    };
    explicit MushGLClaimer(T& ioClaimed, Mushware::U32 inOwner = MushGLBuffers::kOwnerOther) :
        m_claimed(ioClaimed),
        m_owner(inOwner)
    {
        m_claimed.Claim(m_owner);
    }

    ~MushGLClaimer() { m_claimed.Release(m_owner); }

private:
    T& m_claimed;
    Mushware::U32 m_owner;
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
