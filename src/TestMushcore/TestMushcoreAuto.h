#ifndef TESTMUSHCOREAUTO_H
#define TESTMUSHCOREAUTO_H
/*****************************************************************************
 *
 * (Mushware file header version 1.3)
 *
 * Copyrighted work by Andy Southgate 2003
 *
 * This file may be redistributed and/or modified under the terms of the
 * Mushware licence which you should have received with this file.  For
 * information, please contact the author via http://www.mushware.com/.
 *
 ****************************************************************************/

/*
 * $Id: TestMushcoreAuto.h,v 1.2 2003/01/20 17:03:22 southa Exp $
 * $Log: TestMushcoreAuto.h,v $
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
#endif
