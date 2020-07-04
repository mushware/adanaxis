//%Header {
/*****************************************************************************
 *
 * File: src/TestMushcore/TestMushcoreIO.cpp
 *
 * Copyright: Andy Southgate 2002-2007, 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/
//%Header } LOibKRnl+oYzGAP0c6hHrA
/*
 * $Id: TestMushcoreIO.cpp,v 1.19 2006/05/11 10:43:18 southa Exp $
 * $Log: TestMushcoreIO.cpp,v $
 * Revision 1.19  2006/05/11 10:43:18  southa
 * Project updates
 *
 * Revision 1.18  2005/07/01 14:59:00  southa
 * Mushcore auto_ptr and binary string fixes
 *
 * Revision 1.17  2005/06/13 14:25:46  southa
 * Pipe and ordered data work
 *
 * Revision 1.16  2005/05/19 13:02:24  southa
 * Mac release work
 *
 * Revision 1.15  2005/03/25 22:04:51  southa
 * Dialogue and MushcoreIO fixes
 *
 * Revision 1.14  2004/01/18 18:25:29  southa
 * XML stream upgrades
 *
 * Revision 1.13  2004/01/08 22:41:10  southa
 * MushModel commands
 *
 * Revision 1.12  2004/01/08 16:06:11  southa
 * XML fixes
 *
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
#include "TestMushcoreVirtualPointerObject.h"

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
            throw MushcoreCommandFail("MushcoreIO fault '"+testStream.str()+"'");
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
            throw MushcoreCommandFail("MushcoreIO fault '"+testStream.str()+"'");
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
            throw MushcoreCommandFail("MushcoreIO fault '"+testStream.str()+"'");
        }
    }
    
    // serial stream test
    {
        ostringstream testOStream;
        MushcoreXMLOStream xmlOStream(testOStream);
        TestMushcoreObject testObject(1);

        xmlOStream.OStreamGet() << "<!-- Single line comment --><!-- Single line comment -->" << endl;
        xmlOStream.OStreamGet() << "<!-- Multi line comment" << endl;
        xmlOStream.OStreamGet() << endl;
        xmlOStream.OStreamGet() << "...close multiline comment -->" << endl;
        
        xmlOStream << testObject;

        // MushcoreXMLOStream xmlCout(cout);
        // xmlCout << testObject;

        TestMushcoreObject readBackObject;

        istringstream testIStream(testOStream.str());
        MushcoreXMLIStream xmlIStream(testIStream);

        xmlIStream >> readBackObject;

        if (testObject != readBackObject)
        {
            ostringstream readBackStream;
            MushcoreXMLOStream xmlOut(readBackStream);
            xmlOut << readBackObject;
            ostringstream message;
            message << "MushcoreIO readback fault 1 '"+testOStream.str()+"' != " << readBackStream.str() << ", " << testObject << " != " << readBackObject;
            throw MushcoreCommandFail(message.str());
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
        
        ///MushcoreXMLOStream xmlCout(cout);
        //xmlCout << testData;

        MushcoreData<TestMushcoreObject> readBackData;
        
        istringstream testIStream(testOStream.str());
        MushcoreXMLIStream xmlIStream(testIStream);
        
        xmlIStream >> readBackData;
        
        if (testData != readBackData)
        {
            ostringstream readBackStream;
            MushcoreXMLOStream xmlOut(readBackStream);
            xmlOut << readBackData;
            ostringstream message;
            message << "MushcoreIO readback fault 2 '"+testOStream.str()+"' != '" << readBackStream.str() << "', " << testData << " != " << readBackData;
            throw MushcoreCommandFail(message.str());
        }
        
        MushcoreDataRef<TestMushcoreObject> testObjectRef("obj1", testData);
        
        if (testObjectRef.Get() ==  NULL)
        {
            throw MushcoreCommandFail("MushcoreIO DataRef not found ");            
        }            
        
        TestMushcoreObject testObj1(1); // gcc 4.0.1 workaround
        if (*testObjectRef.Get() != testObj1)
        {
            throw MushcoreCommandFail("MushcoreIO DataRef value fault ");            
        }
        
        testObjectRef.Get()->U8Set(3);
        if (*testObjectRef.Get() == testObj1)
        {
            throw MushcoreCommandFail("MushcoreIO DataRef write failure ");            
        }
    }
    
    // Test read and write of virtual objects
    
    {
        ostringstream testOStream;
        MushcoreXMLOStream xmlOStream(testOStream);
        TestMushcoreVirtualPointerObject testObject;
        
        xmlOStream << testObject;
        
        TestMushcoreVirtualPointerObject readBackObject;
        
        istringstream testIStream(testOStream.str());
        MushcoreXMLIStream xmlIStream(testIStream);
        
        xmlIStream >> readBackObject;
        
        if (testObject != readBackObject)
        {
            ostringstream readBackStream;
            MushcoreXMLOStream xmlOut(readBackStream);
            xmlOut << readBackObject;
            ostringstream message;
            message << "MushcoreIO readback fault 3 '"+testOStream.str()+"' != " << readBackStream.str() << ", " << testObject << " != " << readBackObject;
            throw MushcoreCommandFail(message.str());
        }
    }
    
    {
        ostringstream testOStream;
        MushcoreXMLOStream xmlOStream(testOStream);
        TestMushcoreVirtualPointerObject testObject;
        testObject.PopulateObjects1();
        
        xmlOStream << testObject;
        
        TestMushcoreVirtualPointerObject readBackObject;
        
        istringstream testIStream(testOStream.str());
        MushcoreXMLIStream xmlIStream(testIStream);
        
        xmlIStream >> readBackObject;
        
        if (testObject != readBackObject)
        {
            ostringstream readBackStream;
            MushcoreXMLOStream xmlOut(readBackStream);
            xmlOut << readBackObject;
            ostringstream message;
            message << "MushcoreIO readback fault 4 '"+testOStream.str()+"' != " << readBackStream.str() << ", " << testObject << " != " << readBackObject;
            throw MushcoreCommandFail(message.str());
        }
    }
    
    {
        ostringstream testOStream;
        MushcoreXMLOStream xmlOStream(testOStream);
        TestMushcoreVirtualPointerObject testObject;
        testObject.PopulateObjects2();
        
        xmlOStream << testObject;
        
        TestMushcoreVirtualPointerObject readBackObject;
        
        istringstream testIStream(testOStream.str());
        MushcoreXMLIStream xmlIStream(testIStream);
        
        xmlIStream >> readBackObject;

        if (testObject != readBackObject)
        {
            ostringstream readBackStream;
            MushcoreXMLOStream xmlOut(readBackStream);
            xmlOut << readBackObject;
            ostringstream message;
            message << "MushcoreIO readback fault 5 '"+testOStream.str()+"' != " << readBackStream.str() << ", " << testObject << " != " << readBackObject;
            throw MushcoreCommandFail(message.str());
        }
    }

    return MushcoreScalar(0);
}

void
TestMushcoreIO::Install(void)
{
    MushcoreInterpreter::Sgl().HandlerAdd("testmushcoreio", TestIO);
}
