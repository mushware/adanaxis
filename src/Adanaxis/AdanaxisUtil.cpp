//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisUtil.cpp
 *
 * Copyright: Andy Southgate 2005
 *
 * This file may be used and distributed under the terms of the Mushware
 * software licence version 1.0, under the terms for 'Proprietary original
 * source files'.  If not supplied with this software, a copy of the licence
 * can be obtained from Mushware Limited via http://www.mushware.com/.
 * One of your options under that licence is to use and distribute this file
 * under the terms of the GNU General Public Licence version 2.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } CFEozIhAxC4/w3MDbuOShQ
/*
 * $Id: AdanaxisUtil.cpp,v 1.2 2005/07/01 10:03:30 southa Exp $
 * $Log: AdanaxisUtil.cpp,v $
 * Revision 1.2  2005/07/01 10:03:30  southa
 * Projection work
 *
 * Revision 1.1  2005/06/30 16:29:24  southa
 * Adanaxis work
 *
 */

#include "AdanaxisUtil.h"

#include "AdanaxisVolatileData.h"

using namespace Mushware;
using namespace std;

void
AdanaxisUtil::TestPiecesCreate(AdanaxisLogic& ioLogic)
{
    AdanaxisVolatileData::tDecoList& decoListRef = ioLogic.VolatileData().DecoListWRef();
    
    tVal rotMin = -0.03;
    tVal rotMax = 0.03;
    
    for (U32 i=0; i<10; ++i)
    {
        decoListRef.push_back(AdanaxisPieceDeco("testObj1"));
        AdanaxisVolatileData::tDeco& decoRef = decoListRef.back();
        
        decoRef.PostWRef().PosSet(t4Val(MushMeshTools::Random(-5,5),MushMeshTools::Random(-5,5),MushMeshTools::Random(-5,5),MushMeshTools::Random(-30,-5)));
        
        tQValPair orientation = MushMeshTools::RandomOrientation();
        decoRef.PostWRef().AngPosSet(orientation);
        decoRef.PostWRef().AngVelWRef().ToRotationIdentitySet();
        
        decoRef.PostWRef().AngVelWRef().OuterMultiplyBy(orientation);
        
        decoRef.PostWRef().AngVelWRef().OuterMultiplyBy(MushMeshTools::QuaternionRotateInAxis
                                             (0, MushMeshTools::Random(rotMin, rotMax)));
        decoRef.PostWRef().AngVelWRef().OuterMultiplyBy(MushMeshTools::QuaternionRotateInAxis
                                             (1, MushMeshTools::Random(rotMin, rotMax)));
        
        decoRef.PostWRef().AngVelWRef().OuterMultiplyBy(orientation.ConjugateGet());

        MushMesh4Library::Sgl().UnitTesseractCreate(decoRef.MeshWRef());
    }
}

