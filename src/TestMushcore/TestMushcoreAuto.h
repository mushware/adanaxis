//%includeGuardStart {
#ifndef TESTMUSHCOREAUTO_H
#define TESTMUSHCOREAUTO_H
//%includeGuardStart } ws7tE1XfmGwQ1SVRyH0Gcg
//%Header {
/*****************************************************************************
 *
 * File: src/TestMushcore/TestMushcoreAuto.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } WD4KHWY4O+W/dU8T7LsJ+w
/*
 * $Id: TestMushcoreAuto.h,v 1.4 2003/09/17 19:40:39 southa Exp $
 * $Log: TestMushcoreAuto.h,v $
 * Revision 1.4  2003/09/17 19:40:39  southa
 * Source conditioning upgrades
 *
 * Revision 1.3  2003/08/21 23:09:37  southa
 * Fixed file headers
 *
 * Revision 1.2  2003/01/20 17:03:22  southa
 * Command line expression evaluator enhancements
 *
 * Revision 1.1  2003/01/20 15:38:28  southa
 * Created MushcoreTest
 *
 */

#include "TestMushcoreStandard.h"

class TestMushcoreAuto
{
public:
    static MushcoreScalar TestAuto(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static void Install(void);
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
