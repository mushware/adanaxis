#ifndef TESTMUSHCORECOMMAND_H
#define TESTMUSHCORECOMMAND_H
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
 * $Id: TestMushcoreCommand.h,v 1.1 2003/01/20 17:03:22 southa Exp $
 * $Log: TestMushcoreCommand.h,v $
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
#endif
