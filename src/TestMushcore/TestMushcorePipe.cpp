//%Header {
/*****************************************************************************
 *
 * File: src/TestMushcore/TestMushcorePipe.cpp
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
//%Header } aaas2OEWsO6x4IW9qc0DIg
/*
 * $Id: TestMushcorePipe.cpp,v 1.2 2006/06/01 15:40:05 southa Exp $
 * $Log: TestMushcorePipe.cpp,v $
 * Revision 1.2  2006/06/01 15:40:05  southa
 * DrawArray verification and fixes
 *
 * Revision 1.1  2005/06/13 14:25:47  southa
 * Pipe and ordered data work
 *
 */

#include "TestMushcorePipe.h"

#include "TestMushcoreCounter.h"

using namespace Mushware;
using namespace std;

MushcoreInstaller TestMushcorePipeInstaller(TestMushcorePipe::Install);

MushcoreScalar
TestMushcorePipe::TestPipe(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    U32 counter=0;
    MushcorePipe<TestMushcoreCounter> pipe(0);
    
    bool excepted = false;
    
    try
    {
        pipe.Give(new TestMushcoreCounter(counter));
    }
    catch (MushcoreNonFatalFail& e)
    {
        excepted = true;
    }
    
    if (!excepted)
    {
        ostringstream message;
        message << "Pipe absent exception 1: " << pipe;
        throw MushcoreCommandFail(message.str());
    }
    pipe.NotAccessingSoGrow(16);
    
    excepted = false;
    
    try
    {
        pipe.Give(new TestMushcoreCounter(counter));
    }
    catch (MushcoreNonFatalFail& e)
    {
        excepted = true;
    }
    
    if (!excepted)
    {
        throw MushcoreCommandFail("No exception when expected 1");
    }
    pipe.NotAccessingSoGrow(16);
    
    try
    {
        pipe.Give(new TestMushcoreCounter(counter));
    }
    catch (MushcoreNonFatalFail& e)
    {
        ostringstream message;
        message << "Pipe exception 2: " << pipe;
        throw MushcoreCommandFail(message.str());
    }
    
    U32 i;
    for (i=0; i<16; ++i)
    {
        try
        {
            pipe.NotAccessingSoGrow(16);
            pipe.Give(new TestMushcoreCounter(counter));
        }
        catch (MushcoreNonFatalFail& e)
        {
            break;
        }
    }
    
    if (i != 14)
    {
        ostringstream message;
        message << "Pipe exception 3: (i=" << i << ") " << pipe;
        throw MushcoreCommandFail(message.str());
    }

    for (i=0; i<4; ++i)
    {
        pipe.TopDelete();
    }
    
    for (i=0; i<16; ++i)
    {
        try
        {
            pipe.NotAccessingSoGrow(16);
            pipe.Give(new TestMushcoreCounter(counter));
        }
        catch (MushcoreNonFatalFail& e)
        {
            break;
        }
    }
    
    if (i != 4)
    {
        ostringstream message;
        message << "Pipe exception 4: (i=" << i << ") " << pipe;
        throw MushcoreCommandFail(message.str());
    }
    
    if (counter != 15)
    {
        ostringstream message;
        message << "Pipe exception 5: (counter=" << counter << ") " << pipe;
        throw MushcoreCommandFail(message.str());
    }
    
    const TestMushcoreCounter *pBool;
    
    for (i=0; i<16; ++i)
    {
        pBool = NULL;
        if (pipe.TopGet(pBool))
        {
            MUSHCOREASSERT(pBool != NULL);
            pipe.TopDelete();
        }
        else
        {
            break;
        }
    }
    
    if (i != 15)
    {
        ostringstream message;
        message << "Pipe exception 6: (i=" << i << ") " << pipe;
        throw MushcoreCommandFail(message.str());
    }
    
    try
    {
        pipe.TopDelete();
        ostringstream message;
        message << "Pipe exception 7: " << pipe;
        throw MushcoreCommandFail(message.str());
    }
    catch (...)
    {
    }
    
    if (counter != 0)
    {
        ostringstream message;
        message << "Pipe exception 8: (counter=" << counter << ") " << pipe;
        throw MushcoreCommandFail(message.str());
    }
    
    /* Test wrapping fix on resize */
    for (U32 j=0; j<2; ++j)
    {
        MushcorePipe<Mushware::U32> pipe2(8);
        
        for (i=1; i<6; ++i) pipe2.Give(new U32(i));
        for (i=1; i<4; ++i) pipe2.TopDelete();
        for (i=6; i<11; ++i) pipe2.Give(new U32(i));
        if (j == 0)
        {
            pipe2.NotAccessingSoGrow(16);
        }
  
        for (i=4; i<16; ++i)
        {
            const U32 *pU32 = NULL;
            if (pipe2.TopGet(pU32))
            {
                MUSHCOREASSERT(pU32 != NULL);
                if (*pU32 != i)
                {
                    ostringstream message;
                    message << "Pipe exception 10: (i=" << i << ", *pU32=" << *pU32 <<") " << pipe2;
                    throw MushcoreCommandFail(message.str());
                }
                pipe2.TopDelete();
            }
            else
            {
                break;
            }
        }
        
        if (i != 11)
        {
            ostringstream message;
            message << "Pipe exception 11: (i=" << i << ") " << pipe2;
            throw MushcoreCommandFail(message.str());
        }
    }
    
    // Test deletion in pipe destructor
    {
        MushcorePipe<TestMushcoreCounter> pipe3(4);
        pipe3.Give(new TestMushcoreCounter(counter));
        if (counter != 1)
        {
            ostringstream message;
            message << "Pipe exception 20: (counter=" << counter << ") " << pipe3;
            throw MushcoreCommandFail(message.str());
        }
    }
    if (counter != 0)
    {
        ostringstream message;
        message << "Pipe exception 21: (counter=" << counter << ")";
        throw MushcoreCommandFail(message.str());
    }
    
    return MushcoreScalar(0);
}

void
TestMushcorePipe::Install(void)
{
    MushcoreInterpreter::Sgl().HandlerAdd("testmushcorepipe", TestPipe);
}
