//%Header {
/*****************************************************************************
 *
 * File: src/TestMushcore/TestMushcoreMaptor.cpp
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
//%Header } bMQSqQZvxv1cGuqD8QyRCw
/*
 * $Id$
 * $Log$
 */

#include "TestMushcoreMaptor.h"

#include "TestMushcorePipe.h"

#include "TestMushcoreCounter.h"

using namespace Mushware;
using namespace std;

MushcoreInstaller TestMushcoreMaptorInstaller(TestMushcoreMaptor::Install);

MushcoreScalar
TestMushcoreMaptor::TestMaptor(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    bool excepted = false;
    U32 counter = 0;
    
    // Standard container interface
    {
        MushcoreMaptor<TestMushcoreCounter> maptor;
        
        maptor[1] = new TestMushcoreCounter(counter);
        maptor[3] = new TestMushcoreCounter(counter);
        
        if (counter != 2)
        {
            throw MushcoreCommandFail("Counter fault 1");
        }
    }
    if (counter != 0)
    {
        throw MushcoreCommandFail("Counter fault 2");
    }
    MushcoreMaptor<TestMushcoreCounter> maptor;
    
    maptor[1] = new TestMushcoreCounter(counter);
    maptor[3] = new TestMushcoreCounter(counter);
    maptor[6] = new TestMushcoreCounter(counter);
    
    if (maptor.erase(7) != 0)
    {
        throw MushcoreCommandFail("Erase fault 1");
    }
    
    if (maptor.erase(6) != 1 || counter != 2 || maptor.size() != 2)
    {
        throw MushcoreCommandFail("Erase fault 2");
    }
    
    maptor.clear();
    if (counter != 0 || maptor.size() != 0)
    {
        throw MushcoreCommandFail("Clear fault 1");
    }
    
    // Give/Get/Delete interface
    // Standard container interface
    {
        MushcoreMaptor<TestMushcoreCounter> maptor2;
        
        maptor2.Give(new TestMushcoreCounter(counter), 1);
        maptor2.Give(new TestMushcoreCounter(counter), 3);
        
        if (counter != 2)
        {
            throw MushcoreCommandFail("Counter fault 3");
        }
    }
    if (counter != 0)
    {
        throw MushcoreCommandFail("Counter fault 4");
    }
    
    maptor.Give(new TestMushcoreCounter(counter), 1);
    maptor.Give(new TestMushcoreCounter(counter), 3);
    maptor.Give(new TestMushcoreCounter(counter), 6);
    
    if (maptor.DeleteIfExists(7))
    {
        throw MushcoreCommandFail("Erase fault 3");
    }
    
    if (!maptor.DeleteIfExists(6) || counter != 2)
    {
        throw MushcoreCommandFail("Erase fault 4");
    }
    
    MushcoreMaptor<TestMushcoreCounter>::mapped_type result;
    
    if (maptor.GetIfExists(result, 6))
    {
        throw MushcoreCommandFail("GetIfExists fault 1");
    }
    if (!maptor.GetIfExists(result, 3))
    {
        throw MushcoreCommandFail("GetIfExists fault 2");
    }
    
    // Overwrite test
    if (counter != 2)
    {
        throw MushcoreCommandFail("Counter fault 3");
    }
    maptor.Give(new TestMushcoreCounter(counter), 3);
    if (counter != 2)
    {
        throw MushcoreCommandFail("Overwrite fault 1");
    }
    
    maptor.Get(3);
    
    maptor.Clear();
    
    if (counter != 0 || maptor.size() != 0)
    {
        throw MushcoreCommandFail("Clear fault 1");
    }
    
    excepted = false;
    try
    {
        maptor.Get(3);        
    }
    catch (MushcoreNonFatalFail& e)
    {
        excepted = true;
    }
    if (!excepted)
    {
        throw MushcoreCommandFail("Get fault 1");
        
    }
    
    maptor.push_back(TestMushcoreCounter(counter));
    maptor.push_back(TestMushcoreCounter(counter));
    maptor.push_back(TestMushcoreCounter(counter));
    
    if (counter != 3 || maptor.size() != 3)
    {
        cout << "Counter = " << counter << ", size=" << maptor.size() << endl;;
        throw MushcoreCommandFail("Counter fault 4");
    }
    if (!maptor.GetIfExists(result, 0) ||
        !maptor.GetIfExists(result, 1) ||
        !maptor.GetIfExists(result, 2))
    {
        throw MushcoreCommandFail("push_back fault 1");
    }
    maptor.pop_back();
    if (!maptor.GetIfExists(result, 0) ||
        !maptor.GetIfExists(result, 1) ||
        maptor.GetIfExists(result, 2) ||
        counter != 2)
    {
        throw MushcoreCommandFail("pop_back fault 1");
    }
    
    return MushcoreScalar(0);
}

void
TestMushcoreMaptor::Install(void)
{
    MushcoreInterpreter::Sgl().HandlerAdd("testmushcoremaptor", TestMaptor);
}
