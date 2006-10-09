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
 * $Id: MushGamePiece.cpp,v 1.17 2006/10/08 11:31:32 southa Exp $
 * $Log: MushGamePiece.cpp,v $
 * Revision 1.17  2006/10/08 11:31:32  southa
 * Hit points
 *
 * Revision 1.16  2006/10/06 11:54:58  southa
 * Scaled rendering
 *
 * Revision 1.15  2006/10/04 13:35:24  southa
 * Selective targetting
 *
 * Revision 1.14  2006/10/03 14:06:51  southa
 * Khazi and projectile creation
 *
 * Revision 1.13  2006/10/02 20:28:11  southa
 * Object lookup and target selection
 *
 * Revision 1.12  2006/09/09 11:16:41  southa
 * One-time vertex buffer generation
 *
 * Revision 1.11  2006/08/24 13:04:38  southa
 * Event handling
 *
 * Revision 1.10  2006/08/20 14:19:21  southa
 * Seek operation
 *
 * Revision 1.9  2006/08/17 12:18:11  southa
 * Event handling
 *
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

#include "API/mushMushMeshRuby.h"

MUSHCORE_DATA_INSTANCE(MushGamePiece);

using namespace Mushware;
using namespace std;

Mushware::tRubyValue MushGamePiece::m_rubyKlass = Mushware::kRubyQnil;

MushGamePiece::MushGamePiece(const std::string& inID) :
    m_post(MushMeshPosticity::Identity()),
    m_meshScale(Mushware::t4Val::MultiplicativeIdentity()),
    m_expireFlag(false),
    m_hitPoints(0),
    m_initialHitPoints(0),
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

Mushware::tVal
MushGamePiece::HitPointRatio(void) const
{
    if (m_initialHitPoints <= 0)
    {
        return 1.0;
    }
    else
    {
        return m_hitPoints / m_initialHitPoints;
    }
}

void
MushGamePiece::Load(Mushware::tRubyValue inSelf)
{
    MushRubyUtil::InstanceVarSet(inSelf, MushRubyIntern::ATm_id(), MushRubyValue(m_id).Value());
    {
        tRubyValue value = MushRubyUtil::InstanceVar(inSelf, MushRubyIntern::ATm_post());
        if (value == kRubyQnil)
        {
            throw MushcoreDataFail("No attribute @m_post in MushPiece");
        }
        MushMeshRubyPost::WRef(value) = Post();
    }
    
    MushRubyUtil::InstanceVarSet(inSelf, MushRubyIntern::ATm_meshName(), MushRubyValue(m_meshName).Value());    
    MushRubyUtil::InstanceVarSet(inSelf, MushRubyIntern::ATm_expireFlag(), MushRubyValue(m_expireFlag).Value());
    MushRubyUtil::InstanceVarSet(inSelf, MushRubyIntern::ATm_hitPoints(), MushRubyValue(m_hitPoints).Value());
}

void
MushGamePiece::Save(Mushware::tRubyValue inSelf)
{
    m_id = MushRubyValue(MushRubyUtil::InstanceVar(inSelf, MushRubyIntern::ATm_id())).String();
    {
        tRubyValue value = MushRubyUtil::InstanceVar(inSelf, MushRubyIntern::ATm_post());
        if (value == kRubyQnil)
        {
            throw MushcoreDataFail("No attribute @m_post in MushPiece");
        }
        PostSet(MushMeshRubyPost::Ref(value));
    }
    {
        std::string newMeshName = MushRubyValue(MushRubyUtil::InstanceVar(inSelf, MushRubyIntern::ATm_meshName())).String();
        if (m_meshName != newMeshName)
        {
            // Expensive mesh duplication
            MeshSet(*MushcoreData<MushMesh4Mesh>::Sgl().Get(newMeshName));
            SharedBuffersNameSet(newMeshName); 
            m_meshName = newMeshName;
        }
    }
    m_expireFlag = MushRubyValue(MushRubyUtil::InstanceVar(inSelf, MushRubyIntern::ATm_expireFlag())).Bool();
    m_hitPoints = MushRubyValue(MushRubyUtil::InstanceVar(inSelf, MushRubyIntern::ATm_hitPoints())).Val();
}

void
MushGamePiece::RubyPieceConstructor(const std::string& inID, const MushRubyValue& inParams,
                                    const MushRubyValue& inKlass)
{
    /*** This function is called from constructors */

    if (!inParams.IsNil())
    {
        /* Add the element id_suffix => inId so that the ruby object can calculate its ID.
         * This is saved into the C++ m_id by mSave
         */
        MushRubyUtil::HashValueSet(inParams.Value(), MushRubyUtil::SymbolToValue(MushRubyIntern::id_suffix()),
                                   MushRubyValue(inID).Value());
    }
    
    // Create the registered object
    RubyObjSet(MushRubyExec::Sgl().Call(inKlass,
                                        MushRubyIntern::cRegisteredCreate(),
                                        inParams));
    /* Add this C++ object to the ruby object as a wrapped DataStruct, and set
     * embedded data pointer
     */
    MushRubyUtil::DataObjectWrapNew(inKlass, RubyObj(), this);
    
    /* Save the ruby variables (extracted from inParams by the ruby initialize method)
     * into this C++ object
     */
    MushRubyExec::Sgl().Call(RubyObj(), MushRubyIntern::mSave());
    
    /* Store the initial hit points */
    m_initialHitPoints = m_hitPoints;
}

void
MushGamePiece::RubyPieceDestructor(void) // nothrow
{
    /*** This function is called from destructors */
    
    try
    {
        RubyObj().Call(MushRubyIntern::mRegisteredDestroy());
    }
    catch (std::exception& e)
    {
        MushcoreLog::Sgl().ErrorLog() << "Destructor exception: " << e.what() << std::endl;
        // Don't allow exception to propagate
    }
}

Mushware::tRubyValue
MushGamePiece::RubyLoad(Mushware::tRubyValue inSelf)
{
    try
    {
        MushGamePiece *self = reinterpret_cast<MushGamePiece *>(MushRubyUtil::DataObjectRetrieve(inSelf));
        MUSHCOREASSERT(dynamic_cast<MushGamePiece *>(self) != NULL);

        self->Load(inSelf);
    }
    catch (std::exception& e)
    {
            MushRubyUtil::Raise(e.what());    
    }
	return inSelf;
}

Mushware::tRubyValue
MushGamePiece::RubySave(Mushware::tRubyValue inSelf)
{
    try
    {
        MushGamePiece *self = reinterpret_cast<MushGamePiece *>(MushRubyUtil::DataObjectRetrieve(inSelf));
        MUSHCOREASSERT(dynamic_cast<MushGamePiece *>(self) != NULL);
        
        self->Save(inSelf);
    }
    catch (std::exception& e)
    {
        MushRubyUtil::Raise(e.what());    
    }
    return inSelf;
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

Mushware::tRubyValue
MushGamePiece::RubyPost(Mushware::tRubyValue inSelf)
{
    Mushware::tRubyValue retVal = kRubyQnil;
    
    try
    {
        MushGamePiece *self = reinterpret_cast<MushGamePiece *>(MushRubyUtil::DataObjectRetrieve(inSelf));
        MUSHCOREASSERT(dynamic_cast<MushGamePiece *>(self) != NULL);
        
        retVal = MushMeshRubyPost::NewInstance();
        
        MushMeshRubyPost::WRef(retVal) = self->Post();
        MushRubyUtil::Freeze(retVal);
    }
    catch (std::exception& e)
    {
        MushRubyUtil::Raise(e.what());    
    }
    return retVal;
}

void
MushGamePiece::RubyInstall(void)
{
    if (m_rubyKlass == kRubyQnil)
    {
	    m_rubyKlass = MushRubyUtil::SubclassDefine("MushPiece", MushRubyObject::Klass());
        MushRubyUtil::MethodDefineNoParams(Klass(), "mLoad", RubyLoad);
        MushRubyUtil::MethodDefineNoParams(Klass(), "mSave", RubySave);
        MushRubyUtil::MethodDefineNoParams(Klass(), "post", RubyPost);
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
    ioOut << "meshName=" << m_meshName << ", ";
    ioOut << "post=" << m_post << ", ";
    ioOut << "mesh=" << m_mesh << ", ";
    ioOut << "meshScale=" << m_meshScale << ", ";
    ioOut << "expireFlag=" << m_expireFlag << ", ";
    ioOut << "hitPoints=" << m_hitPoints << ", ";
    ioOut << "initialHitPoints=" << m_initialHitPoints << ", ";
    ioOut << "buffersRef=" << m_buffersRef << ", ";
    ioOut << "sharedBuffersRef=" << m_sharedBuffersRef << ", ";
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
    else if (inTagStr == "meshName")
    {
        ioIn >> m_meshName;
    }
    else if (inTagStr == "post")
    {
        ioIn >> m_post;
    }
    else if (inTagStr == "mesh")
    {
        ioIn >> m_mesh;
    }
    else if (inTagStr == "meshScale")
    {
        ioIn >> m_meshScale;
    }
    else if (inTagStr == "expireFlag")
    {
        ioIn >> m_expireFlag;
    }
    else if (inTagStr == "hitPoints")
    {
        ioIn >> m_hitPoints;
    }
    else if (inTagStr == "initialHitPoints")
    {
        ioIn >> m_initialHitPoints;
    }
    else if (inTagStr == "buffersRef")
    {
        ioIn >> m_buffersRef;
    }
    else if (inTagStr == "sharedBuffersRef")
    {
        ioIn >> m_sharedBuffersRef;
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
    ioOut.TagSet("meshName");
    ioOut << m_meshName;
    ioOut.TagSet("post");
    ioOut << m_post;
    ioOut.TagSet("mesh");
    ioOut << m_mesh;
    ioOut.TagSet("meshScale");
    ioOut << m_meshScale;
    ioOut.TagSet("expireFlag");
    ioOut << m_expireFlag;
    ioOut.TagSet("hitPoints");
    ioOut << m_hitPoints;
    ioOut.TagSet("initialHitPoints");
    ioOut << m_initialHitPoints;
    ioOut.TagSet("buffersRef");
    ioOut << m_buffersRef;
    ioOut.TagSet("sharedBuffersRef");
    ioOut << m_sharedBuffersRef;
    ioOut.TagSet("rubyObj");
    ioOut << m_rubyObj;
}
//%outOfLineFunctions } ykBrJQOa5HZ3/BuagvNhQA
