//%includeGuardStart {
#ifndef TESSERACTTRAINERCOMMANDHANDLER_H
#define TESSERACTTRAINERCOMMANDHANDLER_H
//%includeGuardStart } P2HcNfPJjvABO6wu045LyA
//%Header {
/*****************************************************************************
 *
 * File: src/TesseractTrainer/TesseractTrainerCommandHandler.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } +Gz2xC1hP1loTAkYd5P2dg
/*
 * $Id$
 * $Log$
 */

#include "mushMushcore.h"

class TesseractTrainerCommandHandler
{
public:
    static void Install(void);
    static MushcoreScalar TesseractTrainer(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
