//%Header {
/*****************************************************************************
 *
 * File: src/TesseractTrainer/TesseractTrainerInfo.cpp
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
//%Header } b50zUnsi3GfpnQoxq8/q8A
/*
 * $Id: TesseractTrainerInfo.cpp,v 1.7 2006/06/01 15:40:00 southa Exp $
 * $Log: TesseractTrainerInfo.cpp,v $
 * Revision 1.7  2006/06/01 15:40:00  southa
 * DrawArray verification and fixes
 *
 * Revision 1.6  2005/06/08 20:59:52  southa
 * X11 release
 *
 * Revision 1.5  2005/06/04 13:45:12  southa
 * Release 0.1.2 tweaks
 *
 * Revision 1.4  2005/05/27 19:25:24  southa
 * win32 build fixes
 *
 * Revision 1.3  2005/05/27 12:48:37  southa
 * Registration box tweaks
 *
 * Revision 1.2  2005/05/19 13:02:22  southa
 * Mac release work
 *
 * Revision 1.1  2005/02/03 15:47:00  southa
 * Quaternion work
 *
 */

#include "TesseractTrainerInfo.h"

#ifndef PACKAGE
#define PACKAGE "tesseracttrainer"
#endif

#ifndef VERSION
#define VERSION "0.1.3"
#endif

#include "TesseractTrainerSTL.h"

using namespace Mushware;
using namespace std;

MushcoreInstaller TesseractTrainerInfoInstaller(TesseractTrainerInfo::Install);

string
TesseractTrainerInfo::ApplicationNameGet(void)
{
    return "Tesseract Trainer";
}

string
TesseractTrainerInfo::PackageNameGet(void)
{
    return PACKAGE;
}

string
TesseractTrainerInfo::PackageVersionGet(void)
{
    return VERSION;
}

void
TesseractTrainerInfo::Install(void)
{
}
