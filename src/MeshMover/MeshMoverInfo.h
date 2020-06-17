//%includeGuardStart {
#ifndef MESHMOVERINFO_H
#define MESHMOVERINFO_H
//%includeGuardStart } sYQqECwUfvhbPyNMAFHF2g
//%Header {
/*****************************************************************************
 *
 * File: src/MeshMover/MeshMoverInfo.h
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
//%Header } VNAaUCTcWI3cFLgGrAl+Zw
/*
 * $Id: MeshMoverInfo.h,v 1.5 2006/06/01 15:39:14 southa Exp $
 * $Log: MeshMoverInfo.h,v $
 * Revision 1.5  2006/06/01 15:39:14  southa
 * DrawArray verification and fixes
 *
 * Revision 1.4  2005/05/19 13:02:09  southa
 * Mac release work
 *
 * Revision 1.3  2004/01/06 20:46:52  southa
 * Build fixes
 *
 * Revision 1.2  2004/01/02 21:13:10  southa
 * Source conditioning
 *
 * Revision 1.1  2003/10/07 22:40:06  southa
 * Created MeshMover
 *
 */

#include "mushMushcore.h"

class MeshMoverInfo : public MushcoreInfo
{
public:
    virtual std::string ApplicationNameGet(void);
    virtual std::string PackageNameGet(void);
    virtual std::string PackageVersionGet(void);

    static void Install(void);
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
