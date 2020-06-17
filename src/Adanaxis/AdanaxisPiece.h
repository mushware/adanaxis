//%includeGuardStart {
#ifndef ADANAXISPIECE_H
#define ADANAXISPIECE_H
//%includeGuardStart } 8Im+BPIX3SauUY+jOIyAhw
//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisPiece.h
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
//%Header } CXU3/B5gZ8suyVyNJ0fhxA
/*
 * $Id: AdanaxisPiece.h,v 1.2 2007/04/18 09:22:01 southa Exp $
 * $Log: AdanaxisPiece.h,v $
 * Revision 1.2  2007/04/18 09:22:01  southa
 * Header and level fixes
 *
 * Revision 1.1  2006/10/30 17:03:51  southa
 * Remnants creation
 *
 */

#include "AdanaxisStandard.h"

#include "API/mushMushGame.h"

class AdanaxisPiece : public MushGamePiece
{
public:
    static Mushware::tRubyValue Klass(void);
    static void RubyInstall(void);
    
private:
    static Mushware::tRubyValue m_rubyKlass; // Must duplicate this in derived classes
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
