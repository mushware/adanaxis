/*
 * $Id$
 * $Log$
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
