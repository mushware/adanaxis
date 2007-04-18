//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisPieceEffector.cpp
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
//%Header } H4p36W9y6OtJCQWkz9j/3Q
/*
 * $Id: AdanaxisPieceEffector.cpp,v 1.2 2006/11/14 20:28:37 southa Exp $
 * $Log: AdanaxisPieceEffector.cpp,v $
 * Revision 1.2  2006/11/14 20:28:37  southa
 * Added rail gun
 *
 * Revision 1.1  2006/11/03 18:46:33  southa
 * Damage effectors
 *
 */

#include "AdanaxisPieceEffector.h"

#include "AdanaxisIntern.h"
#include "AdanaxisRuby.h"
#include "AdanaxisSaveData.h"
#include "AdanaxisUtil.h"

#include "API/mushMushMeshRuby.h"

Mushware::tRubyValue AdanaxisPieceEffector::m_rubyKlass = Mushware::kRubyQnil;

using namespace Mushware;
using namespace std;

AdanaxisPieceEffector::AdanaxisPieceEffector(const std::string& inID, const MushRubyValue& inParams) :
    MushGamePiece(inID),
    m_launchMsec(0)
{
    RubyPieceConstructor(inID, inParams, AdanaxisIntern::Sgl().AdanaxisPieceEffector());
}

AdanaxisPieceEffector::~AdanaxisPieceEffector()
{
    RubyPieceDestructor();    
}

void
AdanaxisPieceEffector::Move(MushGameLogic& ioLogic, const tVal inFrameslice)
{
    PostWRef().InPlaceVelocityAdd();
    
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
AdanaxisPieceEffector::Render(MushGLJobRender& outRender,
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
AdanaxisPieceEffector::MessageConsume(MushGameLogic& ioLogic, const MushGameMessage& inMessage)
{
    // Pass to base class
    MushGamePiece::MessageConsume(ioLogic, inMessage);
}

void
AdanaxisPieceEffector::Load(Mushware::tRubyValue inSelf)
{
    MushGamePiece::Load(inSelf);
    MushRubyUtil::InstanceVarSet(inSelf, MushRubyIntern::ATm_owner(), MushRubyValue(m_owner).Value());    
    MushRubyUtil::InstanceVarSet(inSelf, MushRubyIntern::ATm_lifeMsec(), MushRubyValue(static_cast<U32>(m_lifeMsec)).Value());    
    MushRubyUtil::InstanceVarSet(inSelf, AdanaxisIntern::Sgl().ATm_rail(), MushRubyValue(m_rail).Value());    
}

void
AdanaxisPieceEffector::Save(Mushware::tRubyValue inSelf)
{
    MushGamePiece::Save(inSelf);
    m_owner = MushRubyValue(MushRubyUtil::InstanceVar(inSelf, MushRubyIntern::ATm_owner())).String();
    m_lifeMsec = MushRubyValue(MushRubyUtil::InstanceVar(inSelf, MushRubyIntern::ATm_lifeMsec())).U32();
    m_rail = MushRubyValue(MushRubyUtil::InstanceVar(inSelf, AdanaxisIntern::Sgl().ATm_rail())).Bool();
}

Mushware::tRubyValue
AdanaxisPieceEffector::RubyCreate(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0)
{
    AdanaxisSaveData::tEffectorList& dataRef = AdanaxisRuby::SaveData().EffectorListWRef();
    
    /* This object contains a reference (MushcoreMaptorRef) to an object
    * in SaveData().EffectorList(), which is a MushcoreMaptor<AdanaxisPieceEffector>.
    * The next line points the MushcoreMaptorRef at that MushcoreMaptor
    */
    AdanaxisSaveData::tEffectorList::key_type key = dataRef.NextKey();
    
    ostringstream idStream;
    idStream << key;
    
    AdanaxisPieceEffector& objRef = *new AdanaxisPieceEffector(idStream.str(), MushRubyValue(inArg0));
    dataRef.Give(&objRef, key);
    
    return objRef.RubyObj().Value();
}

Mushware::tRubyValue
AdanaxisPieceEffector::Klass(void)
{
    if (m_rubyKlass == kRubyQnil)
    {
        RubyInstall();
    }
    return m_rubyKlass;
}    

void
AdanaxisPieceEffector::RubyInstall(void)
{
    if (m_rubyKlass == kRubyQnil)
    {
	    m_rubyKlass = MushRubyUtil::SubclassDefine("AdanaxisPieceEffector", AdanaxisPiece::Klass());
    }
	MushRubyUtil::SingletonMethodDefineOneParam(Klass(), "cCreate", RubyCreate);
}

namespace
{
	void Install(void)
	{
		MushRubyInstall::Sgl().Add(AdanaxisPieceEffector::RubyInstall);
	}
	MushcoreInstaller install(Install);
}
//%outOfLineFunctions {

const char *AdanaxisPieceEffector::AutoName(void) const
{
    return "AdanaxisPieceEffector";
}

MushcoreVirtualObject *AdanaxisPieceEffector::AutoClone(void) const
{
    return new AdanaxisPieceEffector(*this);
}

MushcoreVirtualObject *AdanaxisPieceEffector::AutoCreate(void) const
{
    return new AdanaxisPieceEffector;
}

MushcoreVirtualObject *AdanaxisPieceEffector::AutoVirtualFactory(void)
{
    return new AdanaxisPieceEffector;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("AdanaxisPieceEffector", AdanaxisPieceEffector::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
AdanaxisPieceEffector::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushGamePiece::AutoPrint(ioOut);
    ioOut << "owner=" << m_owner << ", ";
    ioOut << "lifeMsec=" << m_lifeMsec << ", ";
    ioOut << "launchMsec=" << m_launchMsec << ", ";
    ioOut << "rail=" << m_rail;
    ioOut << "]";
}
bool
AdanaxisPieceEffector::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
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
    else if (inTagStr == "rail")
    {
        ioIn >> m_rail;
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
AdanaxisPieceEffector::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushGamePiece::AutoXMLPrint(ioOut);
    ioOut.TagSet("owner");
    ioOut << m_owner;
    ioOut.TagSet("lifeMsec");
    ioOut << m_lifeMsec;
    ioOut.TagSet("launchMsec");
    ioOut << m_launchMsec;
    ioOut.TagSet("rail");
    ioOut << m_rail;
}
//%outOfLineFunctions } yRdBrnbOEOLWmFHOeR7tjA
