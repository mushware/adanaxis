//%Header {
/*****************************************************************************
 *
 * File: src/MushRuby/MushRubyInstall.cpp
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
//%Header } IkzB266g9CiJCLuHrJVu8Q
/*
 * $Id: MushRubyInstall.cpp,v 1.1 2006/04/21 00:10:43 southa Exp $
 * $Log: MushRubyInstall.cpp,v $
 * Revision 1.1  2006/04/21 00:10:43  southa
 * MushGLFont ruby module
 *
 */

#include "MushRubyInstall.h"

MUSHCORE_SINGLETON_INSTANCE(MushRubyInstall);

using namespace Mushware;
using namespace std;

void
MushRubyInstall::Add(MushRubyInstall::tpInstallFunction inFunction)
{
    m_installFunctions.push_back(inFunction);
}

void
MushRubyInstall::Execute(void)
{
    for (U32 i=0; i<m_installFunctions.size(); ++i)
    {
        m_installFunctions[i]();
    }
}
