//%Header {
/*****************************************************************************
 *
 * File: src/TesseractTrainer/TesseractTrainerInfo.cpp
 *
 * Author: Andy Southgate 2002-2005
 *
 * This file contains original work by Andy Southgate.  The author and his
 * employer (Mushware Limited) irrevocably waive all of their copyright rights
 * vested in this particular version of this file to the furthest extent
 * permitted.  The author and Mushware Limited also irrevocably waive any and
 * all of their intellectual property rights arising from said file and its
 * creation that would otherwise restrict the rights of any party to use and/or
 * distribute the use of, the techniques and methods used herein.  A written
 * waiver can be obtained via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } AB8KzsXX8AUrZ2Tp6Oe/IA
/*
 * $Id: TesseractTrainerInfo.cpp,v 1.3 2005/05/27 12:48:37 southa Exp $
 * $Log: TesseractTrainerInfo.cpp,v $
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
#define VERSION "0.1.1"
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
