//%Header {
/*****************************************************************************
 *
 * File: src/TestMushPie/TestMushPiePieces.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } Ga1VHTuO8JZwOaZYl4bW2g
/*
 * $Id: TestMushPiePieces.cpp,v 1.3 2004/09/27 22:42:11 southa Exp $
 * $Log: TestMushPiePieces.cpp,v $
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
