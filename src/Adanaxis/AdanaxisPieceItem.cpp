//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisPieceItem.cpp
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
//%Header } 47JNGPRKChWEEGNXcF88ug
/*
 * $Id: AdanaxisPieceItem.cpp,v 1.4 2007/05/29 13:25:58 southa Exp $
 * $Log: AdanaxisPieceItem.cpp,v $
 * Revision 1.4  2007/05/29 13:25:58  southa
 * Level 20
 *
 * Revision 1.3  2007/04/18 09:22:02  southa
 * Header and level fixes
 *
 * Revision 1.2  2006/10/30 17:03:51  southa
 * Remnants creation
 *
 * Revision 1.1  2006/10/19 15:41:35  southa
 * Item handling
 *
 */

#include "AdanaxisPieceItem.h"

#include "AdanaxisRuby.h"
#include "AdanaxisSaveData.h"
#include "AdanaxisIntern.h"

Mushware::tRubyValue AdanaxisPieceItem::m_rubyKlass = Mushware::kRubyQnil;

using namespace Mushware;
using namespace std;

AdanaxisPieceItem::AdanaxisPieceItem(const std::string& inID, const MushRubyValue& inParams) :
    MushGamePiece(inID),
    m_creationMsec(0)
{
    RubyPieceConstructor(inID, inParams, AdanaxisIntern::Sgl().AdanaxisPieceItem());
}

AdanaxisPieceItem::~AdanaxisPieceItem()
{
    RubyPieceDestructor();
}

void
AdanaxisPieceItem::Move(MushGameLogic& ioLogic, const tVal inFrameSlice)
{
    MushGamePiece::Move(ioLogic, inFrameSlice);

    PostWRef().InPlaceVelocityAdd();
    
    if (m_creationMsec == 0)
    {
        m_creationMsec = ioLogic.FrameMsec();
    }
    if (ioLogic.FrameMsec() > m_creationMsec + m_lifeMsec)
    {
        ExpireFlagSet(true);
        RubyEventHandle(MushGameEvents::Sgl().EventExpiryMake());
    }
}

bool
AdanaxisPieceItem::Render(MushGLJobRender& outRender,
                          MushGameLogic& ioLogic, MushRenderMesh& inRender, const MushGameCamera& inCamera)
{
    MushRenderSpec renderSpec;
    renderSpec.BuffersRefSet(BuffersRef());
    renderSpec.SharedBuffersRefSet(SharedBuffersRef());
    renderSpec.ScaleSet(RenderScale());
    
    MushMeshOps::PosticityToMattress(renderSpec.ModelWRef(), Post());
    MushMeshOps::PosticityToMattress(renderSpec.ViewWRef(), inCamera.Post());
    renderSpec.ViewWRef().InPlaceInvert();
    
    renderSpec.ProjectionSet(inCamera.Projection());
    
    tVal alpha = 0.60+0.40*sin(ioLogic.FrameMsec() / 150.0);
    
    MushcoreUtil::Constrain<tVal>(alpha, 0, 1);
    
    inRender.ColourZMiddleSet(inRender.ColourZMiddle().ElementwiseProduct(t4Val(1,1,1,alpha)));
    
    renderSpec.MaterialAnimatorSet(1.0 - alpha);
    
    return inRender.RenderJobCreate(outRender, renderSpec, Mesh());
}

void
AdanaxisPieceItem::Load(Mushware::tRubyValue inSelf)
{
    MushGamePiece::Load(inSelf);
    MushRubyUtil::InstanceVarSet(inSelf, MushRubyIntern::ATm_owner(), MushRubyValue(m_owner).Value());    
    MushRubyUtil::InstanceVarSet(inSelf, MushRubyIntern::ATm_lifeMsec(), MushRubyValue(static_cast<U32>(m_lifeMsec)).Value());    
}

void
AdanaxisPieceItem::Save(Mushware::tRubyValue inSelf)
{
    MushGamePiece::Save(inSelf);
    m_owner = MushRubyValue(MushRubyUtil::InstanceVar(inSelf, MushRubyIntern::ATm_owner())).String();
    m_lifeMsec = MushRubyValue(MushRubyUtil::InstanceVar(inSelf, MushRubyIntern::ATm_lifeMsec())).U32();
}

Mushware::tRubyValue
AdanaxisPieceItem::RubyCreate(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0)
{
    AdanaxisSaveData::tItemList& dataRef = AdanaxisRuby::SaveData().ItemListWRef();
    
    /* This object contains a reference (MushcoreMaptorRef) to an object
    * in SaveData().ItemList(), which is a MushcoreMaptor<AdanaxisPieceItem>.
    * The next line points the MushcoreMaptorRef at that MushcoreMaptor
    */
    AdanaxisSaveData::tItemList::key_type key = dataRef.NextKey();
    
    ostringstream idStream;
    idStream << key;
    
    AdanaxisPieceItem& objRef = *new AdanaxisPieceItem(idStream.str(), MushRubyValue(inArg0));
    dataRef.Give(&objRef, key);
    
    return objRef.RubyObj().Value();
}

Mushware::tRubyValue
AdanaxisPieceItem::Klass(void)
{
    if (m_rubyKlass == kRubyQnil)
    {
        RubyInstall();
    }
    return m_rubyKlass;
}    

void
AdanaxisPieceItem::RubyInstall(void)
{
    if (m_rubyKlass == kRubyQnil)
    {
	    m_rubyKlass = MushRubyUtil::SubclassDefine("AdanaxisPieceItem", AdanaxisPiece::Klass());
    }
	MushRubyUtil::SingletonMethodDefineOneParam(Klass(), "cCreate", RubyCreate);
}

namespace
{
	void Install(void)
	{
		MushRubyInstall::Sgl().Add(AdanaxisPieceItem::RubyInstall);
	}
	MushcoreInstaller install(Install);
}

//%outOfLineFunctions {

const char *AdanaxisPieceItem::AutoName(void) const
{
    return "AdanaxisPieceItem";
}

MushcoreVirtualObject *AdanaxisPieceItem::AutoClone(void) const
{
    return new AdanaxisPieceItem(*this);
}

MushcoreVirtualObject *AdanaxisPieceItem::AutoCreate(void) const
{
    return new AdanaxisPieceItem;
}

MushcoreVirtualObject *AdanaxisPieceItem::AutoVirtualFactory(void)
{
    return new AdanaxisPieceItem;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("AdanaxisPieceItem", AdanaxisPieceItem::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
AdanaxisPieceItem::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushGamePiece::AutoPrint(ioOut);
    ioOut << "owner=" << m_owner << ", ";
    ioOut << "lifeMsec=" << m_lifeMsec << ", ";
    ioOut << "creationMsec=" << m_creationMsec;
    ioOut << "]";
}
bool
AdanaxisPieceItem::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
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
    else if (inTagStr == "creationMsec")
    {
        ioIn >> m_creationMsec;
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
AdanaxisPieceItem::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushGamePiece::AutoXMLPrint(ioOut);
    ioOut.TagSet("owner");
    ioOut << m_owner;
    ioOut.TagSet("lifeMsec");
    ioOut << m_lifeMsec;
    ioOut.TagSet("creationMsec");
    ioOut << m_creationMsec;
}
//%outOfLineFunctions } YZeoSe0OKVGJGl8rrDlMSA
