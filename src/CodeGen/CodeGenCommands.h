//%includeGuardStart {
#ifndef CODEGENCOMMANDS_H
#define CODEGENCOMMANDS_H
//%includeGuardStart } FHHGpOF69Q6Xwq1bL4LKmA
//%Header {
/*****************************************************************************
 *
 * File: src/CodeGen/CodeGenCommands.h
 *
 * Copyright: Andy Southgate 2002-2007
 *
 * All rights reserved.  Distribution of this source file or the data
 * contained within it is prohibited unless expressly permitted by Mushware
 * Limited.  For information, please contact the author via
 * http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } zEobk0DXETuFz8Ygd2wQqQ
/*
 * $Id: CodeGenCommands.h,v 1.3 2006/06/01 15:38:49 southa Exp $
 * $Log: CodeGenCommands.h,v $
 * Revision 1.3  2006/06/01 15:38:49  southa
 * DrawArray verification and fixes
 *
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
