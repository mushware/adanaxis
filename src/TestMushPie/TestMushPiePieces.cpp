//%Header {
/*****************************************************************************
 *
 * File: src/TestMushPie/TestMushPiePieces.cpp
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
//%Header } 6bmE3jRVSFHgEujtQwtmWw
/*
 * $Id: TestMushPiePieces.cpp,v 1.6 2006/06/01 15:40:03 southa Exp $
 * $Log: TestMushPiePieces.cpp,v $
 * Revision 1.6  2006/06/01 15:40:03  southa
 * DrawArray verification and fixes
 *
 * Revision 1.5  2005/05/19 13:02:23  southa
 * Mac release work
 *
 * Revision 1.4  2005/02/10 12:34:21  southa
 * Template fixes
 *
 * Revision 1.3  2004/09/27 22:42:11  southa
 * MSVC compilation fixes
 *
 * Revision 1.2  2004/01/06 10:08:51  southa
 * MushcoreData and MushPieForm work
 *
 * Revision 1.1  2004/01/06 00:34:56  southa
 * MushPie testing
 *
 */

#include "TestMushPiePieces.h"

using namespace Mushware;
using namespace std;

MushPiePosicity
TestMushPiePieces::TestPosMake(tVal inKey)
{
    MushPiePosicity pos;
    pos.pos = t4Val(inKey, inKey+1, inKey+2, inKey+3);
    pos.vel = t4Val(inKey+4, inKey+5, inKey+6, inKey+7);
    pos.angPos = tQValPair(tQVal(inKey+8, inKey+9, inKey+10, inKey+11),
                           tQVal(inKey+12, inKey+13, inKey+14, inKey+15));
    pos.angVel = tQValPair(tQVal(inKey+16, inKey+17, inKey+18, inKey+19),
                           tQVal(inKey+20, inKey+21, inKey+22, inKey+23));

    return pos;
}

MushcoreScalar
TestMushPiePieces::TestPieces(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    // serial stream test
    {
        ostringstream testOStream;
        MushcoreXMLOStream xmlOStream(testOStream);
        MushPiePieceMobile testObject;
        
		testObject.SleepStateSet(static_cast<MushPiePiece::tSleepState>(1));
        testObject.FormRefSet(MushPieForm::tDataRef(2));
        testObject.NewPosSet(TestPosMake(0));
        testObject.PosSwap();
        testObject.NewPosSet(TestPosMake(100));
        
        xmlOStream << testObject;
        
        // MushcoreXMLOStream xmlCout(cout);
        // xmlCout << testObject;

        MushPiePieceMobile readBackObject;
        istringstream testIStream(testOStream.str());
        MushcoreXMLIStream xmlIStream(testIStream);

        xmlIStream >> readBackObject;
        
        if (testObject != readBackObject)
        {
            ostringstream message;
            message << "MushPiePiece readback fault '"+testOStream.str()+"', " << testObject << " != " << readBackObject;
            throw MushcoreCommandFail(message.str());
        }
    }
    return MushcoreScalar(0);
}

void
TestMushPiePieces::Install(void)
{
    MushcoreInterpreter::Sgl().HandlerAdd("testmushpiepieces", TestPieces);
}

namespace { MushcoreInstaller Installer(TestMushPiePieces::Install); }
