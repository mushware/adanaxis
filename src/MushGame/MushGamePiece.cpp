//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGamePiece.cpp
 *
 * Author: Andy Southgate 2002-2006
 *
 * This file contains original work by Andy Southgate.  The author and his
 * employer (Mushware Limited) irrevocably waive all of their copyright rights
 * vested in this particular version of this file to the furthest extent
 * permitted.  The author and Mushware Limited also irrevocably waive any and
 * all of their intellectual property rights arising from said file and its
 * creation that would otherwise restrict the rights of any party to use and/or
 * distribute the use of, the techniques and methods used herein.  A written
 * waiver can be obtained via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } rVCNunlW+wZoonHnGB5a7Q
/*
 * $Id: MushGamePiece.cpp,v 1.8 2006/08/17 08:57:12 southa Exp $
 * $Log: MushGamePiece.cpp,v $
 * Revision 1.8  2006/08/17 08:57:12  southa
 * Event handling
 *
 * Revision 1.7  2006/06/30 15:05:35  southa
 * Texture and buffer purge
 *
 * Revision 1.6  2006/06/01 15:39:25  southa
 * DrawArray verification and fixes
 *
 * Revision 1.5  2005/07/06 19:08:27  southa
 * Adanaxis control work
 *
 * Revision 1.4  2005/07/02 00:42:38  southa
 * Conditioning tweaks
 *
 * Revision 1.3  2005/07/01 16:42:54  southa
 * Render work
 *
 * Revision 1.2  2005/06/29 11:11:15  southa
 * Camera and rendering work
 *
 * Revision 1.1  2005/06/24 10:30:12  southa
 * MushGame camera work
 *
 */

#include "MushGamePiece.h"

#include "MushGameMessage.h"

MUSHCORE_DATA_INSTANCE(MushGamePiece);

using namespace Mushware;
using namespace std;

Mushware::tRubyValue MushGamePiece::m_rubyKlass = Mushware::kRubyQnil;

MushGamePiece::MushGamePiece(const std::string& inID) :
    m_id(inID),
    m_post(MushMeshPosticity::Identity()),
    m_expireFlag(false),
    m_rubyObj(Mushware::kRubyQnil)
{
    m_buffersRef.NameSet(MushGLBuffers::NextBufferNumAdvance());
    MushGLBuffers::tData::Sgl().GetOrCreate(m_buffersRef.Name());    
}

void
MushGamePiece::MessageConsume(MushGameLogic& ioLogic, const MushGameMessage& inMessage)
{
    throw MushcoreDataFail(std::string("Unhandled message type ")+inMessage.AutoName()+" in "+AutoName());
}

Mushware::tRubyValue
MushGamePiece::Klass(void)
{
    if (m_rubyKlass == kRubyQnil)
    {
        RubyInstall();
    }
    return m_rubyKlass;
}    

void
MushGamePiece::RubyInstall(void)
{
    if (m_rubyKlass == kRubyQnil)
    {
	    m_rubyKlass = MushRubyUtil::SubclassDefine("MushPiece", MushRubyObject::Klass());
    }
}

namespace
{
	void Install(void)
	{
		MushRubyInstall::Sgl().Add(MushGamePiece::RubyInstall);
	}
	MushcoreInstaller install(Install);
}

//%outOfLineFunctions {

const char *MushGamePiece::AutoName(void) const
{
    return "MushGamePiece";
}

MushcoreVirtualObject *MushGamePiece::AutoClone(void) const
{
    return new MushGamePiece(*this);
}

MushcoreVirtualObject *MushGamePiece::AutoCreate(void) const
{
    return new MushGamePiece;
}

MushcoreVirtualObject *MushGamePiece::AutoVirtualFactory(void)
{
    return new MushGamePiece;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGamePiece", MushGamePiece::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGamePiece::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "id=" << m_id << ", ";
    ioOut << "post=" << m_post << ", ";
    ioOut << "mesh=" << m_mesh << ", ";
    ioOut << "expireFlag=" << m_expireFlag << ", ";
    ioOut << "buffersRef=" << m_buffersRef << ", ";
    ioOut << "texCoordBuffersRef=" << m_texCoordBuffersRef << ", ";
    ioOut << "rubyObj=" << m_rubyObj;
    ioOut << "]";
}
bool
MushGamePiece::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "id")
    {
        ioIn >> m_id;
    }
    else if (inTagStr == "post")
    {
        ioIn >> m_post;
    }
    else if (inTagStr == "mesh")
    {
        ioIn >> m_mesh;
    }
    else if (inTagStr == "expireFlag")
    {
        ioIn >> m_expireFlag;
    }
    else if (inTagStr == "buffersRef")
    {
        ioIn >> m_buffersRef;
    }
    else if (inTagStr == "texCoordBuffersRef")
    {
        ioIn >> m_texCoordBuffersRef;
    }
    else if (inTagStr == "rubyObj")
    {
        ioIn >> m_rubyObj;
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushGamePiece::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("id");
    ioOut << m_id;
    ioOut.TagSet("post");
    ioOut << m_post;
    ioOut.TagSet("mesh");
    ioOut << m_mesh;
    ioOut.TagSet("expireFlag");
    ioOut << m_expireFlag;
    ioOut.TagSet("buffersRef");
    ioOut << m_buffersRef;
    ioOut.TagSet("texCoordBuffersRef");
    ioOut << m_texCoordBuffersRef;
    ioOut.TagSet("rubyObj");
    ioOut << m_rubyObj;
}
//%outOfLineFunctions } IamEJXzQ9bxpzTb/wn6ONA
