//%includeGuardStart {
#ifndef MUSTLID_H
#define MUSTLID_H
//%includeGuardStart } G1vJoUq0DG+kQKGx0TIkuA
//%Header {
/*****************************************************************************
 *
 * File: src/Mustl/MustlID.h
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
//%Header } 3Tb16P4OzZ7nRibb9E1eKg
/*
 * $Id: MustlID.h,v 1.9 2006/06/01 15:39:52 southa Exp $
 * $Log: MustlID.h,v $
 * Revision 1.9  2006/06/01 15:39:52  southa
 * DrawArray verification and fixes
 *
 * Revision 1.8  2005/05/19 13:02:18  southa
 * Mac release work
 *
 * Revision 1.7  2004/01/02 21:13:14  southa
 * Source conditioning
 *
 * Revision 1.6  2003/09/17 19:40:37  southa
 * Source conditioning upgrades
 *
 * Revision 1.5  2003/08/21 23:09:25  southa
 * Fixed file headers
 *
 * Revision 1.4  2003/01/07 17:13:44  southa
 * Fixes for gcc 3.1
 *
 * Revision 1.3  2002/12/20 13:17:45  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.2  2002/12/17 12:53:33  southa
 * Mustl library
 *
 * Revision 1.1  2002/12/12 14:00:25  southa
 * Created Mustl
 *
 * Revision 1.1  2002/12/07 18:32:15  southa
 * Network ID stuff
 *
 */

#include "MustlStandard.h"

class MustlData;

class MustlID
{
public:
    virtual ~MustlID() {}
    virtual MustlID *Clone(void) const = 0;
    virtual void Pack(MustlData& ioData) const = 0;
    virtual void Unpack(MustlData& ioData) = 0;
    virtual void Print(std::ostream& ioOut) const = 0;
    
private:
};

std::ostream& operator<<(std::ostream &ioOut, const MustlID& inObj);

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
