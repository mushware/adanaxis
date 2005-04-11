//%includeGuardStart {
#ifndef CODEGENCOMMANDS_H
#define CODEGENCOMMANDS_H
//%includeGuardStart } FHHGpOF69Q6Xwq1bL4LKmA
//%Header {
/*****************************************************************************
 *
 * File: src/CodeGen/CodeGenCommands.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } V31ae4LqVVZQrXmmvogKBQ
/*
 * $Id$
 * $Log$
 */

#include "mushMushcore.h"

class CodeGenCommands
{
public:
    static void Install(void);
    static MushcoreScalar CodeGenGenerate(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
