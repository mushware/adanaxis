//%Header {
/*****************************************************************************
 *
 * File: src/TestMushcore/TestMushcoreMaptor.cpp
 *
 * Author: Andy Southgate 2002-2006
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
//%Header } ietMVQFNbSPIPNpSC2q+eA
/*
 * $Id: TestMushcoreMaptor.cpp,v 1.3 2005/07/29 18:51:28 southa Exp $
 * $Log: TestMushcoreMaptor.cpp,v $
 * Revision 1.3  2005/07/29 18:51:28  southa
 * Maptor tweaks
 *
 * Revision 1.2  2005/07/29 14:59:51  southa
 * Maptor access
 *
 * Revision 1.1  2005/07/29 11:53:41  southa
 * MushcoreMaptor created
 *
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
    
    if (maptor.erase(6) != 1 || counter != 2 || maptor.size() != 4)
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
    
    // Iterators
    MushcoreMaptor<U32> u32Maptor;
    u32Maptor.push_back(3);
    u32Maptor.push_back(7);
    u32Maptor.push_back(1);
    
    MushcoreMaptor<U32>::iterator endIter = u32Maptor.end();
    U32 sum = 0;
    for (MushcoreMaptor<U32>::iterator p = u32Maptor.begin(); p != endIter;)
    {
        sum += *p;
        if (*p == 7)
        {
            u32Maptor.Delete(p++);
        }
        else
        {
            ++p;
        }
    }
    
    if (sum != 11 || u32Maptor.size() != 3)
    {
        throw MushcoreCommandFail("Iterator fault 1");
    }
    
    MushcoreMaptor<U32>::const_iterator endConstIter = u32Maptor.end();
    sum = 0;
    for (MushcoreMaptor<U32>::const_iterator p = u32Maptor.begin(); p != endConstIter; ++p)
    {
        sum += *p;
    }
    
    if (sum != 4)
    {
        throw MushcoreCommandFail("Iterator fault 2");
    }
    
    // References
    MushcoreMaptor<U32>::tRef ref0(u32Maptor, 0);
    MushcoreMaptor<U32>::tRef ref1(u32Maptor, 1);
    MushcoreMaptor<U32>::tRef ref2(u32Maptor, 2);
    
    if (*ref0 != 3 || *ref2 != 1)
    {
        throw MushcoreCommandFail("Reference fault 1");        
    }
    excepted = false;
    try
    {
        *ref1;
    }
    catch (MushcoreNonFatalFail& e)
    {
        excepted = true;
    }
    if (!excepted)
    {
        throw MushcoreCommandFail("Reference fault 2");
    }
    
    maptor.resize(15);
    if (maptor.size() != 15)
    {
        throw MushcoreCommandFail("Size fault 1");        
    }
    maptor.resize(0);
    if (maptor.size() != 0)
    {
        throw MushcoreCommandFail("Size fault 2");        
    }
    maptor.resize(15);
    maptor.resize(7);
    if (maptor.size() != 7)
    {
        throw MushcoreCommandFail("Size fault 3");        
    }

    return MushcoreScalar(0);
}

void
TestMushcoreMaptor::Install(void)
{
    MushcoreInterpreter::Sgl().HandlerAdd("testmushcoremaptor", TestMaptor);
}
