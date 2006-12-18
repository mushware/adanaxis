//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisUtil.cpp
 *
 * Copyright: Andy Southgate 2005-2006
 *
 * This file may be used and distributed under the terms of the Mushware
 * software licence version 1.1, under the terms for 'Proprietary original
 * source files'.  If not supplied with this software, a copy of the licence
 * can be obtained from Mushware Limited via http://www.mushware.com/.
 * One of your options under that licence is to use and distribute this file
 * under the terms of the GNU General Public Licence version 2.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } XsVs/rr7rRJFJzKi6eatxg
/*
 * $Id: AdanaxisUtil.cpp,v 1.36 2006/10/19 15:41:36 southa Exp $
 * $Log: AdanaxisUtil.cpp,v $
 * Revision 1.36  2006/10/19 15:41:36  southa
 * Item handling
 *
 * Revision 1.35  2006/10/15 17:12:54  southa
 * Scripted explosions
 *
 * Revision 1.34  2006/10/14 16:59:44  southa
 * Ruby Deco objects
 *
 * Revision 1.33  2006/10/06 11:54:57  southa
 * Scaled rendering
 *
 * Revision 1.32  2006/10/05 15:39:17  southa
 * Explosion handling
 *
 * Revision 1.31  2006/09/09 11:16:40  southa
 * One-time vertex buffer generation
 *
 * Revision 1.30  2006/08/01 17:21:30  southa
 * River demo
 *
 * Revision 1.29  2006/07/19 14:34:51  southa
 * Flare effects
 *
 * Revision 1.28  2006/06/21 16:52:29  southa
 * Deco objects
 *
 * Revision 1.27  2006/06/21 12:17:56  southa
 * Ruby object generation
 *
 * Revision 1.26  2006/06/14 18:45:46  southa
 * Ruby mesh generation
 *
 * Revision 1.25  2006/06/12 16:01:21  southa
 * Ruby mesh generation
 *
 * Revision 1.24  2006/06/09 21:07:12  southa
 * Tiled skin generation
 *
 * Revision 1.23  2006/06/08 20:17:30  southa
 * Texture tile generation method 2
 *
 * Revision 1.22  2006/06/07 12:15:18  southa
 * Grid and test textures
 *
 * Revision 1.21  2006/05/03 00:58:43  southa
 * Texturing updates
 *
 * Revision 1.20  2005/09/05 12:54:29  southa
 * Solid rendering work
 *
 * Revision 1.19  2005/08/29 18:40:56  southa
 * Solid rendering work
 *
 * Revision 1.18  2005/08/02 14:37:44  southa
 * Adanaxis control demo work
 *
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
#include "API/mushMushSkin.h"

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
AdanaxisUtil::MissingSkinsCreate(AdanaxisLogic& ioLogic)
{
    MushSkinTiled skinTiled;
    MushSkinSingular skinSingular;
    
	typedef MushcoreData<MushMesh4Mesh> tMeshData;
	
	tMeshData::iterator endIter = tMeshData::Sgl().end();
	for (tMeshData::iterator p = tMeshData::Sgl().begin(); p != endIter; ++p)
	{
        switch (p->second->MaterialRef(0).MappingType())
        {
            case MushMesh4Material::kMappingTypeNone:
                throw MushcoreDataFail("No mapping type specified for material '"+p->first+"'");
                break;

            case MushMesh4Material::kMappingTypeTiled:
                skinTiled.TexCoordsGenerate(*p->second);
                break;
                
            case MushMesh4Material::kMappingTypeSingular:
                skinSingular.TexCoordsGenerate(*p->second);
                break;
                
            default:
                throw MushcoreDataFail("Bad value for mapping type");
                break;
        }
		MushcoreData<MushGLBuffers>::Sgl().GetOrCreate(p->first);
	}
}

void
AdanaxisUtil::MeshPurge(AdanaxisLogic& ioLogic)
{
	typedef MushcoreData<MushMesh4Mesh> tMeshData;
	
	tMeshData::iterator endIter = tMeshData::Sgl().end();
	for (tMeshData::iterator p = tMeshData::Sgl().begin(); p != endIter; ++p)
	{
        MUSHCOREASSERT(p->second != NULL);
        p->second->Purge();
    }
}

void
AdanaxisUtil::TestDecoCreate(AdanaxisLogic& ioLogic)
{
    AdanaxisVolatileData::tDecoList& decoListRef = ioLogic.VolatileData().DecoListWRef();

    tVal rotMin = -0.002;
    tVal rotMax = 0.002;
    
    for (U32 i=0; i<100; ++i)
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
        MushMeshDisplacement disp(t4Val(0,0,0,1), rotation, t4Val(1,1,1,1));
        
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
    
    tVal rotMin = -0.01;
    tVal rotMax = 0.01;
    
    for (U32 i=0; i<10; ++i)
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

		khaziRef.MeshWRef() = *MushcoreData<MushMesh4Mesh>::Sgl().Get("attendant");
#if 0
        AdanaxisMeshLibrary::AdanaxisSgl().AttendantCreate(khaziRef.MeshWRef());
		AdanaxisMeshLibrary::AdanaxisSgl().AttendantVerticesSet(khaziRef.MeshWRef(), 1);
#endif
        //AdanaxisMeshLibrary::AdanaxisSgl().TesseractCreate(khaziRef.MeshWRef());
        khaziRef.MeshWRef().TexCoordDelegateSet(MushMesh4Mesh::tDataRef("attendant"));
        khaziRef.SharedBuffersNameSet("attendant");
    }
}

void
AdanaxisUtil::TestSkinsCreate(AdanaxisLogic& ioLogic)
{
    MushMesh4Mesh *p4Mesh = NULL;
    MushSkinTiled skinTiled;
    
    p4Mesh = MushcoreData<MushMesh4Mesh>::Sgl().Give("tesseract", new MushMesh4Mesh);
    AdanaxisMeshLibrary::AdanaxisSgl().TesseractCreate(*p4Mesh);
    
    skinTiled.TexCoordsGenerate(*p4Mesh);
    MushcoreData<MushGLBuffers>::Sgl().GetOrCreate("tesseract");
      
    p4Mesh = MushcoreData<MushMesh4Mesh>::Sgl().GetOrCreate("attendant");
#if 0
    AdanaxisMeshLibrary::AdanaxisSgl().AttendantCreate(*p4Mesh);
	AdanaxisMeshLibrary::AdanaxisSgl().AttendantVerticesSet(*p4Mesh, 1);
#endif

    skinTiled.TexCoordsGenerate(*p4Mesh);
    MushcoreData<MushGLBuffers>::Sgl().GetOrCreate("attendant");
    
    p4Mesh = MushcoreData<MushMesh4Mesh>::Sgl().Give("projectile", new MushMesh4Mesh);
    AdanaxisMeshLibrary::AdanaxisSgl().ProjectileCreate(*p4Mesh);
    
    skinTiled.TexCoordsGenerate(*p4Mesh);
    MushcoreData<MushGLBuffers>::Sgl().GetOrCreate("projectile");
}

void
AdanaxisUtil::FlareCreate(AdanaxisLogic& ioLogic, const MushMeshPosticity& inPost, Mushware::tVal inSize, Mushware::tVal inSpeed)
{
    ostringstream objNameStream;
    objNameStream << "flare" << MushcoreUtil::RandomU32(0, 10);
    std::string objName = objNameStream.str();
    
    AdanaxisVolatileData::tDecoList& decoListRef = ioLogic.VolatileData().DecoListWRef();
    
    decoListRef.push_back(AdanaxisPieceDeco("flareObj"));
    AdanaxisVolatileData::tDeco& objRef = decoListRef.back();
        
    objRef.LifeMsecSet(400);

    objRef.PostSet(inPost);
    objRef.PostWRef().VelWRef() += MushMeshTools::RandomUnitVector() * inSpeed;    
    objRef.PostWRef().AngPosWRef().ToRotationIdentitySet();
    objRef.PostWRef().AngVelWRef().ToRotationIdentitySet();
    
    objRef.MeshWRef() = *MushcoreData<MushMesh4Mesh>::Sgl().Get(objName);
    objRef.MeshWRef().TexCoordDelegateSet(MushMesh4Mesh::tDataRef(objName));
    objRef.SharedBuffersNameSet(objName);
    
    objRef.RenderScaleSet(t4Val(inSize, inSize, inSize, inSize));
}

void
AdanaxisUtil::EmberCreate(AdanaxisLogic& ioLogic, const MushMeshPosticity& inPost, Mushware::tVal inSize, Mushware::tVal inSpeed)
{
    ostringstream objNameStream;
    objNameStream << "ember" << MushcoreUtil::RandomU32(0, 10);
    std::string objName = objNameStream.str();
    
    
    AdanaxisVolatileData::tDecoList& decoListRef = ioLogic.VolatileData().DecoListWRef();
    
    decoListRef.push_back(AdanaxisPieceDeco("emberObj"));
    AdanaxisVolatileData::tDeco& objRef = decoListRef.back();
    

    objRef.PostSet(inPost);
    objRef.PostWRef().VelWRef() += MushMeshTools::RandomUnitVector() * inSpeed;    
    objRef.PostWRef().AngPosWRef().ToRotationIdentitySet();
    objRef.PostWRef().AngVelWRef().ToRotationIdentitySet();
    
    objRef.MeshWRef() = *MushcoreData<MushMesh4Mesh>::Sgl().Get(objName);
    objRef.MeshWRef().TexCoordDelegateSet(MushMesh4Mesh::tDataRef(objName));
    objRef.SharedBuffersNameSet(objName);
    
    
    objRef.RenderScaleSet(t4Val(inSize, inSize, inSize, inSize));
}


void
AdanaxisUtil::ExploCreate(AdanaxisLogic& ioLogic, const MushMeshPosticity& inPost, Mushware::tVal inSize, Mushware::tVal inSpeed)
{
    ostringstream objNameStream;
    objNameStream << "explo1";
    std::string objName = objNameStream.str();
    
    AdanaxisVolatileData::tDecoList& decoListRef = ioLogic.VolatileData().DecoListWRef();
    
    decoListRef.push_back(AdanaxisPieceDeco("exploObj"));
    AdanaxisVolatileData::tDeco& objRef = decoListRef.back();
    
    objRef.LifeMsecSet(2000);
    
    objRef.PostSet(inPost);
    objRef.PostWRef().AngPosWRef().ToRotationIdentitySet();
    objRef.PostWRef().AngVelWRef().ToRotationIdentitySet();
    
    objRef.MeshWRef() = *MushcoreData<MushMesh4Mesh>::Sgl().Get(objName);
    objRef.MeshWRef().TexCoordDelegateSet(MushMesh4Mesh::tDataRef(objName));
    objRef.SharedBuffersNameSet(objName);
    
    objRef.RenderScaleSet(t4Val(inSize, inSize, inSize, inSize));
}
