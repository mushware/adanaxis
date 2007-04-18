//%Header {
/*****************************************************************************
 *
 * File: src/TestMushPie/TestMushPiePieces.cpp
 *
 * Author: Andy Southgate 2002-2007
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
//%Header } HG9wy1YiD+IhLdcZ6Vnaog
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
