//%Header {
/*****************************************************************************
 *
 * File: src/TestMushcore/TestMushcoreIO.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } P6yBrDF9KuOXOLkAKGMvXA
/*
 * $Id: TestMushcoreIO.cpp,v 1.11 2004/01/07 18:01:19 southa Exp $
 * $Log: TestMushcoreIO.cpp,v $
 * Revision 1.11  2004/01/07 18:01:19  southa
 * MushModel and Infernal work
 *
 * Revision 1.10  2004/01/05 14:27:41  southa
 * MushPie work and build fixes
 *
 * Revision 1.9  2004/01/02 21:13:17  southa
 * Source conditioning
 *
 * Revision 1.8  2003/09/30 22:11:30  southa
 * XML objects within objects
 *
 * Revision 1.7  2003/09/23 22:57:57  southa
 * XML vector handling
 *
 * Revision 1.6  2003/09/22 19:40:36  southa
 * XML I/O work
 *
 * Revision 1.5  2003/09/21 23:15:08  southa
 * XML input stream improvements
 *
 * Revision 1.4  2003/09/21 11:46:11  southa
 * XML input stream
 *
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
        ostringstream testOStream;
        MushcoreXMLOStream xmlOStream(testOStream);
        TestMushcoreObject testObject(1);

        xmlOStream << testObject;

        MushcoreXMLOStream xmlCout(cout);
        // xmlCout << testObject;

        TestMushcoreObject readBackObject;

        istringstream testIStream(testOStream.str());
        MushcoreXMLIStream xmlIStream(testIStream);

        xmlIStream >> readBackObject;

        if (testObject != readBackObject)
        {
            ostringstream message;
            message << "MushcoreIO readback fault '"+testOStream.str()+"', " << testObject << " != " << readBackObject;
            throw MushcoreLogicFail(message.str());
        }
    }
    
    // MushcoreData test
    {
        ostringstream testOStream;
        MushcoreXMLOStream xmlOStream(testOStream);
        MushcoreData<TestMushcoreObject> testData;
        
        testData.Give("obj1", new TestMushcoreObject(1));
        testData.Give("obj2", new TestMushcoreObject());
        
        xmlOStream << testData;
        
        MushcoreXMLOStream xmlCout(cout);
        // xmlCout << testData;

        MushcoreData<TestMushcoreObject> readBackData;
        
        istringstream testIStream(testOStream.str());
        MushcoreXMLIStream xmlIStream(testIStream);
        
        xmlIStream >> readBackData;
        
        if (testData != readBackData)
        {
            ostringstream message;
            message << "MushcoreIO readback fault '"+testOStream.str()+"', " << testData << " != " << readBackData;
            throw MushcoreLogicFail(message.str());
        }
        
        MushcoreDataRef<TestMushcoreObject> testObjectRef("obj1", testData);
        
        if (testObjectRef.Get() ==  NULL)
        {
            throw MushcoreLogicFail("MushcoreIO DataRef not found ");            
        }            
        
        if (*testObjectRef.Get() != TestMushcoreObject(1))
        {
            throw MushcoreLogicFail("MushcoreIO DataRef value fault ");            
        }
        
        testObjectRef.Get()->U8Set(3);
        if (*testObjectRef.Get() == TestMushcoreObject(1))
        {
            throw MushcoreLogicFail("MushcoreIO DataRef write failure ");            
        }
    }
    
    return MushcoreScalar(0);
}

void
TestMushcoreIO::Install(void)
{
    MushcoreInterpreter::Sgl().HandlerAdd("testmushcoreio", TestIO);
}
