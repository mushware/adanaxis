//%Header {
/*****************************************************************************
 *
 * File: src/TestMushcore/TestMushcoreData.cpp
 *
 * Author: Andy Southgate 2002-2005
 *
 * This file contains original work by Andy Southgate.  The author and his
 * employer (Mushware Limited) irrevocably waive all of their copyright rights
 * vested in this particular version of this file to the furthest extent
 * permitted.  The author and Mushware Limited also irrevocably waive any and
 * all of their intellectual property rights arising from said file and its
 * creation that would otherwise restrict the rights of any party to use and/or
 * distribute the use of, the techniques and methods used herein.  A written
 * waiver can be obtained via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } Z5hWHff0cWGaac4N3Vz3Rg
/*
 * $Id$
 * $Log$
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
