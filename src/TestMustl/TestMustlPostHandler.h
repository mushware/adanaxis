//%includeGuardStart {
#ifndef TESTMUSTLPOSTHANDLER_H
#define TESTMUSTLPOSTHANDLER_H
//%includeGuardStart } SJgpGuH7CQ341wYrg3Yerw
//%Header {
/*****************************************************************************
 *
 * File: src/TestMustl/TestMustlPostHandler.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } l8+IkZlcg/bu6cW8cHVB5A
/*
 * $Id: TestMustlPostHandler.h,v 1.4 2003/09/17 19:40:39 southa Exp $
 * $Log: TestMustlPostHandler.h,v $
 * Revision 1.4  2003/09/17 19:40:39  southa
 * Source conditioning upgrades
 *
 * Revision 1.3  2003/08/21 23:09:39  southa
 * Fixed file headers
 *
 * Revision 1.2  2003/01/17 13:30:42  southa
 * Source conditioning and build fixes
 *
 * Revision 1.1  2003/01/14 20:46:12  southa
 * Post data handling
 *
 */

#include "TestMustlStandard.h"

class MushcoreCommand;
class MushcoreEnv;
class MushcoreScalar;

class TestMustlPostHandler
{
public:
    static void Install(void);
    static MushcoreScalar PostHandler(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
