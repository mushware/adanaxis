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
 * $Id: AdanaxisUtil.cpp,v 1.5 2005/07/06 19:08:26 southa Exp $
 * $Log: AdanaxisUtil.cpp,v $
 * Revision 1.5  2005/07/06 19:08:26  southa
 * Adanaxis control work
 *
 * Revision 1.4  2005/07/05 13:52:22  southa
 * Adanaxis work
 *
 * Revision 1.3  2005/07/04 15:59:00  southa
 * Adanaxis work
 *
 * Revision 1.2  2005/07/01 10:03:30  southa
 * Projection work
 *
 * Revision 1.1  2005/06/30 16:29:24  southa
 * Adanaxis work
 *
 */

#include "AdanaxisUtil.h"

#include "AdanaxisAppHandler.h"
#include "AdanaxisVolatileData.h"

#include "API/mushMushMeshLibrary.h"

using namespace Mushware;
using namespace std;

AdanaxisAppHandler&
AdanaxisUtil::AppHandler(void)
{
    AdanaxisAppHandler *pAppHandler=dynamic_cast<AdanaxisAppHandler *>(&MushcoreAppHandler::Sgl());
    if (pAppHandler == NULL)
    {
        throw MushcoreRequestFail("AppHandler of wrong type for AdanaxisAppHandler");
    }
    return *pAppHandler;
}

void
AdanaxisUtil::TestPiecesCreate(AdanaxisLogic& ioLogic)
{
    AdanaxisVolatileData::tDecoList& decoListRef = ioLogic.VolatileData().DecoListWRef();
    
    tVal rotMin = -0.03;
    tVal rotMax = 0.03;
    
    for (U32 i=0; i<100; ++i)
    {
        decoListRef.push_back(AdanaxisPieceDeco("testObj1"));
        AdanaxisVolatileData::tDeco& decoRef = decoListRef.back();
        
        decoRef.PostWRef().PosSet(t4Val(MushMeshTools::Random(-1,1),MushMeshTools::Random(-1,1),MushMeshTools::Random(-1,1),MushMeshTools::Random(-1,1)));
        
        decoRef.PostWRef().PosWRef() *= 20;
        
        tQValPair orientation = MushMeshTools::RandomOrientation();
        decoRef.PostWRef().AngPosSet(orientation);
        decoRef.PostWRef().AngVelWRef().ToRotationIdentitySet();
        
        decoRef.PostWRef().AngVelWRef().OuterMultiplyBy(orientation);
        
        decoRef.PostWRef().AngVelWRef().OuterMultiplyBy(MushMeshTools::QuaternionRotateInAxis
                                             (0, MushMeshTools::Random(rotMin, rotMax)));
        decoRef.PostWRef().AngVelWRef().OuterMultiplyBy(MushMeshTools::QuaternionRotateInAxis
                                             (1, MushMeshTools::Random(rotMin, rotMax)));
        
        decoRef.PostWRef().AngVelWRef().OuterMultiplyBy(orientation.ConjugateGet());

        MushMeshLibraryBase::Sgl().UnitTesseractCreate(decoRef.MeshWRef());
        
        tQValPair rotation;
        rotation.ToRotationIdentitySet();
        MushMeshDisplacement disp(t4Val(0,0,0,1), rotation, 0.5);

        MushMeshLibraryFGenExtrude faceExtrude;
        faceExtrude.FaceExtrude(decoRef.MeshWRef(), 0, 1);

        MushMeshLibraryVGenExtrude vertexExtrude;
        vertexExtrude.FaceExtrude(decoRef.MeshWRef(), disp, 0, 1);
        static U32 ctr=0;
        if (ctr == 0)
        {
            ++ctr;
            MushcoreXMLOStream xmlOut(cout);
            xmlOut << decoRef.Mesh();
        }
    }
}

