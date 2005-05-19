//%includeGuardStart {
#ifndef TESTMUSHCORECOMMAND_H
#define TESTMUSHCORECOMMAND_H
//%includeGuardStart } xx+iiGc2tYCbwZhxX9q4Qw
//%Header {
/*****************************************************************************
 *
 * File: src/TestMushcore/TestMushcoreCommand.h
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
//%Header } TNiloae2dlIHle1CKaq2dQ
/*
 * $Id: TestMushcoreCommand.h,v 1.4 2004/01/02 21:13:17 southa Exp $
 * $Log: TestMushcoreCommand.h,v $
 * Revision 1.4  2004/01/02 21:13:17  southa
 * Source conditioning
 *
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
