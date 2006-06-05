//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLCacheControl.cpp
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
//%Header } vYDFvfnYgaI4ZFA13k+Usg
/*
 * $Id$
 * $Log$
 */

#include "MushGLCacheControl.h"

MUSHCORE_SINGLETON_INSTANCE(MushGLCacheControl);

using namespace Mushware;
using namespace std;

MushGLCacheControl::MushGLCacheControl() :
	m_permitCache(true),
	m_permitCompression(true),
	m_globalCachePath(""),
	m_textureCacheHits(0),
	m_textureCacheMisses(0)
{
	MushcoreScalar globalCachePath;
	if (MushcoreEnv::Sgl().VariableGetIfExists(globalCachePath, "GLOBAL_CACHE_PATH"))
	{
		m_globalCachePath = globalCachePath.StringGet();
	}
	else
	{
		m_permitCache = false;	
	}
	
	MushcoreScalar textureCache;
	if (MushcoreEnv::Sgl().VariableGetIfExists(textureCache, "MUSHGL_TEXTURE_CACHE"))
	{
		m_permitCache = textureCache.BoolGet();
	}

	m_hashSeed = std::string(kFilenameHashLength, 'A');
	m_hashSeed = HashedFilenameMake(MushcoreInfo::Sgl().PackageID());
	MUSHCOREASSERT(m_hashSeed.size() == kFilenameHashLength);
}

std::string
MushGLCacheControl::HashedFilenameMake(const std::string& inName)
{
	std::string hashedFilename(m_hashSeed);
	
	MUSHCOREASSERT(hashedFilename.size() == kFilenameHashLength);
	
	U32 j=0;
	for (U32 i=0; i<inName.size(); ++i)
	{
		hashedFilename[j] ^= inName[i];
		j = (j+1) % kFilenameHashLength;
	}
	for (U32 i=0; i < kFilenameHashLength; ++i)
	{
		hashedFilename[i] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"[static_cast<U8>(hashedFilename[i]) % 32];
	}
	return hashedFilename;
}

std::string
MushGLCacheControl::TextureCacheFilenameMake(const std::string& inName)
{
	std::string filename;
	if (m_globalCachePath == "")
	{
	    throw MushcoreRequestFail("No global cache path defined");	
	}
	
	filename = m_globalCachePath+"/tex-"+HashedFilenameMake(inName)+".tiff";
	return filename;
}

std::string
MushGLCacheControl::TextureCachePlainFilenameMake(const std::string& inName)
{
	std::string filename;
	if (m_globalCachePath == "")
	{
	    throw MushcoreRequestFail("No global cache path defined");	
	}
	
	filename = m_globalCachePath+"/"+inName;
	return filename;
}



//%outOfLineFunctions {

const char *MushGLCacheControl::AutoName(void) const
{
    return "MushGLCacheControl";
}

MushcoreVirtualObject *MushGLCacheControl::AutoClone(void) const
{
    return new MushGLCacheControl(*this);
}

MushcoreVirtualObject *MushGLCacheControl::AutoCreate(void) const
{
    return new MushGLCacheControl;
}

MushcoreVirtualObject *MushGLCacheControl::AutoVirtualFactory(void)
{
    return new MushGLCacheControl;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGLCacheControl", MushGLCacheControl::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGLCacheControl::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "permitCache=" << m_permitCache << ", ";
    ioOut << "permitCompression=" << m_permitCompression << ", ";
    ioOut << "globalCachePath=" << m_globalCachePath << ", ";
    ioOut << "hashSeed=" << m_hashSeed << ", ";
    ioOut << "textureCacheHits=" << m_textureCacheHits << ", ";
    ioOut << "textureCacheMisses=" << m_textureCacheMisses;
    ioOut << "]";
}
bool
MushGLCacheControl::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "permitCache")
    {
        ioIn >> m_permitCache;
    }
    else if (inTagStr == "permitCompression")
    {
        ioIn >> m_permitCompression;
    }
    else if (inTagStr == "globalCachePath")
    {
        ioIn >> m_globalCachePath;
    }
    else if (inTagStr == "hashSeed")
    {
        ioIn >> m_hashSeed;
    }
    else if (inTagStr == "textureCacheHits")
    {
        ioIn >> m_textureCacheHits;
    }
    else if (inTagStr == "textureCacheMisses")
    {
        ioIn >> m_textureCacheMisses;
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushGLCacheControl::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("permitCache");
    ioOut << m_permitCache;
    ioOut.TagSet("permitCompression");
    ioOut << m_permitCompression;
    ioOut.TagSet("globalCachePath");
    ioOut << m_globalCachePath;
    ioOut.TagSet("hashSeed");
    ioOut << m_hashSeed;
    ioOut.TagSet("textureCacheHits");
    ioOut << m_textureCacheHits;
    ioOut.TagSet("textureCacheMisses");
    ioOut << m_textureCacheMisses;
}
//%outOfLineFunctions } dzmANVo9gIP5goz2lfkTvw
