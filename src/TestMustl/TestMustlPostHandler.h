#ifndef TESTMUSTLPOSTHANDLER_H
#define TESTMUSTLPOSTHANDLER_H
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
 * $Id: TestMustlPostHandler.h,v 1.2 2003/01/17 13:30:42 southa Exp $
 * $Log: TestMustlPostHandler.h,v $
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
#endif
