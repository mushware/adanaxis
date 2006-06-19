//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLMaterial.cpp
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
//%Header } yyGH2nvFnzrMau3Fpl5qfQ
/*
 * $Id: MushGLMaterial.cpp,v 1.3 2006/06/01 15:39:18 southa Exp $
 * $Log: MushGLMaterial.cpp,v $
 * Revision 1.3  2006/06/01 15:39:18  southa
 * DrawArray verification and fixes
 *
 * Revision 1.2  2005/09/05 12:54:30  southa
 * Solid rendering work
 *
 * Revision 1.1  2005/09/03 17:05:36  southa
 * Material work
 *
 */

#include "MushGLMaterial.h"

#include "API/mushMushRuby.h"

using namespace Mushware;
using namespace std;

void
MushGLMaterial::TexNameSet(const std::string& inName, Mushware::U32 inIndex)
{
    if (m_texRefs.size() <= inIndex)
	{
		m_texRefs.resize(inIndex + 1);	
	}
	m_texRefs[inIndex].NameSet(inName);
}

MushGLTexture&
MushGLMaterial::TexRef(Mushware::U32 inIndex)
{
	if (inIndex >= m_texRefs.size())
	{
		std::ostringstream message;
		message << "Texture '" << Name() << "' has " << m_texRefs.size() << " textures but index " << inIndex << " requested";
		throw MushcoreRequestFail(message.str());
	}
	return m_texRefs[inIndex].WRef();
}

MushGLTexture&
MushGLMaterial::TexWRef(Mushware::U32 inIndex)
{
	if (inIndex >= m_texRefs.size())
	{
		std::ostringstream message;
		message << "Texture '" << Name() << "' has " << m_texRefs.size() << " textures but index " << inIndex << " requested";
		throw MushcoreRequestFail(message.str());
	}
	return m_texRefs[inIndex].WRef();
}

Mushware::tRubyValue
MushGLMaterial::RubyDefine(Mushware::tRubyArgC inArgC, Mushware::tRubyValue *inpArgV, Mushware::tRubyValue inSelf)
{
	try
	{
		if (inArgC != 1)
		{
			throw MushRubyFail("Wrong number of parameters to RubyDefine (must be a hash)");	
		}
		
		Mushware::tRubyHash paramHash;
		MushRubyUtil::HashConvert(paramHash, MushRubyValue(inpArgV[0]));

		std::string materialName = "";
		std::string textureName = "";
		
		tRubyHash::const_iterator endIter = paramHash.end();
		for (tRubyHash::const_iterator p = paramHash.begin(); p != endIter; ++p)
		{
			tRubyID symbol = p->first.Symbol();
			if (symbol == MushRubyIntern::name())
			{
				materialName = p->second.String();
			}
			else if (symbol == MushRubyIntern::texture_name())
			{
				textureName = p->second.String();
			}
			else
			{
				MushRubyUtil::Raise("Unknown name in parameter hash '"+p->first.String()+"'");	
			}
		}			
				
		if (materialName == "" || textureName == "")
		{
			MushRubyUtil::Raise("Both :name and :texture_name paramters must be supplied");	
			
		}
		
		MushGLMaterial *pMaterial = dynamic_cast<MushGLMaterial *>(MushcoreData<MushMesh4Material>::Sgl().Give(materialName, new MushGLMaterial));
		pMaterial->NameSet(materialName);
		pMaterial->TexNameSet(textureName);
	}
	catch (MushcoreFail& e)
	{
		MushRubyUtil::Raise(e.what());
	}

	return Mushware::kRubyQnil;
}

Mushware::tRubyValue
MushGLMaterial::Rubyto_xml(Mushware::tRubyValue inSelf)
{
	try
	{
		std::ostringstream objStream;
		MushcoreXMLOStream xmlStream(objStream);
		xmlStream << MushcoreData<MushMesh4Material>::Sgl();
		
		return MushRubyUtil::StringNew(objStream.str());
	}
	catch (MushcoreFail& e)
	{
		MushRubyUtil::Raise(e.what());
	}

	return Mushware::kRubyQnil;
}

void
MushGLMaterial::RubyInstall(void)
{
	Mushware::tRubyValue klass = MushRubyUtil::ClassDefine("MushMaterial");
	MushRubyUtil::SingletonMethodDefine(klass, "cRubyDefine", RubyDefine);
	MushRubyUtil::SingletonMethodDefineNoParams(klass, "cRubyto_xml", Rubyto_xml);
}

namespace
{
	void Install(void)
	{
		MushRubyInstall::Sgl().Add(MushGLMaterial::RubyInstall);
	}
	MUSHCORE_INSTALLER(Install);
}

//%outOfLineFunctions {

const char *MushGLMaterial::AutoName(void) const
{
    return "MushGLMaterial";
}

MushcoreVirtualObject *MushGLMaterial::AutoClone(void) const
{
    return new MushGLMaterial(*this);
}

MushcoreVirtualObject *MushGLMaterial::AutoCreate(void) const
{
    return new MushGLMaterial;
}

MushcoreVirtualObject *MushGLMaterial::AutoVirtualFactory(void)
{
    return new MushGLMaterial;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGLMaterial", MushGLMaterial::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGLMaterial::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "texRefs=" << m_texRefs;
    ioOut << "]";
}
bool
MushGLMaterial::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "texRefs")
    {
        ioIn >> m_texRefs;
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushGLMaterial::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("texRefs");
    ioOut << m_texRefs;
}
//%outOfLineFunctions } x3xh/JbLnzza669EngaO5g
