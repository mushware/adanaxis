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
 * $Id$
 * $Log$
 */

#include "TestMushPiePieces.h"

using namespace Mushware;
using namespace std;

MushPiePosicity
TestMushPiePieces::TestPosMake(tVal inKey)
{
    MushPiePosicity pos;
    pos.pos = t3Val(inKey, inKey+1, inKey+2);
    pos.vel = t3Val(inKey+3, inKey+4, inKey+5);
    pos.angPos = tQVal(inKey+6, inKey+7, inKey+8, inKey+9);
    pos.angVel = tQVal(inKey+10, inKey+11, inKey+12, inKey+13);
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
        
        testObject.NewPosSet(TestPosMake(0));
        testObject.PosSwap();
        testObject.NewPosSet(TestPosMake(100));
        
        xmlOStream << testObject;
        
        MushcoreXMLOStream xmlCout(cout);

        xmlCout << testObject;

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
