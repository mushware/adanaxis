//%includeGuardStart {
#ifndef TESTMUSHCORECOMMAND_H
#define TESTMUSHCORECOMMAND_H
//%includeGuardStart } xx+iiGc2tYCbwZhxX9q4Qw
//%Header {
/*****************************************************************************
 *
 * File: src/TestMushcore/TestMushcoreCommand.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 4arXJMRIM2vOXG8E2G5JkQ
/*
 * $Id: TestMushcoreCommand.h,v 1.3 2003/09/17 19:40:39 southa Exp $
 * $Log: TestMushcoreCommand.h,v $
 * Revision 1.3  2003/09/17 19:40:39  southa
 * Source conditioning upgrades
 *
 * Revision 1.2  2003/08/21 23:09:37  southa
 * Fixed file headers
 *
 * Revision 1.1  2003/01/20 17:03:22  southa
 * Command line expression evaluator enhancements
 *
 */

#include "TestMushcoreStandard.h"

class TestMushcoreCommand
{
public:
    static MushcoreScalar TestCommand(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static void Install(void);

protected:
    static void ValueTest(const std::string& inName, const MushcoreScalar& inScalar);
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
