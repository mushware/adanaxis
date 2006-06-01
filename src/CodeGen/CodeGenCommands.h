//%includeGuardStart {
#ifndef CODEGENCOMMANDS_H
#define CODEGENCOMMANDS_H
//%includeGuardStart } FHHGpOF69Q6Xwq1bL4LKmA
//%Header {
/*****************************************************************************
 *
 * File: src/CodeGen/CodeGenCommands.h
 *
 * Copyright: Andy Southgate 2002-2006
 *
 * All rights reserved.  Distribution prohibited.  For information, please
 * contact the author via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } nfr4RJPN0SfeGKZQ2TobNw
/*
 * $Id: CodeGenCommands.h,v 1.2 2005/05/19 13:01:57 southa Exp $
 * $Log: CodeGenCommands.h,v $
 * Revision 1.2  2005/05/19 13:01:57  southa
 * Mac release work
 *
 * Revision 1.1  2005/04/11 23:31:40  southa
 * Startup and registration screen
 *
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
