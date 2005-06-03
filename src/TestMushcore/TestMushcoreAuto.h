#ifndef TESTMUSHCOREAUTO_H
#define TESTMUSHCOREAUTO_H
/*****************************************************************************
 *
 * (Mushware file header version 1.2)
 *
 * This file contains original work by Andy Southgate.
 * Copyright Andy Southgate 2002.  All rights reserved.
 * Contact details can be found at http://www.mushware.com/
 *
 ****************************************************************************/

/*
 * $Id: TestMushcoreAuto.h,v 1.1 2003/01/20 15:38:28 southa Exp $
 * $Log: TestMushcoreAuto.h,v $
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
#endif
