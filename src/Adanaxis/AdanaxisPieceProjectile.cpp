//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisPieceProjectile.cpp
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
//%Header } AKn0HlU4NeCX3ptHFWodSQ
/*
 * $Id: AdanaxisPieceProjectile.cpp,v 1.13 2006/10/03 14:06:51 southa Exp $
 * $Log: AdanaxisPieceProjectile.cpp,v $
 * Revision 1.13  2006/10/03 14:06:51  southa
 * Khazi and projectile creation
 *
 * Revision 1.12  2006/09/09 11:16:39  southa
 * One-time vertex buffer generation
 *
 * Revision 1.11  2006/08/25 01:44:57  southa
 * Khazi fire
 *
 * Revision 1.10  2006/08/01 17:21:25  southa
 * River demo
 *
 * Revision 1.9  2006/07/24 18:46:47  southa
 * Depth sorting
 *
 * Revision 1.8  2006/07/19 14:34:51  southa
 * Flare effects
 *
 * Revision 1.7  2006/06/30 15:05:32  southa
 * Texture and buffer purge
 *
 * Revision 1.6  2006/06/21 12:17:55  southa
 * Ruby object generation
 *
 * Revision 1.5  2006/06/01 15:38:48  southa
 * DrawArray verification and fixes
 *
 * Revision 1.4  2005/08/01 13:09:57  southa
 * Collision messaging
 *
 * Revision 1.3  2005/07/19 10:08:06  southa
 * Adanaxis work
 *
 * Revision 1.2  2005/07/18 13:13:36  southa
 * Extrude to point and projectile mesh
 *
 * Revision 1.1  2005/07/12 12:18:17  southa
 * Projectile work
 *
 */

#include "AdanaxisPieceProjectile.h"

#include "AdanaxisIntern.h"
#include "AdanaxisRuby.h"
#include "AdanaxisSaveData.h"
#include "AdanaxisUtil.h"

#include "API/mushMushMeshRuby.h"

Mushware::tRubyValue AdanaxisPieceProjectile::m_rubyKlass = Mushware::kRubyQnil;

using namespace Mushware;
using namespace std;

AdanaxisPieceProjectile::AdanaxisPieceProjectile(const std::string& inID, const MushRubyValue& inParams) :
    MushGamePiece(inID),
    m_launchMsec(0)
{
    RubyPieceConstructor(inID, inParams, AdanaxisIntern::Sgl().KlassAdanaxisPieceProjectile());
}

AdanaxisPieceProjectile::~AdanaxisPieceProjectile()
{
    RubyPieceDestructor();    
}

void
AdanaxisPieceProjectile::Move(MushGameLogic& ioLogic, const tVal inFrameslice)
{
    PostWRef().InPlaceVelocityAdd();

    if (m_launchMsec == 0)
    {
        m_launchMsec = ioLogic.FrameMsec();
    }
    if (ioLogic.FrameMsec() > m_launchMsec + m_lifeMsec)
    {
        Explode(ioLogic);
        ExpireFlagSet(true);
    }
}

bool
AdanaxisPieceProjectile::Render(MushGLJobRender& outRender,
    MushGameLogic& ioLogic, MushRenderMesh& inRender, const MushGameCamera& inCamera)
{
    MushRenderSpec renderSpec;
    renderSpec.BuffersRefSet(BuffersRef());
    renderSpec.SharedBuffersRefSet(SharedBuffersRef());
    
    MushMeshOps::PosticityToMattress(renderSpec.ModelWRef(), Post());
    MushMeshOps::PosticityToMattress(renderSpec.ViewWRef(), inCamera.Post());
    renderSpec.ViewWRef().InPlaceInvert();
    
    renderSpec.ProjectionSet(inCamera.Projection());
    
    bool jobCreated = inRender.RenderJobCreate(outRender, renderSpec, Mesh());
    return jobCreated;
}

void
AdanaxisPieceProjectile::CollisionFatalConsume(MushGameLogic& ioLogic, const MushGameMessageCollisionFatal& inMessage)
{
    Explode(ioLogic);
    ExpireFlagSet(true);
}    

void
AdanaxisPieceProjectile::MessageConsume(MushGameLogic& ioLogic, const MushGameMessage& inMessage)
{
    const MushGameMessageCollisionFatal *pCollisionFatal;
    
    if ((pCollisionFatal = dynamic_cast<const MushGameMessageCollisionFatal *>(&inMessage)) != NULL)
    {
        CollisionFatalConsume(ioLogic, *pCollisionFatal);
    }
    else
    {
        // Pass to base class
        MushGamePiece::MessageConsume(ioLogic, inMessage);
    }
}

void
AdanaxisPieceProjectile::Explode(MushGameLogic& ioLogic)
{
    MushMeshPosticity flarePost = Post();
    flarePost.VelWRef().ToAdditiveIdentitySet();
    
    AdanaxisUtil::FlareCreate(dynamic_cast<AdanaxisLogic&>(ioLogic), flarePost, 3, 0);
    for (U32 i=0; i<3; ++i)
    {
        AdanaxisUtil::EmberCreate(dynamic_cast<AdanaxisLogic&>(ioLogic),
                                  Post(),
                                  MushMeshTools::Random(0.1, 0.4), // size
                                  MushMeshTools::Random(0.1, 1)  // speed
                                  );
    }
}

void
AdanaxisPieceProjectile::Load(Mushware::tRubyValue inSelf)
{
    MushGamePiece::Load(inSelf);
    MushRubyUtil::InstanceVarSet(inSelf, MushRubyIntern::ATm_owner(), MushRubyValue(m_owner).Value());    
    MushRubyUtil::InstanceVarSet(inSelf, MushRubyIntern::ATm_lifeMsec(), MushRubyValue(static_cast<U32>(m_lifeMsec)).Value());    
}

void
AdanaxisPieceProjectile::Save(Mushware::tRubyValue inSelf)
{
    MushGamePiece::Save(inSelf);
    m_owner = MushRubyValue(MushRubyUtil::InstanceVar(inSelf, MushRubyIntern::ATm_owner())).String();
    m_lifeMsec = MushRubyValue(MushRubyUtil::InstanceVar(inSelf, MushRubyIntern::ATm_lifeMsec())).U32();
}

Mushware::tRubyValue
AdanaxisPieceProjectile::RubyCreate(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0)
{
        AdanaxisSaveData::tProjectileList& dataRef = AdanaxisRuby::SaveData().ProjectileListWRef();
        
        /* This object contains a reference (MushcoreMaptorRef) to an object
         * in SaveData().ProjectileList(), which is a MushcoreMaptor<AdanaxisPieceProjectile>.
         * The next line points the MushcoreMaptorRef at that MushcoreMaptor
         */
        AdanaxisSaveData::tProjectileList::key_type key = dataRef.NextKey();
        
        ostringstream idStream;
        idStream << key;
        
        AdanaxisPieceProjectile& objRef = *new AdanaxisPieceProjectile(idStream.str(), MushRubyValue(inArg0));
        dataRef.Give(&objRef, key);
        
        return objRef.RubyObj().Value();
}

Mushware::tRubyValue
AdanaxisPieceProjectile::Klass(void)
{
    if (m_rubyKlass == kRubyQnil)
    {
        RubyInstall();
    }
    return m_rubyKlass;
}    

void
AdanaxisPieceProjectile::RubyInstall(void)
{
    if (m_rubyKlass == kRubyQnil)
    {
	    m_rubyKlass = MushRubyUtil::SubclassDefine("AdanaxisPieceProjectile", MushGamePiece::Klass());
    }
	MushRubyUtil::SingletonMethodDefineOneParam(Klass(), "cCreate", RubyCreate);
}

namespace
{
	void Install(void)
	{
		MushRubyInstall::Sgl().Add(AdanaxisPieceProjectile::RubyInstall);
	}
	MushcoreInstaller install(Install);
}

//%outOfLineFunctions {

const char *AdanaxisPieceProjectile::AutoName(void) const
{
    return "AdanaxisPieceProjectile";
}

MushcoreVirtualObject *AdanaxisPieceProjectile::AutoClone(void) const
{
    return new AdanaxisPieceProjectile(*this);
}

MushcoreVirtualObject *AdanaxisPieceProjectile::AutoCreate(void) const
{
    return new AdanaxisPieceProjectile;
}

MushcoreVirtualObject *AdanaxisPieceProjectile::AutoVirtualFactory(void)
{
    return new AdanaxisPieceProjectile;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("AdanaxisPieceProjectile", AdanaxisPieceProjectile::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
AdanaxisPieceProjectile::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushGamePiece::AutoPrint(ioOut);
    ioOut << "owner=" << m_owner << ", ";
    ioOut << "lifeMsec=" << m_lifeMsec << ", ";
    ioOut << "launchMsec=" << m_launchMsec;
    ioOut << "]";
}
bool
AdanaxisPieceProjectile::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "owner")
    {
        ioIn >> m_owner;
    }
    else if (inTagStr == "lifeMsec")
    {
        ioIn >> m_lifeMsec;
    }
    else if (inTagStr == "launchMsec")
    {
        ioIn >> m_launchMsec;
    }
    else if (MushGamePiece::AutoXMLDataProcess(ioIn, inTagStr))
    {
        // Tag consumed by base class
    }
    else 
    {
        return false;
    }
    return true;
}
void
AdanaxisPieceProjectile::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushGamePiece::AutoXMLPrint(ioOut);
    ioOut.TagSet("owner");
    ioOut << m_owner;
    ioOut.TagSet("lifeMsec");
    ioOut << m_lifeMsec;
    ioOut.TagSet("launchMsec");
    ioOut << m_launchMsec;
}
//%outOfLineFunctions } nGrestPzIZ/DZtg9HdC84g
