//%Header {
/*****************************************************************************
 *
 * File: src/TestMushcore/TestMushcoreData.cpp
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
//%Header } i2LAmkdOdIvxYwJe0Twyjw
/*
 * $Id: TestMushcoreData.cpp,v 1.2 2006/06/01 15:40:04 southa Exp $
 * $Log: TestMushcoreData.cpp,v $
 * Revision 1.2  2006/06/01 15:40:04  southa
 * DrawArray verification and fixes
 *
 * Revision 1.1  2005/06/13 14:25:46  southa
 * Pipe and ordered data work
 *
 */

#include "TestMushcoreData.h"

using namespace Mushware;
using namespace std;

MushcoreInstaller TestMushcoreDataInstaller(TestMushcoreData::Install);

MushcoreScalar
TestMushcoreData::TestData(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    typedef MushcoreOrderedData<std::string, U32> tData;
    tData data;
    data.Set(1, "one");
    data.Set(7, "seven");
    data.Set(4, "four");
    data.Set(2, "two");

    std::ostringstream testOStream;
    MushcoreXMLOStream xmlStream(testOStream);

    xmlStream << data;
    
    tData::tMapIterator mapIter = data.Begin();
    bool success = true;

    if (mapIter->first != 1 || *mapIter->second != "one")
    {
        success = false;
    }
    ++mapIter;
    if (mapIter->first != 2 || *mapIter->second != "two")
    {
        success = false;
    }
    ++mapIter;
    if (mapIter->first != 4 || *mapIter->second != "four")
    {
        success = false;
    }
    ++mapIter;
    if (mapIter->first != 7 || *mapIter->second != "seven")
    {
        success = false;
    }
    ++mapIter;
    if (mapIter != data.End())
    {
        success = false;   
    }
    if (!success)
    {
        throw MushcoreCommandFail("MushcoreOrderedData ordering fault");
    }
    
    return MushcoreScalar(0);
}

void
TestMushcoreData::Install(void)
{
    MushcoreInterpreter::Sgl().HandlerAdd("testmushcoredata", TestData);
}
