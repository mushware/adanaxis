//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLTexture.cpp
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
//%Header } vh/xCnesmbXGxXqZK5YEaA
/*
 * $Id: MushGLTexture.cpp,v 1.19 2006/11/12 14:39:50 southa Exp $
 * $Log: MushGLTexture.cpp,v $
 * Revision 1.19  2006/11/12 14:39:50  southa
 * Player weapons amd audio fix
 *
 * Revision 1.18  2006/11/09 23:53:59  southa
 * Explosion and texture loading
 *
 * Revision 1.17  2006/11/07 11:08:54  southa
 * Texture loading from mushfiles
 *
 * Revision 1.16  2006/07/28 16:52:22  southa
 * Options work
 *
 * Revision 1.15  2006/07/17 14:43:39  southa
 * Billboarded deco objects
 *
 * Revision 1.14  2006/06/30 15:05:33  southa
 * Texture and buffer purge
 *
 * Revision 1.13  2006/06/16 12:11:04  southa
 * Ruby subclasses
 *
 * Revision 1.12  2006/06/12 11:59:38  southa
 * Ruby wrapper for MushMeshVector
 *
 * Revision 1.11  2006/06/09 21:07:13  southa
 * Tiled skin generation
 *
 * Revision 1.10  2006/06/07 12:15:19  southa
 * Grid and test textures
 *
 * Revision 1.9  2006/06/06 17:58:32  southa
 * Ruby texture definition
 *
 * Revision 1.8  2006/06/06 10:29:51  southa
 * Ruby texture definitions
 *
 * Revision 1.7  2006/06/05 16:54:44  southa
 * Ruby textures
 *
 * Revision 1.6  2006/06/05 11:48:25  southa
 * Noise textures
 *
 * Revision 1.5  2006/06/02 18:14:36  southa
 * Texture caching
 *
 * Revision 1.4  2006/06/01 20:12:59  southa
 * Initial texture caching
 *
 * Revision 1.3  2006/05/02 17:32:13  southa
 * Texturing
 *
 * Revision 1.2  2005/08/29 18:40:57  southa
 * Solid rendering work
 *
 * Revision 1.1  2005/08/28 22:41:52  southa
 * MushGLTexture work
 *
 */

#include "MushGLTexture.h"

#include "MushGLCacheControl.h"
#include "MushGLPixelSource.h"
#include "MushGLPixelSourceTIFF.h"
#include "MushGLResolverPixelSource.h"
#include "MushGLTIFFUtil.h"
#include "MushGLUtil.h"
#include "MushGLV.h"

using namespace Mushware;
using namespace std;

MUSHCORE_DATA_INSTANCE(MushGLTexture);

MushcoreInstaller MushGLTextureInstaller(MushGLTexture::Install);

Mushware::tSize MushGLTexture::m_byteCount = 0;

void
MushGLTexture::Make(void)
{	
	// This cache load should still happen if m_made is true
	if (m_cacheable && MushGLCacheControl::Sgl().PermitCache())
	{
		m_compress = MushGLCacheControl::Sgl().PermitCompression();
        if (FromCacheLoad())
		{
			m_made = true;
		}
	}

	if (!m_made)
	{
		// Switch off compression when generating, so we save a pristine copy to the cache
		m_compress = false;
		
		MushGLPixelSource *pSrc = NULL;
		
		if (!MushcoreData<MushGLPixelSource>::Sgl().GetIfExists(pSrc, m_name))
		{
			throw MushcoreRequestFail("Cannot resolve pixel source '"+m_name+"' for texture");
		}

		if (pSrc == NULL)
		{
			MUSHCOREASSERT(false);
			throw MushcoreRequestFail("MushGLTexture::Make failure");
		}
		pSrc->ToTextureCreate(*this);
		m_cacheable = pSrc->Cacheable();
		
		// Built this texture the hard way, so save to cache
		m_cacheSaveRequired = m_cacheable;
		m_made = true;
	}
}

void
MushGLTexture::Bind(void)
{
    if (!m_made)
    {
        Make();
    }
	
    if (!m_bindingNameValid)
    {
        throw MushcoreRequestFail("MushGLTexture::Bind attempt on non-GL texture");
    }
	
    MushGLV::Sgl().BindTexture2D(m_bindingName);
	
	if (m_cacheSaveRequired)
	{
		m_cacheSaveRequired = false;
		if (m_cacheable && MushGLCacheControl::Sgl().PermitCache())
		{
		    ToCacheSave();
			
			if (MushGLCacheControl::Sgl().PermitCompression())
			{
				// Remake to load the compressed version
				Make();
			}
		}
	}
}

void
MushGLTexture::Purge(void)
{
    if (m_bindingNameValid)
    {
        MushGLV::Sgl().DeleteTexture(m_bindingName);
        m_bindingNameValid = false;
        m_made = false;
        m_bound = false;
    }
}

void
MushGLTexture::ToCacheSave(void)
{
	try
	{
        if (m_saveable)
        {
            m_cacheFilename = MushGLCacheControl::Sgl().TextureCacheFilenameMake(m_uniqueIdentifier);
            MushGLTIFFUtil::TextureSave(m_cacheFilename, m_uniqueIdentifier);
        }
	}
	catch (MushcoreNonFatalFail& e)
	{
		MushcoreLog::Sgl().InfoLog() << "Texture save to cache failed: " << e.what() << endl;
	}
}

bool
MushGLTexture::FromCacheLoad(void)
{
	bool success = false;
	
	m_cacheFilename = MushGLCacheControl::Sgl().TextureCacheFilenameMake(m_uniqueIdentifier);
    MushGLPixelSourceTIFF pixelSourceTIFF;
	
	pixelSourceTIFF.FilenameSet(m_cacheFilename);
	
	try
	{
		pixelSourceTIFF.ToTextureCreate(*this);
		MushGLCacheControl::Sgl().TextureCacheHitRegister();
		MushcoreLog::Sgl().InfoLog() << "Loaded cache texture: '" << m_name << "' from '" << m_cacheFilename << "'" << endl;
		success = true;
		
#ifdef MUSHCORE_DEBUG
        if (m_saveable)
        {
            std::string saveFilename = m_cacheFilename.substr(0, m_cacheFilename.size()-5);
            MushGLTIFFUtil::TextureSave(saveFilename+"-resaved.tiff", m_name);
        }
#endif

	}
	catch (MushcoreNonFatalFail& e)
	{
		MushcoreLog::Sgl().InfoLog() << "Texture cache miss: '" << m_name << "' (loads from '" << m_cacheFilename << "')" << endl;
		MushGLCacheControl::Sgl().TextureCacheMissRegister();
	}
	return success;
}

void
MushGLTexture::PixelDataGLRGBAUse(void *pData)
{
    if (!MushGLV::Sgl().ContextValid())
    {
        throw MushcoreRequestFail("Cannot create texture because OpenGL context not valid yet");
    }
    
    if (!m_bindingNameValid)
    {
        glGenTextures(1, &m_bindingName);
        m_bindingNameValid = true;
    }
    
    MushGLV::Sgl().BindTexture2D(m_bindingName);

    if (1) // Use MIPMAP
    {
#ifdef GL_VERSION_1_4
        glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
        glHint(GL_TEXTURE_COMPRESSION_HINT, GL_NICEST);

		GLenum internalFormat;
		
		if (m_compress && MushGLV::Sgl().UseS3TC())
		{
			internalFormat = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
		}
		else
		{
		    internalFormat = GL_RGBA;	
		}
		
        glTexImage2D(GL_TEXTURE_2D,      // target
                     0,                  // level
                     internalFormat,     // internal format
                     m_size.X(),         // width
                     m_size.Y(),         // height
                     0,                  // border
                     GL_RGBA,            // format
                     GL_UNSIGNED_BYTE,   // type
                     pData               // pointer to data
                     );
		
        Mushware::U32 naturalSize = m_size.X() * m_size.Y() * 4; // 1.33 factor for mipmapping
		GLint compFlag = GL_FALSE;
        GLint compSize = 0;
		glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_COMPRESSED, &compFlag);
		if (compFlag == GL_TRUE)
		{
			glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_COMPRESSED_IMAGE_SIZE, &compSize);
            m_byteCount += compSize;
#ifdef MUSHCORE_DEBUG        
            MushcoreLog::Sgl().InfoLog() << "Compressed texture (natural size " << naturalSize
                << " bytes) to " << compSize << " bytes (" << 100*compSize/naturalSize << "%)" << endl;
#endif
		}
        else
        {
            m_byteCount += naturalSize;
        }
        MushGLUtil::CheckGLError("Texture load");
        
		
#else
        GLint err=gluBuild2DMipmaps(GL_TEXTURE_2D,    // target
                                    4,                // components
                                    m_size.X(),       // width
                                    m_size.Y(),       // height
                                    GL_RGBA,          // format
                                    GL_UNSIGNED_BYTE, // type
                                    pData             // pointer to data
                                    );
        if (err != 0)
        {
            // throw MushcoreRequestFail(std::string("Error building mipmaps: ") + gluErrorString(err));
        }
#endif
    }
    else
    {
#ifdef GL_VERSION_1_4
        glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_FALSE);
#endif
        
        glTexImage2D(GL_TEXTURE_2D,    // target
                     0,                // level
                     GL_RGBA,          // internal format
                     m_size.X(),       // width
                     m_size.Y(),       // height
                     0,                // border
                     GL_RGBA,          // format
                     GL_UNSIGNED_BYTE, // type
                     pData             // pointer to data
                     );
    }
    m_bound=true;
}

void
MushGLTexture::PixelDataU8RGBAUse(void *pData)
{
    m_bindingNameValid = false;
    m_bound = false;
    U32 storageSize = 4*m_size.X()*m_size.Y();
    m_u8Data.resize(storageSize);
    memcpy(&m_u8Data[0], pData, storageSize);
}        

Mushware::t4Val
MushGLTexture::U8RGBALookup(Mushware::t2Val inPos) const
{
    if (m_pixelType != kPixelTypeRGBA || m_storageType != kStorageTypeU8Data)
    {
        ostringstream message;
        message << "U8RGBALookup not possible when pixelType=" << m_pixelType << " and storageType=" << m_storageType;
        throw MushcoreRequestFail(message.str());
    }
    
    // Input values spanning the texture in the range 0 < x < 1
    tVal x = inPos.X();
    tVal y = inPos.Y();
    
    tVal xFrac, yFrac;
    
    double xInteger, yInteger;

    if (x<0)
    {
        std::modf(x, &xInteger);
        x += xInteger+1;
    }
    
    if (y<0)
    {
        std::modf(y, &yInteger);
        y += yInteger+1;
    }

    xFrac = std::modf(std::fmod(m_size.X()*x, m_size.X()), &xInteger);
	yFrac = std::modf(std::fmod(m_size.Y()*y, m_size.Y()), &yInteger);
	
	if (xInteger < 0) xInteger = 0;
	if (yInteger < 0) yInteger = 0;
	
    U32 x0 = static_cast<U32>(xInteger);
    U32 y0 = static_cast<U32>(yInteger);
    
	MUSHCOREASSERT(x0 < m_size.X());
	MUSHCOREASSERT(y0 < m_size.Y());
	
    U32 x1 = x0+1;
    if (x1 >= m_size.X()) x1 = 0;
    U32 y1 = y0+1;
    if (y1 >= m_size.Y()) y1 = 0;

    const U8 *p00 = &m_u8Data[4*(y0*m_size.X()+x0)];
    const U8 *p10 = &m_u8Data[4*(y0*m_size.X()+x1)];
    const U8 *p01 = &m_u8Data[4*(y1*m_size.X()+x0)];
    const U8 *p11 = &m_u8Data[4*(y1*m_size.X()+x1)];
    
    MUSHCOREASSERT(p00 >= &m_u8Data[0] && p00 < &m_u8Data[m_u8Data.size()]);
    MUSHCOREASSERT(p10 >= &m_u8Data[0] && p10 < &m_u8Data[m_u8Data.size()]);
    MUSHCOREASSERT(p01 >= &m_u8Data[0] && p01 < &m_u8Data[m_u8Data.size()]);
    MUSHCOREASSERT(p11 >= &m_u8Data[0] && p11 < &m_u8Data[m_u8Data.size()]);
	
    t4Val col00 = t4Val(p00[0], p00[1], p00[2], p00[3]);
    t4Val col10 = t4Val(p10[0], p10[1], p10[2], p10[3]);
    t4Val col01 = t4Val(p01[0], p01[1], p01[2], p01[3]);
    t4Val col11 = t4Val(p11[0], p11[1], p11[2], p11[3]);

    t4Val retVal = (col00 * (1-xFrac) + col10 * xFrac) * (1-yFrac) +
        (col01 * (1-xFrac) + col11 * xFrac) * yFrac;
    
    return retVal;
}

void
MushGLTexture::PixelDataUse(void *pData)
{
    if (m_pixelType == kPixelTypeRGBA && m_storageType == kStorageTypeGL)
    {
        PixelDataGLRGBAUse(pData);
    }
    else if (m_pixelType == kPixelTypeRGBA && m_storageType == kStorageTypeU8Data)
    {
        PixelDataU8RGBAUse(pData);
    }
    else
    {
        ostringstream message;
        message << "Cannot use data where pixelType=" << m_pixelType << " and storageType=" << m_storageType;
        throw MushcoreRequestFail(message.str());
    }
}

void
MushGLTexture::StorageTypeSet(const std::string& inType)
{
    if (inType == "gl" || inType == "GL")
    {
        m_storageType = kStorageTypeGL;
    }
    else  if (inType == "u8" || inType == "U8")
    {
        m_storageType = kStorageTypeU8Data;
    }
    else
    {
        m_storageType = kStorageTypeNone;
        throw MushcoreRequestFail("Unknown pixel storage type '"+inType+"'");
    }
}

Mushware::tRubyValue
MushGLTexture::RubyDefine(Mushware::tRubyArgC inArgC, Mushware::tRubyValue *inpArgV, Mushware::tRubyValue inSelf)
{
	try
	{
		if (inArgC != 1)
		{
			throw MushRubyFail("Wrong number of parameters to RubyDefine");	
		}

		Mushware::tRubyHash paramHash;
		MushRubyUtil::HashConvert(paramHash, MushRubyValue(inpArgV[0]));
		
		MushGLPixelSource& pixelSource = MushGLResolverPixelSource::Sgl().ParamHashResolve(paramHash);
		std::string textureName = pixelSource.Name();
		
		MushGLTexture *pTexture = MushcoreData<MushGLTexture>::Sgl().Give(textureName, new MushGLTexture);
		pTexture->NameSet(textureName);
		pTexture->CacheableSet(pixelSource.Cacheable());
		std::ostringstream hashStream;
		hashStream << paramHash;
		pTexture->UniqueIdentifierSet(hashStream.str());
	}
	catch (MushcoreFail& e)
	{
		MushRubyUtil::Raise(e.what());
	}

	return Mushware::kRubyQnil;
}

Mushware::tRubyValue
MushGLTexture::RubyPreCache(Mushware::tRubyArgC inArgC, Mushware::tRubyValue *inpArgV, Mushware::tRubyValue inSelf)
{
	try
	{
		if (inArgC != 1)
		{
			throw MushRubyFail("Wrong number of parameters to RubyPreCache");	
		}
		
		std::string textureName = MushRubyValue(inpArgV[0]).String();
		
		MushGLTexture *pTexture = MushcoreData<MushGLTexture>::Sgl().Get(textureName);
		pTexture->Make();
		pTexture->Bind();
	}
	catch (MushcoreFail& e)
	{
		MushRubyUtil::Raise(e.what());
	}

	return Mushware::kRubyQnil;
}

void
MushGLTexture::RubyInstall(void)
{
	Mushware::tRubyValue klass = MushRubyUtil::ClassDefine("MushGLTexture");
	MushRubyUtil::SingletonMethodDefine(klass, "cRubyDefine", RubyDefine);
	MushRubyUtil::SingletonMethodDefine(klass, "cRubyPreCache", RubyPreCache);
}	

void
MushGLTexture::Install(void)
{
	MushRubyInstall::Sgl().Add(RubyInstall);
}

//%outOfLineFunctions {

const char *MushGLTexture::AutoName(void) const
{
    return "MushGLTexture";
}

MushcoreVirtualObject *MushGLTexture::AutoClone(void) const
{
    throw MushcoreRequestFail("Cannot clone 'MushGLTexture'");;
}

MushcoreVirtualObject *MushGLTexture::AutoCreate(void) const
{
    return new MushGLTexture;
}

MushcoreVirtualObject *MushGLTexture::AutoVirtualFactory(void)
{
    return new MushGLTexture;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGLTexture", MushGLTexture::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGLTexture::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "u8Data=" << m_u8Data << ", ";
    ioOut << "valData=" << m_valData << ", ";
    ioOut << "size=" << m_size << ", ";
    ioOut << "bound=" << m_bound << ", ";
    ioOut << "bindingNameValid=" << m_bindingNameValid << ", ";
    ioOut << "bindingName=" << m_bindingName << ", ";
    ioOut << "pixelType=" << m_pixelType << ", ";
    ioOut << "storageType=" << m_storageType << ", ";
    ioOut << "uniqueIdentifier=" << m_uniqueIdentifier << ", ";
    ioOut << "name=" << m_name << ", ";
    ioOut << "cacheFilename=" << m_cacheFilename << ", ";
    ioOut << "cacheable=" << m_cacheable << ", ";
    ioOut << "cacheSaveRequired=" << m_cacheSaveRequired << ", ";
    ioOut << "compress=" << m_compress << ", ";
    ioOut << "made=" << m_made << ", ";
    ioOut << "saveable=" << m_saveable;
    ioOut << "]";
}
bool
MushGLTexture::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "u8Data")
    {
        ioIn >> m_u8Data;
    }
    else if (inTagStr == "valData")
    {
        ioIn >> m_valData;
    }
    else if (inTagStr == "size")
    {
        ioIn >> m_size;
    }
    else if (inTagStr == "bound")
    {
        ioIn >> m_bound;
    }
    else if (inTagStr == "bindingNameValid")
    {
        ioIn >> m_bindingNameValid;
    }
    else if (inTagStr == "bindingName")
    {
        ioIn >> m_bindingName;
    }
    else if (inTagStr == "pixelType")
    {
        ioIn >> m_pixelType;
    }
    else if (inTagStr == "storageType")
    {
        ioIn >> m_storageType;
    }
    else if (inTagStr == "uniqueIdentifier")
    {
        ioIn >> m_uniqueIdentifier;
    }
    else if (inTagStr == "name")
    {
        ioIn >> m_name;
    }
    else if (inTagStr == "cacheFilename")
    {
        ioIn >> m_cacheFilename;
    }
    else if (inTagStr == "cacheable")
    {
        ioIn >> m_cacheable;
    }
    else if (inTagStr == "cacheSaveRequired")
    {
        ioIn >> m_cacheSaveRequired;
    }
    else if (inTagStr == "compress")
    {
        ioIn >> m_compress;
    }
    else if (inTagStr == "made")
    {
        ioIn >> m_made;
    }
    else if (inTagStr == "saveable")
    {
        ioIn >> m_saveable;
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushGLTexture::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("u8Data");
    ioOut << m_u8Data;
    ioOut.TagSet("valData");
    ioOut << m_valData;
    ioOut.TagSet("size");
    ioOut << m_size;
    ioOut.TagSet("bound");
    ioOut << m_bound;
    ioOut.TagSet("bindingNameValid");
    ioOut << m_bindingNameValid;
    ioOut.TagSet("bindingName");
    ioOut << m_bindingName;
    ioOut.TagSet("pixelType");
    ioOut << m_pixelType;
    ioOut.TagSet("storageType");
    ioOut << m_storageType;
    ioOut.TagSet("uniqueIdentifier");
    ioOut << m_uniqueIdentifier;
    ioOut.TagSet("name");
    ioOut << m_name;
    ioOut.TagSet("cacheFilename");
    ioOut << m_cacheFilename;
    ioOut.TagSet("cacheable");
    ioOut << m_cacheable;
    ioOut.TagSet("cacheSaveRequired");
    ioOut << m_cacheSaveRequired;
    ioOut.TagSet("compress");
    ioOut << m_compress;
    ioOut.TagSet("made");
    ioOut << m_made;
    ioOut.TagSet("saveable");
    ioOut << m_saveable;
}
//%outOfLineFunctions } VKOa5rKnPvep/vVpGpU9eg

