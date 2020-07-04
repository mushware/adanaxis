//%Header {
/*****************************************************************************
 *
 * File: src/MeshMover/MeshMoverInfo.cpp
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
//%Header } tG2RNhmwaRgYF8r+TfSVkg
/*
 * $Id: MeshMoverInfo.cpp,v 1.6 2006/06/01 15:39:14 southa Exp $
 * $Log: MeshMoverInfo.cpp,v $
 * Revision 1.6  2006/06/01 15:39:14  southa
 * DrawArray verification and fixes
 *
 * Revision 1.5  2005/05/19 13:02:09  southa
 * Mac release work
 *
 * Revision 1.4  2004/01/06 20:46:52  southa
 * Build fixes
 *
 * Revision 1.3  2004/01/02 21:13:10  southa
 * Source conditioning
 *
 * Revision 1.2  2004/01/01 21:15:46  southa
 * Created XCode project
 *
 * Revision 1.1  2003/10/07 22:40:06  southa
 * Created MeshMover
 *
 */

#include "MeshMoverInfo.h"

#ifndef PACKAGE
#define PACKAGE "meshmover"
#endif

#ifndef VERSION
#define VERSION "0.0.1"
#endif

#include "MeshMoverSTL.h"

using namespace Mushware;
using namespace std;

MushcoreInstaller MeshMoverInfoInstaller(MeshMoverInfo::Install);

string
MeshMoverInfo::ApplicationNameGet(void)
{
    return "MeshMover";
}

string
MeshMoverInfo::PackageNameGet(void)
{
    return PACKAGE;
}

string
MeshMoverInfo::PackageVersionGet(void)
{
    return VERSION;
}

void
MeshMoverInfo::Install(void)
{
}
