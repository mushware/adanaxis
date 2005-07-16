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
 * $Id: AdanaxisUtil.cpp,v 1.10 2005/07/14 16:55:08 southa Exp $
 * $Log: AdanaxisUtil.cpp,v $
 * Revision 1.10  2005/07/14 16:55:08  southa
 * Mesh library work
 *
 * Revision 1.9  2005/07/14 12:50:30  southa
 * Extrusion work
 *
 * Revision 1.8  2005/07/13 20:35:47  southa
 * Extrusion work
 *
 * Revision 1.7  2005/07/13 16:45:04  southa
 * Extrusion work
 *
 * Revision 1.6  2005/07/12 20:39:04  southa
 * Mesh library work
 *
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
    
    for (U32 i=0; i<10; ++i)
    {
        decoListRef.push_back(AdanaxisPieceDeco("testObj1"));
        AdanaxisVolatileData::tDeco& decoRef = decoListRef.back();
        
        decoRef.PostWRef().PosSet(t4Val(MushMeshTools::Random(-1,1),MushMeshTools::Random(-1,1),MushMeshTools::Random(-1,1),MushMeshTools::Random(-1,1)));
        
        decoRef.PostWRef().PosWRef() *= 20;
        
        tQValPair orientation = MushMeshTools::RandomOrientation();
        decoRef.PostWRef().AngPosSet(orientation);
        decoRef.PostWRef().AngVelWRef().ToRotationIdentitySet();
        
        if (i % 4 > 1)
        {
            decoRef.PostWRef().AngVelWRef().OuterMultiplyBy(orientation);
            
            decoRef.PostWRef().AngVelWRef().OuterMultiplyBy(MushMeshTools::QuaternionRotateInAxis
                                                 (0, MushMeshTools::Random(rotMin, rotMax)));
            decoRef.PostWRef().AngVelWRef().OuterMultiplyBy(MushMeshTools::QuaternionRotateInAxis
                                                 (1, MushMeshTools::Random(rotMin, rotMax)));
            
            decoRef.PostWRef().AngVelWRef().OuterMultiplyBy(orientation.ConjugateGet());
        }

        MushMeshLibraryFGenExtrude faceExtrude;
        MushMeshLibraryVGenExtrude vertexExtrude;
        tQValPair rotation;
        rotation.ToRotationIdentitySet();
        MushMeshDisplacement disp(t4Val(0,0,0,1), rotation, 0.5);
        
        MushMeshLibraryExtrusionContext extrusionContext(disp, 0);
        switch (i % 3)
        {
            case 0:
            {
                MushMeshLibraryBase::Sgl().PolygonPrismCreate(decoRef.MeshWRef(), t4Val(1,1,0.5,3), 6);            
                
            }
            break;
                
            case 1:
            {
                MushMeshLibraryBase::Sgl().UnitTesseractCreate(decoRef.MeshWRef());
                //MushMeshLibraryBase::Sgl().PolygonPrismCreate(decoRef.MeshWRef(), t4Val(1,1,0.5,3), 6);            
                for (U32 j=0; j<8; ++j)
                {
                    extrusionContext.ResetNewFace(j);
                    faceExtrude.FaceExtrude(decoRef.MeshWRef(), extrusionContext, 1);
                }
                disp.ScaleSet(0.3);
                tVal dist = 3.0;
                disp.OffsetSet(t4Val(0,0,0,dist));
                extrusionContext.ResetNewDispFace(disp, 0);
                vertexExtrude.FaceExtrude(decoRef.MeshWRef(), extrusionContext, 1);
                disp.OffsetSet(t4Val(0,0,0,-dist));
                extrusionContext.ResetNewDispFace(disp, 1);
                vertexExtrude.FaceExtrude(decoRef.MeshWRef(), extrusionContext, 1);
                disp.OffsetSet(t4Val(0,0,dist,0));
                extrusionContext.ResetNewDispFace(disp, 2);
                vertexExtrude.FaceExtrude(decoRef.MeshWRef(), extrusionContext, 1);
                disp.OffsetSet(t4Val(0,0,-dist,0));
                extrusionContext.ResetNewDispFace(disp, 3);
                vertexExtrude.FaceExtrude(decoRef.MeshWRef(), extrusionContext, 1);
                disp.OffsetSet(t4Val(0,dist,0,0));
                extrusionContext.ResetNewDispFace(disp, 4);
                vertexExtrude.FaceExtrude(decoRef.MeshWRef(), extrusionContext, 1);
                disp.OffsetSet(t4Val(0,-dist,0,0));
                extrusionContext.ResetNewDispFace(disp, 5);
                vertexExtrude.FaceExtrude(decoRef.MeshWRef(), extrusionContext, 1);
                disp.OffsetSet(t4Val(dist,0,0,0));
                extrusionContext.ResetNewDispFace(disp, 6);
                vertexExtrude.FaceExtrude(decoRef.MeshWRef(), extrusionContext, 1);
                disp.OffsetSet(t4Val(-dist,0,0,0));
                extrusionContext.ResetNewDispFace(disp, 7);
                vertexExtrude.FaceExtrude(decoRef.MeshWRef(), extrusionContext, 1);     
            }
            break;
            
            case 2:
            {
                //MushMeshLibraryBase::Sgl().UnitTesseractCreate(decoRef.MeshWRef());
                MushMeshLibraryBase::Sgl().PolygonPrismCreate(decoRef.MeshWRef(), t4Val(1,1,1,1), 12);            
                U32 number = 12;
                t4Val offset(0,0,0,-1);
                if (i % 1 == 0)
                {
                    disp.RotationWRef().OuterMultiplyBy(MushMeshTools::QuaternionRotateInAxis
                                                        (1, M_PI/number));
                    MushMeshTools::QuaternionRotateInAxis(1, 0.5*M_PI/number).VectorRotate(offset);
                    disp.OffsetSet(offset);
                    extrusionContext.DispSet(disp);
                }
                extrusionContext.ScaleVelocitySet(1.0/number);
                extrusionContext.ResetNewFace(0);
                faceExtrude.FaceExtrude(decoRef.MeshWRef(), extrusionContext, number);
                extrusionContext.ResetNewFace(1);
                faceExtrude.FaceExtrude(decoRef.MeshWRef(), extrusionContext, number);

                disp.OffsetSet(offset);
                extrusionContext.ResetNewDispFace(disp, 0);
                vertexExtrude.FaceExtrude(decoRef.MeshWRef(), extrusionContext, number);
                offset.WSet(-offset.W());
                disp.OffsetSet(offset);
                disp.RotationSet(disp.Rotation().ConjugateGet());
                extrusionContext.ResetNewDispFace(disp, 1);
                vertexExtrude.FaceExtrude(decoRef.MeshWRef(), extrusionContext, number);
            }
            break;
        }
    }
}

