//%includeGuardStart {
#ifndef TESTMUSHCOREIO_H
#define TESTMUSHCOREIO_H
//%includeGuardStart } 8NR/SClt8A407tgBZheUAQ
//%Header {
/*****************************************************************************
 *
 * File: src/TestMushcore/TestMushcoreIO.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } gdYpHWihKjy7PXfuuAHfLw
/*
 * $Id: TestMushcoreIO.h,v 1.1 2003/09/17 19:10:17 southa Exp $
 * $Log: TestMushcoreIO.h,v $
 * Revision 1.1  2003/09/17 19:10:17  southa
 * Created
 *
 */

#include "TestMushcoreStandard.h"

class TestMushcoreIO
{
public:
    static MushcoreScalar TestIO(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static void Install(void);
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
