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
 * $Id: AdanaxisUtil.cpp,v 1.17 2005/08/02 11:11:47 southa Exp $
 * $Log: AdanaxisUtil.cpp,v $
 * Revision 1.17  2005/08/02 11:11:47  southa
 * Adanaxis control demo work
 *
 * Revision 1.16  2005/08/01 20:24:15  southa
 * Backdrop and build fixes
 *
 * Revision 1.15  2005/08/01 13:09:57  southa
 * Collision messaging
 *
 * Revision 1.14  2005/07/30 19:06:14  southa
 * Collision checking
 *
 * Revision 1.13  2005/07/29 08:27:47  southa
 * Collision work
 *
 * Revision 1.12  2005/07/18 13:13:36  southa
 * Extrude to point and projectile mesh
 *
 * Revision 1.11  2005/07/16 14:22:59  southa
 * Added diagnostic renderer
 *
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
#include "AdanaxisMeshLibrary.h"
#include "AdanaxisSaveData.h"
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

AdanaxisMeshLibrary&
AdanaxisUtil::MeshLibrary(void)
{
    AdanaxisMeshLibrary *pMeshLibrary=dynamic_cast<AdanaxisMeshLibrary *>(&MushMeshLibraryBase::Sgl());
    if (pMeshLibrary == NULL)
    {
        throw MushcoreRequestFail("MeshLibrary of wrong type for AdanaxisMeshLibrary");
    }
    return *pMeshLibrary;
}

void
AdanaxisUtil::TestDecoCreate(AdanaxisLogic& ioLogic)
{
    AdanaxisVolatileData::tDecoList& decoListRef = ioLogic.VolatileData().DecoListWRef();

    tVal rotMin = -0.002;
    tVal rotMax = 0.002;
    
    for (U32 i=0; i<1000; ++i)
    {
        decoListRef.push_back(AdanaxisPieceDeco("decoObj1"));
        AdanaxisVolatileData::tDeco& objRef = decoListRef.back();
        
        objRef.PostWRef().PosSet(t4Val(MushMeshTools::Random(-1,1),MushMeshTools::Random(-1,1),MushMeshTools::Random(-1,1),MushMeshTools::Random(-1,1)));
        
        objRef.PostWRef().PosWRef().InPlaceNormalise();
        
        objRef.PostWRef().PosWRef() *= 50;
        
        tQValPair orientation = MushMeshTools::RandomOrientation();
        objRef.PostWRef().AngPosSet(orientation);
        objRef.PostWRef().AngVelWRef().ToRotationIdentitySet();
        
        {
            objRef.PostWRef().AngVelWRef().OuterMultiplyBy(orientation);
            
            objRef.PostWRef().AngVelWRef().OuterMultiplyBy(MushMeshTools::QuaternionRotateInAxis
                                                             (0, MushMeshTools::Random(rotMin, rotMax)));
            objRef.PostWRef().AngVelWRef().OuterMultiplyBy(MushMeshTools::QuaternionRotateInAxis
                                                             (1, MushMeshTools::Random(rotMin, rotMax)));
            
            objRef.PostWRef().AngVelWRef().OuterMultiplyBy(orientation.Conjugate());
        }
        
        MushMeshLibraryFGenExtrude faceExtrude;
        MushMeshLibraryVGenExtrude vertexExtrude;
        tQValPair rotation;
        rotation.ToRotationIdentitySet();
        MushMeshDisplacement disp(t4Val(0,0,0,1), rotation, 1);
        
        MushMeshLibraryExtrusionContext extrusionContext(disp, 0);
        switch (i % 30)
        {
            case 2:
            {
                MushMeshLibraryBase::Sgl().PolygonPrismCreate(objRef.MeshWRef(), t4Val(3,3,3,3), 5);            
            }
            break;
                                
            case 1:
            {
                MushMeshLibraryBase::Sgl().PolygonPrismCreate(objRef.MeshWRef(), t4Val(1,1,1,1), 3);            
                U32 number = 5;
                t4Val offset(0,0,0,-1);
                if (i % 1 == 0)
                {
                    disp.RotationWRef().OuterMultiplyBy(MushMeshTools::QuaternionRotateInAxis
                                                        (1, 0.5*M_PI/number));
                    MushMeshTools::QuaternionRotateInAxis(1, 0.5*M_PI/number).VectorRotate(offset);
                    disp.OffsetSet(offset);
                    extrusionContext.DispSet(disp);
                }
                extrusionContext.ScaleVelocitySet(-0.205);
                extrusionContext.ResetNewFace(0);
                faceExtrude.FaceExtrude(objRef.MeshWRef(), extrusionContext, number);
                extrusionContext.ResetNewFace(1);
                faceExtrude.FaceExtrude(objRef.MeshWRef(), extrusionContext, number);
                
                disp.OffsetSet(offset);
                extrusionContext.ResetNewDispFace(disp, 0);
                vertexExtrude.FaceExtrude(objRef.MeshWRef(), extrusionContext, number);
                offset.WSet(-offset.W());
                disp.OffsetSet(offset);
                disp.RotationSet(disp.Rotation().Conjugate());
                extrusionContext.ResetNewDispFace(disp, 1);
                vertexExtrude.FaceExtrude(objRef.MeshWRef(), extrusionContext, number);
            }
            break;
                
            case 0:
            default:
            {
                tVal scale=MushMeshTools::Random(0.1,0.2);
                MushMeshLibraryBase::Sgl().PolygonPrismCreate(objRef.MeshWRef(), scale * t4Val(1,1,1,1), 4);            
            }
            break;
        }
    }
}

void
AdanaxisUtil::TestPiecesCreate(AdanaxisLogic& ioLogic)
{
    AdanaxisSaveData::tKhaziList& khaziListRef = ioLogic.SaveData().KhaziListWRef();
    
    tVal rotMin = -0.03;
    tVal rotMax = 0.03;
    
    for (U32 i=0; i<30; ++i)
    {
        khaziListRef.push_back(AdanaxisPieceKhazi("testObj1"));
        AdanaxisSaveData::tKhazi& khaziRef = khaziListRef.back();
        
        khaziRef.PostWRef().PosSet(t4Val(MushMeshTools::Random(-1,1),MushMeshTools::Random(-1,1),MushMeshTools::Random(-1,1),MushMeshTools::Random(-1,1)));
        
        khaziRef.PostWRef().PosWRef() *= 50;
        
        tQValPair orientation = MushMeshTools::RandomOrientation();
        khaziRef.PostWRef().AngPosSet(orientation);
        khaziRef.PostWRef().AngVelWRef().ToRotationIdentitySet();
        
        if (i % 5 > 0)
        {
            khaziRef.PostWRef().AngVelWRef().OuterMultiplyBy(orientation);
            
            khaziRef.PostWRef().AngVelWRef().OuterMultiplyBy(MushMeshTools::QuaternionRotateInAxis
                                                 (0, MushMeshTools::Random(rotMin, rotMax)));
            khaziRef.PostWRef().AngVelWRef().OuterMultiplyBy(MushMeshTools::QuaternionRotateInAxis
                                                 (1, MushMeshTools::Random(rotMin, rotMax)));
            
            khaziRef.PostWRef().AngVelWRef().OuterMultiplyBy(orientation.Conjugate());
        }

        MushMeshLibraryFGenExtrude faceExtrude;
        MushMeshLibraryVGenExtrude vertexExtrude;
        tQValPair rotation;
        rotation.ToRotationIdentitySet();
        MushMeshDisplacement disp(t4Val(0,0,0,1), rotation, 0.5);
        
        MushMeshLibraryExtrusionContext extrusionContext(disp, 0);
        switch (i % 2)
        {
            case 2:
            {
                MushMeshLibraryBase::Sgl().PolygonPrismCreate(khaziRef.MeshWRef(), t4Val(1,1,0.5,3), 6);            
            }
            break;
                
            case 1:
            {
                MushMeshLibraryBase::Sgl().UnitTesseractCreate(khaziRef.MeshWRef());
                //MushMeshLibraryBase::Sgl().PolygonPrismCreate(khaziRef.MeshWRef(), t4Val(1,1,0.5,3), 6);            
                for (U32 j=0; j<8; ++j)
                {
                    extrusionContext.ResetNewFace(j);
                    faceExtrude.FaceExtrude(khaziRef.MeshWRef(), extrusionContext, 1);
                }
                disp.ScaleSet(0.3);
                tVal dist = 3.0;
                disp.OffsetSet(t4Val(0,0,0,dist));
                extrusionContext.ResetNewDispFace(disp, 0);
                vertexExtrude.FaceExtrude(khaziRef.MeshWRef(), extrusionContext, 1);
                disp.OffsetSet(t4Val(0,0,0,-dist));
                extrusionContext.ResetNewDispFace(disp, 1);
                vertexExtrude.FaceExtrude(khaziRef.MeshWRef(), extrusionContext, 1);
                disp.OffsetSet(t4Val(0,0,dist,0));
                extrusionContext.ResetNewDispFace(disp, 2);
                vertexExtrude.FaceExtrude(khaziRef.MeshWRef(), extrusionContext, 1);
                disp.OffsetSet(t4Val(0,0,-dist,0));
                extrusionContext.ResetNewDispFace(disp, 3);
                vertexExtrude.FaceExtrude(khaziRef.MeshWRef(), extrusionContext, 1);
                disp.OffsetSet(t4Val(0,dist,0,0));
                extrusionContext.ResetNewDispFace(disp, 4);
                vertexExtrude.FaceExtrude(khaziRef.MeshWRef(), extrusionContext, 1);
                disp.OffsetSet(t4Val(0,-dist,0,0));
                extrusionContext.ResetNewDispFace(disp, 5);
                vertexExtrude.FaceExtrude(khaziRef.MeshWRef(), extrusionContext, 1);
                disp.OffsetSet(t4Val(dist,0,0,0));
                extrusionContext.ResetNewDispFace(disp, 6);
                vertexExtrude.FaceExtrude(khaziRef.MeshWRef(), extrusionContext, 1);
                disp.OffsetSet(t4Val(-dist,0,0,0));
                extrusionContext.ResetNewDispFace(disp, 7);
                vertexExtrude.FaceExtrude(khaziRef.MeshWRef(), extrusionContext, 1);     
            }
            break;
            
            case 0:
            {
                //MushMeshLibraryBase::Sgl().UnitTesseractCreate(khaziRef.MeshWRef());
                MushMeshLibraryBase::Sgl().PolygonPrismCreate(khaziRef.MeshWRef(), t4Val(1,1,1,1), 5);            
                U32 number = 5;
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
                faceExtrude.FaceExtrude(khaziRef.MeshWRef(), extrusionContext, number);
                extrusionContext.ResetNewFace(1);
                faceExtrude.FaceExtrude(khaziRef.MeshWRef(), extrusionContext, number);

                disp.OffsetSet(offset);
                extrusionContext.ResetNewDispFace(disp, 0);
                vertexExtrude.FaceExtrude(khaziRef.MeshWRef(), extrusionContext, number);
                offset.WSet(-offset.W());
                disp.OffsetSet(offset);
                disp.RotationSet(disp.Rotation().Conjugate());
                extrusionContext.ResetNewDispFace(disp, 1);
                vertexExtrude.FaceExtrude(khaziRef.MeshWRef(), extrusionContext, number);
            }
            break;
                
            case 3:
            {
                MeshLibrary().ProjectileCreate(khaziRef.MeshWRef());
            }
            break;
        }
    }
}

