//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisPieceDeco.cpp
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
//%Header } 2OzvBSSDnfZa1M+lgXB8MQ
/*
 * $Id: AdanaxisPieceDeco.cpp,v 1.38 2007/04/18 09:22:01 southa Exp $
 * $Log: AdanaxisPieceDeco.cpp,v $
 * Revision 1.38  2007/04/18 09:22:01  southa
 * Header and level fixes
 *
 * Revision 1.37  2007/04/16 08:41:08  southa
 * Level and header mods
 *
 * Revision 1.36  2007/03/21 18:05:58  southa
 * Tied sound fixes
 *
 * Revision 1.35  2007/03/21 11:56:06  southa
 * Rail effects and damage icons
 *
 * Revision 1.34  2007/03/20 20:36:55  southa
 * Solid renderer fixes
 *
 * Revision 1.33  2006/10/30 17:03:51  southa
 * Remnants creation
 *
 * Revision 1.32  2006/10/16 15:25:57  southa
 * Explosion lifetimes
 *
 * Revision 1.31  2006/10/16 14:36:50  southa
 * Deco handling
 *
 * Revision 1.30  2006/10/15 17:12:54  southa
 * Scripted explosions
 *
 * Revision 1.29  2006/10/14 16:59:44  southa
 * Ruby Deco objects
 *
 * Revision 1.28  2006/10/06 14:48:18  southa
 * Material animation
 *
 * Revision 1.27  2006/10/06 11:54:57  southa
 * Scaled rendering
 *
 * Revision 1.26  2006/10/05 15:39:17  southa
 * Explosion handling
 *
 * Revision 1.25  2006/09/30 13:46:33  southa
 * Seek and patrol
 *
 * Revision 1.24  2006/09/09 11:16:39  southa
 * One-time vertex buffer generation
 *
 * Revision 1.23  2006/08/01 17:21:25  southa
 * River demo
 *
 * Revision 1.22  2006/08/01 13:41:15  southa
 * Pre-release updates
 *
 * Revision 1.21  2006/07/24 18:46:46  southa
 * Depth sorting
 *
 * Revision 1.20  2006/07/19 14:34:50  southa
 * Flare effects
 *
 * Revision 1.19  2006/07/19 10:22:14  southa
 * World objects
 *
 * Revision 1.18  2006/07/17 14:43:39  southa
 * Billboarded deco objects
 *
 * Revision 1.17  2006/06/30 15:05:31  southa
 * Texture and buffer purge
 *
 * Revision 1.16  2006/06/27 11:58:08  southa
 * Warning fixes
 *
 * Revision 1.15  2006/06/21 16:52:28  southa
 * Deco objects
 *
 * Revision 1.14  2006/06/01 15:38:47  southa
 * DrawArray verification and fixes
 *
 * Revision 1.13  2005/08/02 11:11:47  southa
 * Adanaxis control demo work
 *
 * Revision 1.12  2005/08/01 20:24:15  southa
 * Backdrop and build fixes
 *
 * Revision 1.11  2005/07/19 10:08:06  southa
 * Adanaxis work
 *
 * Revision 1.10  2005/07/18 13:13:35  southa
 * Extrude to point and projectile mesh
 *
 * Revision 1.9  2005/07/06 19:08:26  southa
 * Adanaxis control work
 *
 * Revision 1.8  2005/07/05 16:35:53  southa
 * Adanaxis work
 *
 * Revision 1.7  2005/07/05 13:52:22  southa
 * Adanaxis work
 *
 * Revision 1.6  2005/07/04 15:59:00  southa
 * Adanaxis work
 *
 * Revision 1.5  2005/07/04 11:10:43  southa
 * Rendering pipeline
 *
 * Revision 1.4  2005/07/02 00:42:36  southa
 * Conditioning tweaks
 *
 * Revision 1.3  2005/07/01 10:36:46  southa
 * MushRender work
 *
 * Revision 1.2  2005/06/30 16:29:24  southa
 * Adanaxis work
 *
 * Revision 1.1  2005/06/30 14:26:35  southa
 * Adanaxis work
 *
 */

#include "AdanaxisPieceDeco.h"

#include "AdanaxisIntern.h"
#include "AdanaxisRuby.h"
#include "AdanaxisVolatileData.h"

Mushware::tRubyValue AdanaxisPieceDeco::m_rubyKlass = Mushware::kRubyQnil;

using namespace Mushware;
using namespace std;

AdanaxisPieceDeco::AdanaxisPieceDeco(const std::string& inID, const MushRubyValue& inParams) :
    MushGamePiece(inID),
    m_launchMsec(0)
{
    RubyPieceConstructor(inID, inParams, AdanaxisIntern::Sgl().AdanaxisPieceDeco());
}

AdanaxisPieceDeco::~AdanaxisPieceDeco()
{
    RubyPieceDestructor();
}

void
AdanaxisPieceDeco::Move(MushGameLogic& ioLogic, const tVal inFrameSlice)
{
    PostWRef().InPlaceVelocityAdd();
    
    if (m_launchMsec == 0)
    {
        m_launchMsec = ioLogic.FrameMsec();
    }
    if (ioLogic.FrameMsec() > m_launchMsec + m_lifeMsec)
    {
        ExpireFlagSet(true);
    }
}

bool
AdanaxisPieceDeco::Render(MushGLJobRender& outRender,
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

    tVal alpha =  1.0 - (0.0 + ioLogic.FrameMsec() - m_launchMsec) / m_lifeMsec;
    MushcoreUtil::Constrain<tVal>(alpha, 0, 1);

    renderSpec.MaterialAnimatorSet(1.0 - alpha);
    
    if (AlphaStutter() > 0.0)
    {
        alpha = MushcoreUtil::RandomVal(alpha * (1-AlphaStutter()), alpha);
    }
    
    inRender.ColourZMiddleSet(inRender.ColourZMiddle().ElementwiseProduct(t4Val(1,1,1,alpha)));

    return inRender.RenderJobCreate(outRender, renderSpec, Mesh());
}

void
AdanaxisPieceDeco::Load(Mushware::tRubyValue inSelf)
{
    MushGamePiece::Load(inSelf);
    MushRubyUtil::InstanceVarSet(inSelf, MushRubyIntern::ATm_lifeMsec(), MushRubyValue(static_cast<U32>(m_lifeMsec)).Value());    
}

void
AdanaxisPieceDeco::Save(Mushware::tRubyValue inSelf)
{
    MushGamePiece::Save(inSelf);
    m_lifeMsec = MushRubyValue(MushRubyUtil::InstanceVar(inSelf, MushRubyIntern::ATm_lifeMsec())).U32();
}

Mushware::tRubyValue
AdanaxisPieceDeco::RubyCreate(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0)
{
    AdanaxisVolatileData::tDecoList& dataRef = AdanaxisRuby::VolatileData().DecoListWRef();
    
    /* This object contains a reference (MushcoreMaptorRef) to an object
     * in SaveData().DecoList(), which is a MushcoreMaptor<AdanaxisPieceDeco>.
     * The next line points the MushcoreMaptorRef at that MushcoreMaptor
     */
    AdanaxisVolatileData::tDecoList::key_type key = dataRef.NextKey();
    
    ostringstream idStream;
    idStream << key;
    
    AdanaxisPieceDeco& objRef = *new AdanaxisPieceDeco(idStream.str(), MushRubyValue(inArg0));
    dataRef.Give(&objRef, key);
    
    return objRef.RubyObj().Value();
}

Mushware::tRubyValue
AdanaxisPieceDeco::Klass(void)
{
    if (m_rubyKlass == kRubyQnil)
    {
        RubyInstall();
    }
    return m_rubyKlass;
}    

void
AdanaxisPieceDeco::RubyInstall(void)
{
    if (m_rubyKlass == kRubyQnil)
    {
	    m_rubyKlass = MushRubyUtil::SubclassDefine("AdanaxisPieceDeco", AdanaxisPiece::Klass());
    }
	MushRubyUtil::SingletonMethodDefineOneParam(Klass(), "cCreate", RubyCreate);
}

namespace
{
	void Install(void)
	{
		MushRubyInstall::Sgl().Add(AdanaxisPieceDeco::RubyInstall);
	}
	MushcoreInstaller install(Install);
}

//%outOfLineFunctions {

const char *AdanaxisPieceDeco::AutoName(void) const
{
    return "AdanaxisPieceDeco";
}

MushcoreVirtualObject *AdanaxisPieceDeco::AutoClone(void) const
{
    return new AdanaxisPieceDeco(*this);
}

MushcoreVirtualObject *AdanaxisPieceDeco::AutoCreate(void) const
{
    return new AdanaxisPieceDeco;
}

MushcoreVirtualObject *AdanaxisPieceDeco::AutoVirtualFactory(void)
{
    return new AdanaxisPieceDeco;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("AdanaxisPieceDeco", AdanaxisPieceDeco::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
AdanaxisPieceDeco::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushGamePiece::AutoPrint(ioOut);
    ioOut << "lifeMsec=" << m_lifeMsec << ", ";
    ioOut << "launchMsec=" << m_launchMsec;
    ioOut << "]";
}
bool
AdanaxisPieceDeco::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
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
AdanaxisPieceDeco::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushGamePiece::AutoXMLPrint(ioOut);
    ioOut.TagSet("lifeMsec");
    ioOut << m_lifeMsec;
    ioOut.TagSet("launchMsec");
    ioOut << m_launchMsec;
}
//%outOfLineFunctions } ib/EjpdMjjfDJRWLbWpTlQ
