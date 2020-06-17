//%includeGuardStart {
#ifndef MUSTLPLATFORMERROR_H
#define MUSTLPLATFORMERROR_H
//%includeGuardStart } QbpcCz1efIT/WY1UE3COEw
//%Header {
/*****************************************************************************
 *
 * File: src/Mustl/MustlPlatformError.h
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
//%Header } dOETrQ1nY75NFXVYTD6iow
/*
 * $Id: MustlPlatformError.h,v 1.7 2006/06/01 15:39:53 southa Exp $
 * $Log: MustlPlatformError.h,v $
 * Revision 1.7  2006/06/01 15:39:53  southa
 * DrawArray verification and fixes
 *
 * Revision 1.6  2005/05/19 13:02:19  southa
 * Mac release work
 *
 * Revision 1.5  2004/01/02 21:13:15  southa
 * Source conditioning
 *
 * Revision 1.4  2003/09/17 19:40:38  southa
 * Source conditioning upgrades
 *
 * Revision 1.3  2003/08/21 23:09:29  southa
 * Fixed file headers
 *
 * Revision 1.2  2003/01/17 13:30:41  southa
 * Source conditioning and build fixes
 *
 * Revision 1.1  2003/01/16 15:58:02  southa
 * Mustl exception handling
 *
 */

#include "MustlStandard.h"

class MustlPlatformError
{
public:
    typedef int tErrorCode;
    static void Throw(const std::string& inPrefix);
    static void Throw(tErrorCode inCode, const std::string& inPrefix);
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
