//%Header {
/*****************************************************************************
 *
 * File: src/TesseractTrainer/TesseractTrainerInfo.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } I881tJl8D0lHUN545yQ8NA
/*
 * $Id$
 * $Log$
 */

#include "TesseractTrainerInfo.h"

#ifndef PACKAGE
#define PACKAGE "tesseracttrainer"
#endif

#ifndef VERSION
#define VERSION "0.0.1"
#endif

#include "TesseractTrainerSTL.h"

using namespace Mushware;
using namespace std;

MushcoreInstaller TesseractTrainerInfoInstaller(TesseractTrainerInfo::Install);

string
TesseractTrainerInfo::ApplicationNameGet(void)
{
    return "TesseractTrainer";
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
