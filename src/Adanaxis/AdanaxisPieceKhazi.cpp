//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisPieceKhazi.cpp
 *
 * Copyright: Andy Southgate 2002-2007, 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/
//%Header } PGLR46JWijoLV/gXTw11uQ
/*
 * $Id: AdanaxisPieceKhazi.cpp,v 1.36 2007/06/06 15:11:21 southa Exp $
 * $Log: AdanaxisPieceKhazi.cpp,v $
 * Revision 1.36  2007/06/06 15:11:21  southa
 * Level 23
 *
 * Revision 1.35  2007/04/18 09:22:02  southa
 * Header and level fixes
 *
 * Revision 1.34  2007/04/16 08:41:08  southa
 * Level and header mods
 *
 * Revision 1.33  2007/03/13 18:21:37  southa
 * Scanner jamming
 *
 * Revision 1.32  2007/03/13 12:22:50  southa
 * Scanner symbols
 *
 * Revision 1.31  2006/11/12 20:09:54  southa
 * Missile guidance
 *
 * Revision 1.30  2006/10/30 17:03:51  southa
 * Remnants creation
 *
 * Revision 1.29  2006/10/17 15:28:01  southa
 * Player collisions
 *
 * Revision 1.28  2006/10/17 11:05:54  southa
 * Expiry events
 *
 * Revision 1.27  2006/10/12 22:04:47  southa
 * Collision events
 *
 * Revision 1.26  2006/10/09 16:00:16  southa
 * Intern generation
 *
 * Revision 1.25  2006/10/05 15:39:17  southa
 * Explosion handling
 *
 * Revision 1.24  2006/10/04 13:35:22  southa
 * Selective targetting
 *
 * Revision 1.23  2006/10/03 14:06:51  southa
 * Khazi and projectile creation
 *
 * Revision 1.22  2006/10/02 20:28:10  southa
 * Object lookup and target selection
 *
 * Revision 1.21  2006/09/09 15:59:27  southa
 * Shader colour calculations
 *
 * Revision 1.20  2006/09/09 11:16:39  southa
 * One-time vertex buffer generation
 *
 * Revision 1.19  2006/08/24 16:30:55  southa
 * Event handling
 *
 * Revision 1.18  2006/08/24 13:04:38  southa
 * Event handling
 *
 * Revision 1.17  2006/08/20 14:19:20  southa
 * Seek operation
 *
 * Revision 1.16  2006/08/19 09:12:09  southa
 * Event handling
 *
 * Revision 1.15  2006/08/17 12:18:10  southa
 * Event handling
 *
 * Revision 1.14  2006/08/17 08:57:11  southa
 * Event handling
 *
 * Revision 1.13  2006/08/01 17:21:25  southa
 * River demo
 *
 * Revision 1.12  2006/07/24 18:46:46  southa
 * Depth sorting
 *
 * Revision 1.11  2006/07/19 14:34:51  southa
 * Flare effects
 *
 * Revision 1.10  2006/07/19 10:22:14  southa
 * World objects
 *
 * Revision 1.9  2006/06/30 15:05:31  southa
 * Texture and buffer purge
 *
 * Revision 1.8  2006/06/21 12:17:55  southa
 * Ruby object generation
 *
 * Revision 1.7  2006/06/01 15:38:47  southa
 * DrawArray verification and fixes
 *
 * Revision 1.6  2005/09/05 12:54:29  southa
 * Solid rendering work
 *
 * Revision 1.5  2005/09/03 17:05:36  southa
 * Material work
 *
 * Revision 1.4  2005/08/02 11:11:47  southa
 * Adanaxis control demo work
 *
 * Revision 1.3  2005/08/01 17:58:51  southa
 * Object explosion
 *
 * Revision 1.2  2005/08/01 13:09:57  southa
 * Collision messaging
 *
 * Revision 1.1  2005/07/19 10:08:06  southa
 * Adanaxis work
 *
 */

#include "AdanaxisPieceKhazi.h"

#include "AdanaxisData.h"
#include "AdanaxisIntern.h"
#include "AdanaxisPieceProjectile.h"
#include "AdanaxisRuby.h"
#include "AdanaxisUtil.h"

#include "API/mushMushMeshRuby.h"

using namespace Mushware;
using namespace std;

Mushware::tRubyValue AdanaxisPieceKhazi::m_rubyKlass = Mushware::kRubyQnil;

AdanaxisPieceKhazi::AdanaxisPieceKhazi(const std::string& inID, const MushRubyValue& inParams) :
    MushGamePiece(inID)
{
    RubyPieceConstructor(inID, inParams, AdanaxisIntern::Sgl().AdanaxisPieceKhazi());
}

AdanaxisPieceKhazi::~AdanaxisPieceKhazi()
{
    RubyPieceDestructor();
}

void
AdanaxisPieceKhazi::EventHandle(MushGameLogic& ioLogic, MushRubyValue inEvent, MushRubyValue inParams)
{
    MushcoreLog::Sgl().InfoLog() << "Khazi event " << inEvent.Call(MushRubyIntern::to_s()) << endl;
}

void
AdanaxisPieceKhazi::Move(MushGameLogic& ioLogic, const tVal inFrameslice)
{
    MushGamePiece::Move(ioLogic, inFrameslice);
        
    PostWRef().InPlaceVelocityAdd();
}

bool
AdanaxisPieceKhazi::Render(MushGLJobRender& outRender,
                           MushGameLogic& ioLogic, MushRenderMesh& inRender, const MushGameCamera& inCamera)
{
    MushRenderSpec renderSpec;
    renderSpec.BuffersRefSet(BuffersRef());
    renderSpec.SharedBuffersRefSet(SharedBuffersRef());

    MushMeshOps::PosticityToMattress(renderSpec.ModelWRef(), Post());
    MushMeshOps::PosticityToMattress(renderSpec.ViewWRef(), inCamera.Post());
    renderSpec.ViewWRef().InPlaceInvert();
    
    renderSpec.ProjectionSet(inCamera.Projection());

    if (m_isStealth)
    {
        AdanaxisVolatileData *pVolData = dynamic_cast<AdanaxisVolatileData *>(&ioLogic.VolatileData());
        if (pVolData->JammerCount() > 0)
        {
            inRender.ColourZMiddleSet(inRender.ColourZMiddle().ElementwiseProduct(t4Val(1,1,1,0.05)));
        }
    }
    
    return inRender.RenderJobCreate(outRender, renderSpec, Mesh());
}

void
AdanaxisPieceKhazi::MessageConsume(MushGameLogic& ioLogic, const MushGameMessage& inMessage)
{
    // Pass to base class
    MushGamePiece::MessageConsume(ioLogic, inMessage);
}

void
AdanaxisPieceKhazi::Load(Mushware::tRubyValue inSelf)
{
    MushGamePiece::Load(inSelf);
    MushRubyUtil::InstanceVarSet(inSelf, AdanaxisIntern::Sgl().ATm_scannerSymbol(), MushRubyValue(m_scannerSymbol).Value());    
    MushRubyUtil::InstanceVarSet(inSelf, AdanaxisIntern::Sgl().ATm_isJammer(), MushRubyValue(m_isJammer).Value());    
    MushRubyUtil::InstanceVarSet(inSelf, AdanaxisIntern::Sgl().ATm_isStealth(), MushRubyValue(m_isStealth).Value());    
}

void
AdanaxisPieceKhazi::Save(Mushware::tRubyValue inSelf)
{
    MushGamePiece::Save(inSelf);
    m_scannerSymbol = MushRubyValue(MushRubyUtil::InstanceVar(inSelf, AdanaxisIntern::Sgl().ATm_scannerSymbol())).U32();
    m_isJammer = MushRubyValue(MushRubyUtil::InstanceVar(inSelf, AdanaxisIntern::Sgl().ATm_isJammer())).Bool();
    m_isStealth = MushRubyValue(MushRubyUtil::InstanceVar(inSelf, AdanaxisIntern::Sgl().ATm_isStealth())).Bool();
}

Mushware::tRubyValue
AdanaxisPieceKhazi::RubyCreate(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0)
{
    AdanaxisSaveData::tKhaziList& dataRef = AdanaxisRuby::SaveData().KhaziListWRef();
	
	/* This object contains a reference (MushcoreMaptorRef) to an object
     * in SaveData().KhaziList(), which is a MushcoreMaptor<AdanaxisPieceProjectile>.
     * The next line points the MushcoreMaptorRef at that MushcoreMaptor
     */
    AdanaxisSaveData::tKhaziList::key_type key = dataRef.NextKey();
    
    ostringstream idStream;
    idStream << key;
    
	AdanaxisPieceKhazi& objRef = *new AdanaxisPieceKhazi(idStream.str(), MushRubyValue(inArg0));
    dataRef.Give(&objRef, key);

    return objRef.RubyObj().Value();
}

Mushware::tRubyValue
AdanaxisPieceKhazi::Klass(void)
{
    if (m_rubyKlass == kRubyQnil)
    {
        RubyInstall();
    }
    return m_rubyKlass;
}    

void
AdanaxisPieceKhazi::RubyInstall(void)
{
    if (m_rubyKlass == kRubyQnil)
    {
	    m_rubyKlass = MushRubyUtil::SubclassDefine("AdanaxisPieceKhazi", AdanaxisPiece::Klass());
    }
	MushRubyUtil::SingletonMethodDefineOneParam(Klass(), "cCreate", RubyCreate);
}

namespace
{
	void Install(void)
	{
		MushRubyInstall::Sgl().Add(AdanaxisPieceKhazi::RubyInstall);
	}
	MushcoreInstaller install(Install);
}

//%outOfLineFunctions {

const char *AdanaxisPieceKhazi::AutoName(void) const
{
    return "AdanaxisPieceKhazi";
}

MushcoreVirtualObject *AdanaxisPieceKhazi::AutoClone(void) const
{
    return new AdanaxisPieceKhazi(*this);
}

MushcoreVirtualObject *AdanaxisPieceKhazi::AutoCreate(void) const
{
    return new AdanaxisPieceKhazi;
}

MushcoreVirtualObject *AdanaxisPieceKhazi::AutoVirtualFactory(void)
{
    return new AdanaxisPieceKhazi;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("AdanaxisPieceKhazi", AdanaxisPieceKhazi::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
AdanaxisPieceKhazi::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushGamePiece::AutoPrint(ioOut);
    ioOut << "scannerSymbol=" << m_scannerSymbol << ", ";
    ioOut << "isJammer=" << m_isJammer << ", ";
    ioOut << "isStealth=" << m_isStealth;
    ioOut << "]";
}
bool
AdanaxisPieceKhazi::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "scannerSymbol")
    {
        ioIn >> m_scannerSymbol;
    }
    else if (inTagStr == "isJammer")
    {
        ioIn >> m_isJammer;
    }
    else if (inTagStr == "isStealth")
    {
        ioIn >> m_isStealth;
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
AdanaxisPieceKhazi::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushGamePiece::AutoXMLPrint(ioOut);
    ioOut.TagSet("scannerSymbol");
    ioOut << m_scannerSymbol;
    ioOut.TagSet("isJammer");
    ioOut << m_isJammer;
    ioOut.TagSet("isStealth");
    ioOut << m_isStealth;
}
//%outOfLineFunctions } JCbK10kejuEdcr3rQa9vcg
