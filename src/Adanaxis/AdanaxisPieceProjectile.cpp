//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisPieceProjectile.cpp
 *
 * Copyright: Andy Southgate 2005-2007
 *
 * This file may be used and distributed under the terms of the Mushware
 * Software Licence version 1.3, under the terms for 'Proprietary original
 * source files'.  If not supplied with this software, a copy of the licence
 * can be obtained from Mushware Limited via http://www.mushware.com/.
 * One of your options under that licence is to use and distribute this file
 * under the terms of the GNU General Public Licence version 2.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } pQ5BRw+L1Th8huxU49D5bg
/*
 * $Id: AdanaxisPieceProjectile.cpp,v 1.20 2007/04/18 09:22:02 southa Exp $
 * $Log: AdanaxisPieceProjectile.cpp,v $
 * Revision 1.20  2007/04/18 09:22:02  southa
 * Header and level fixes
 *
 * Revision 1.19  2006/11/12 20:09:54  southa
 * Missile guidance
 *
 * Revision 1.18  2006/11/12 14:39:50  southa
 * Player weapons amd audio fix
 *
 * Revision 1.17  2006/10/30 17:03:51  southa
 * Remnants creation
 *
 * Revision 1.16  2006/10/17 11:05:55  southa
 * Expiry events
 *
 * Revision 1.15  2006/10/12 22:04:47  southa
 * Collision events
 *
 * Revision 1.14  2006/10/04 13:35:23  southa
 * Selective targetting
 *
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
    RubyPieceConstructor(inID, inParams, AdanaxisIntern::Sgl().AdanaxisPieceProjectile());
}

AdanaxisPieceProjectile::~AdanaxisPieceProjectile()
{
    RubyPieceDestructor();    
}

void
AdanaxisPieceProjectile::Move(MushGameLogic& ioLogic, const tVal inFrameslice)
{
    MushGamePiece::Move(ioLogic, inFrameslice);

    PostWRef().InPlaceVelocityAdd();

    if (m_acceleration != 0.0)
    {
        if (m_speedLimit * m_speedLimit > Post().Vel().MagnitudeSquared())
        {
            t4Val accVec(0,0,0,-m_acceleration);
            Post().AngPos().VectorRotate(accVec);
            PostWRef().VelWRef() += accVec;
        }
    }
    
    if (m_launchMsec == 0)
    {
        m_launchMsec = ioLogic.FrameMsec();
    }
    if (ioLogic.FrameMsec() > m_launchMsec + m_lifeMsec)
    {
        ExpireFlagSet(true);
        RubyEventHandle(MushGameEvents::Sgl().EventExpiryMake());
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
    
    tVal alpha =  1.0;
    
    if (AlphaStutter() > 0.0)
    {
        alpha = MushcoreUtil::RandomVal(alpha * (1-AlphaStutter()), alpha);
    }
    inRender.ColourZMiddleSet(inRender.ColourZMiddle().ElementwiseProduct(t4Val(1,1,1,alpha)));

    bool jobCreated = inRender.RenderJobCreate(outRender, renderSpec, Mesh());
    return jobCreated;
}

void
AdanaxisPieceProjectile::MessageConsume(MushGameLogic& ioLogic, const MushGameMessage& inMessage)
{
    // Pass to base class
    MushGamePiece::MessageConsume(ioLogic, inMessage);
}

void
AdanaxisPieceProjectile::Load(Mushware::tRubyValue inSelf)
{
    MushGamePiece::Load(inSelf);
    MushRubyUtil::InstanceVarSet(inSelf, MushRubyIntern::ATm_owner(), MushRubyValue(m_owner).Value());    
    MushRubyUtil::InstanceVarSet(inSelf, MushRubyIntern::ATm_lifeMsec(), MushRubyValue(static_cast<U32>(m_lifeMsec)).Value());    
    MushRubyUtil::InstanceVarSet(inSelf, AdanaxisIntern::Sgl().ATm_acceleration(), MushRubyValue(m_acceleration).Value());    
    MushRubyUtil::InstanceVarSet(inSelf, AdanaxisIntern::Sgl().ATm_speedLimit(), MushRubyValue(m_speedLimit).Value());    
}

void
AdanaxisPieceProjectile::Save(Mushware::tRubyValue inSelf)
{
    MushGamePiece::Save(inSelf);
    m_owner = MushRubyValue(MushRubyUtil::InstanceVar(inSelf, MushRubyIntern::ATm_owner())).String();
    m_lifeMsec = MushRubyValue(MushRubyUtil::InstanceVar(inSelf, MushRubyIntern::ATm_lifeMsec())).U32();
    m_acceleration = MushRubyValue(MushRubyUtil::InstanceVar(inSelf, AdanaxisIntern::Sgl().ATm_acceleration())).Val();
    m_speedLimit = MushRubyValue(MushRubyUtil::InstanceVar(inSelf, AdanaxisIntern::Sgl().ATm_speedLimit())).Val();
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
	    m_rubyKlass = MushRubyUtil::SubclassDefine("AdanaxisPieceProjectile", AdanaxisPiece::Klass());
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
    ioOut << "launchMsec=" << m_launchMsec << ", ";
    ioOut << "acceleration=" << m_acceleration << ", ";
    ioOut << "speedLimit=" << m_speedLimit;
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
    else if (inTagStr == "acceleration")
    {
        ioIn >> m_acceleration;
    }
    else if (inTagStr == "speedLimit")
    {
        ioIn >> m_speedLimit;
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
    ioOut.TagSet("acceleration");
    ioOut << m_acceleration;
    ioOut.TagSet("speedLimit");
    ioOut << m_speedLimit;
}
//%outOfLineFunctions } mv03bToCvrVPzqZD3pMXVQ
