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
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } QlV3oDo+7Am5sdDcKqi8RQ
/*
 * $Id: TestMushcoreAuto.h,v 1.3 2003/08/21 23:09:37 southa Exp $
 * $Log: TestMushcoreAuto.h,v $
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
