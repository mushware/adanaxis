//%Header {
/*****************************************************************************
 *
 * File: src/TestMushcore/TestMushcoreIO.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } xZttvudy36KFB+QD1H0nmA
/*
 * $Id: TestMushcoreIO.cpp,v 1.1 2003/09/17 19:10:17 southa Exp $
 * $Log: TestMushcoreIO.cpp,v $
 * Revision 1.1  2003/09/17 19:10:17  southa
 * Created
 *
 */

#include "TestMushcoreIO.h"

using namespace Mushware;
using namespace std;

MushcoreInstaller TestMushcoreIOInstaller(TestMushcoreIO::Install);

MushcoreScalar
TestMushcoreIO::TestIO(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    {
        vector<U8> testVector;	
        testVector.push_back(4);
        testVector.push_back(8);
        testVector.push_back(1);
        testVector.push_back(2);
    
        ostringstream testStream;
        testStream << testVector;
    
        if (testStream.str() != "[4, 8, 1, 2]")
        {
            throw MushcoreLogicFail("MushcoreIO fault '"+testStream.str()+"'");
        }
    }
    {
        vector<U32> testVector;
        testVector.push_back(0);
        testVector.push_back(3);
        testVector.push_back(57);
        testVector.push_back(4);

        ostringstream testStream;
        testStream << testVector;
    
        if (testStream.str() != "[0, 3, 57, 4]")
        {
            throw MushcoreLogicFail("MushcoreIO fault '"+testStream.str()+"'");
        }
    }
    return MushcoreScalar(0);
}

void
TestMushcoreIO::Install(void)
{
    MushcoreInterpreter::Sgl().HandlerAdd("testio", TestIO);
}
