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
 * $Id: TestMushcoreIO.cpp,v 1.3 2003/09/21 09:51:10 southa Exp $
 * $Log: TestMushcoreIO.cpp,v $
 * Revision 1.3  2003/09/21 09:51:10  southa
 * Stream autogenerators
 *
 * Revision 1.2  2003/09/17 19:40:39  southa
 * Source conditioning upgrades
 *
 * Revision 1.1  2003/09/17 19:10:17  southa
 * Created
 *
 */

#include "TestMushcoreIO.h"
#include "TestMushcoreObject.h"

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

    {
        map<string, U32> testVector;
        testVector["one"] = 1;
        testVector["fifteen"] = 15;
        testVector["eight"] = 8;
        testVector["twenty five"] = 25;

        ostringstream testStream;
        testStream << testVector;

        if (testStream.str() != "[eight => 8, fifteen => 15, one => 1, twenty five => 25]")
        {
            throw MushcoreLogicFail("MushcoreIO fault '"+testStream.str()+"'");
        }
    }

    // serial stream test
    {
        MushcoreXMLOStream xmlOStream;
        TestMushcoreObject testObject;

        Mushcore::Pickle(xmlOStream, testObject, "testobject");
        ostringstream testOutStream;
        testOutStream << xmlOStream;

        if (testOutStream.str() != "")
        {
            // throw MushcoreLogicFail("MushcoreIO fault '"+testOutStream.str()+"'");
        }

        TestMushcoreObject readBackObject(0);

        istringstream testInStream(testOutStream.str());
        MushcoreXMLIStream xmlIStream(&testInStream);

        Mushcore::Unpickle(xmlIStream, readBackObject);
        cout << readBackObject << endl;
    } 
    
    return MushcoreScalar(0);
}

void
TestMushcoreIO::Install(void)
{
    MushcoreInterpreter::Sgl().HandlerAdd("testio", TestIO);
}
