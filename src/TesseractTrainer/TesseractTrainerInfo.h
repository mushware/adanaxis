//%includeGuardStart {
#ifndef TESSERACTTRAINERINFO_H
#define TESSERACTTRAINERINFO_H
//%includeGuardStart } ufVSJcKPA53cgWOU6771bA
//%Header {
/*****************************************************************************
 *
 * File: src/TesseractTrainer/TesseractTrainerInfo.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } caBkS6mQQh/rknN3GII2zw
/*
 * $Id$
 * $Log$
 */

#include "mushMushcore.h"

class TesseractTrainerInfo : public MushcoreInfo
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
