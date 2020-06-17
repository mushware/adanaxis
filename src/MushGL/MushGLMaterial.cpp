//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLMaterial.cpp
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
//%Header } LpN+7QeD6VQVNLBjKsB28A
/*
 * $Id: MushGLMaterial.cpp,v 1.7 2006/10/19 15:41:36 southa Exp $
 * $Log: MushGLMaterial.cpp,v $
 * Revision 1.7  2006/10/19 15:41:36  southa
 * Item handling
 *
 * Revision 1.6  2006/10/06 14:48:18  southa
 * Material animation
 *
 * Revision 1.5  2006/06/20 19:06:52  southa
 * Object creation
 *
 * Revision 1.4  2006/06/19 15:57:17  southa
 * Materials
 *
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
MushGLMaterial::TexNameSet(const std::string& inName, Mushware::U32 inFrame, Mushware::U32 inTexNum)
{
    if (m_multiTexRefs.size() <= inFrame)
	{
		m_multiTexRefs.resize(inFrame + 1);	
	}
    tMultiTextureRef& multiTexRef = m_multiTexRefs[inFrame];
    
    if (multiTexRef.size() <= inTexNum)
	{
		multiTexRef.resize(inTexNum + 1);	
	}
	multiTexRef[inTexNum].NameSet(inName);
}

const MushGLMaterial::tMultiTextureRef&
MushGLMaterial::MultiTextureRef(Mushware::U32 inFrame) const
{
	if (inFrame >= m_multiTexRefs.size())
	{
		std::ostringstream message;
		message << "Material '" << Name() << "' has " << m_multiTexRefs.size() << " frames but frame " << inFrame << " requested";
		throw MushcoreRequestFail(message.str());
	}
	return m_multiTexRefs[inFrame];
}

MushGLTexture&
MushGLMaterial::TexRef(Mushware::U32 inFrame, Mushware::U32 inTexNum) const
{
    const tMultiTextureRef& multiTexRef = MultiTextureRef(inFrame);
    
	if (inTexNum >= multiTexRef.size())
	{
		std::ostringstream message;
		message << "Material '" << Name() << "' frame " << inFrame << " has " << multiTexRef.size() << " textures but index " << inTexNum << " requested";
		throw MushcoreRequestFail(message.str());
	}
	return multiTexRef[inTexNum].WRef();
}

Mushware::U32
MushGLMaterial::AnimatorToFrame(Mushware::tVal inAnimator) const
{
    U32 retVal = 0;
    
    U32 numMulti = m_multiTexRefs.size();
    
    if (numMulti > 0)
    {
        retVal = static_cast<U32>(std::fabs(inAnimator) * numMulti);
        if (retVal >= numMulti)
        {
            // Catch inAnimator >= 1.0
            retVal = numMulti - 1;
        }
    }
    return retVal;
}

MushGLTexture&
MushGLMaterial::AnimatedTexRef(Mushware::tVal inAnimator, Mushware::U32 inTexNum) const
{
    return TexRef(AnimatorToFrame(inAnimator), inTexNum);
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
        std::vector<std::string> textureNames;
		U32 mappingType = kMappingTypeNone;
        
		tRubyHash::const_iterator endIter = paramHash.end();
		for (tRubyHash::const_iterator p = paramHash.begin(); p != endIter; ++p)
		{
			tRubyID symbol = p->first.Symbol();
			if (symbol == MushRubyIntern::name())
			{
				materialName = p->second.String();
			}
			else if (symbol == MushRubyIntern::texture_names())
			{
                if (!p->second.IsArray())
                {
                    MushRubyUtil::Raise(":texture_names parameters must be an array");	
                    
                }
                U32 size = p->second.ArraySize();
                for (U32 i=0; i<size; ++i)
                {
				    textureNames.push_back(p->second.ArrayEntry(i).String());
                }
			}
			else if (symbol == MushRubyIntern::SymbolID("mapping_type"))
			{
                tRubyID typeSymbol = p->second.Symbol();
                if (typeSymbol == MushRubyIntern::SymbolID("none"))
                {
                    mappingType = kMappingTypeNone;
                }
                else if (typeSymbol == MushRubyIntern::SymbolID("tiled"))
                {
                    mappingType = kMappingTypeTiled;
                }
                else if (typeSymbol == MushRubyIntern::SymbolID("singular"))
                {
                    mappingType = kMappingTypeSingular;
                }
                else
                {
                    MushRubyUtil::Raise("Bad mapping type (should be :none, :tiled or :singular)");	
                }
            }
			else
			{
				MushRubyUtil::Raise("Unknown name in parameter hash '"+p->first.String()+"'");	
			}
		}			
				
		if (materialName == "" || textureNames.size() == 0)
		{
			MushRubyUtil::Raise("Both :name and :texture_names parameters must be supplied");	
			
		}
		
		MushGLMaterial *pMaterial = dynamic_cast<MushGLMaterial *>(MushcoreData<MushMesh4Material>::Sgl().Give(materialName, new MushGLMaterial));
		pMaterial->NameSet(materialName);
        pMaterial->MappingTypeSet(mappingType);
            
        for (U32 i=0; i<textureNames.size(); ++i)
        {
		    pMaterial->TexNameSet(textureNames[i], i, 0);
        }
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
    ioOut << "multiTexRefs=" << m_multiTexRefs;
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
    else if (inTagStr == "multiTexRefs")
    {
        ioIn >> m_multiTexRefs;
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
    ioOut.TagSet("multiTexRefs");
    ioOut << m_multiTexRefs;
}
//%outOfLineFunctions } sqgVyGcaZ7BP29i7Dy1rcw
