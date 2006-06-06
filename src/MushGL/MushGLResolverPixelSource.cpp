//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLResolverPixelSource.cpp
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
//%Header } MLe+9IO+KhBjFrt79ygTPg
/*
 * $Id: MushGLResolverPixelSource.cpp,v 1.3 2006/05/02 17:32:13 southa Exp $
 * $Log: MushGLResolverPixelSource.cpp,v $
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


#include "MushGLResolverPixelSource.h"

#include "MushGLPixelSourceTIFF.h"

MUSHCORE_SINGLETON_INSTANCE(MushGLResolverPixelSource);

using namespace Mushware;
using namespace std;

void
MushGLResolverPixelSource::ParamDecode(MushGLPixelSource& outSource, 
									   const MushRubyValue& inName, const MushRubyValue& inValue)
{
	MushcoreLog::Sgl().InfoLog() << "Param name " << inName << "=" << inValue << endl;
}	

void
MushGLResolverPixelSource::ParamHashDecode(MushGLPixelSource& outSource, const Mushware::tRubyHash& inHash)
{
    tRubyHash::const_iterator endIter = inHash.end();
    for (tRubyHash::const_iterator p = inHash.begin(); p != endIter; ++p)
    {
		ParamDecode(outSource, p->first, p->second);
	}
}

void
MushGLResolverPixelSource::ParamHashResolve(const Mushware::tRubyHash& inHash)
{
	std::auto_ptr<MushGLPixelSource> aResolver(NULL);
	std::string textureName;
	
    tRubyHash::const_iterator endIter = inHash.end();
    for (tRubyHash::const_iterator p = inHash.begin(); p != endIter; ++p)
    {
		if (p->first.String() == "type")
		{
			try
			{
				aResolver.reset(dynamic_cast<MushGLPixelSource *>(
					MushcoreFactory::Sgl().ObjectCreate("MushGLPixelSource"+p->second.String())
																));
			}
			catch (MushcoreFail& e)
			{
			    throw MushcoreRequestFail("Unknown texture type '"+p->first.String()+"': "+e.what());;		
			}
		}
		
		if (p->first.String() == "name")
		{
			textureName = p->second.String();
		}
		
	}
	
	if (textureName == "")
	{
		throw MushcoreRequestFail("No 'name' parameter specified for texture");		
	}
	if (aResolver.get() == NULL)
	{
		throw MushcoreRequestFail("No 'type' parameter specified for texture");		
	}
	
	MushcoreData<MushGLPixelSource>::Sgl().Give(textureName, aResolver.release());
}

void
MushGLResolverPixelSource::Resolve(const std::string& inSrcName)
{
    MushcoreRegExp regExp;
    MushcoreRegExp::tMatches matches;
    regExp.SearchPatternSet("file=\"([^\"]+\\.tiff?)\"");
    if (regExp.Search(matches, inSrcName))
    {
        MUSHCOREASSERT(matches.size() == 1);
        std::string filenameStr = matches[0];
        
        std::string storageType = "GL";
        regExp.SearchPatternSet("\\bstoragetype=\"([^\"]*)\"");
        if (regExp.Search(matches, inSrcName))
        {
            MUSHCOREASSERT(matches.size() == 1);
            storageType = matches[0];
        }

        std::auto_ptr<MushGLPixelSourceTIFF> aResolver(new MushGLPixelSourceTIFF);
        aResolver->StringParameterSet(MushGLPixelSource::kParamFilename, filenameStr);
        aResolver->StringParameterSet(MushGLPixelSource::kParamStorageType, storageType);
        MushcoreData<MushGLPixelSource>::Sgl().Give(inSrcName, aResolver.release());
    }
    else
    {
        throw MushcoreRequestFail("Cannot resolve pixel source for '"+inSrcName+"'");   
    }
}

//%outOfLineFunctions {

const char *MushGLResolverPixelSource::AutoName(void) const
{
    return "MushGLResolverPixelSource";
}

MushcoreVirtualObject *MushGLResolverPixelSource::AutoClone(void) const
{
    throw MushcoreRequestFail("Cannot clone 'MushGLResolverPixelSource'");;
}

MushcoreVirtualObject *MushGLResolverPixelSource::AutoCreate(void) const
{
    return new MushGLResolverPixelSource;
}

MushcoreVirtualObject *MushGLResolverPixelSource::AutoVirtualFactory(void)
{
    return new MushGLResolverPixelSource;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGLResolverPixelSource", MushGLResolverPixelSource::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGLResolverPixelSource::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "]";
}
bool
MushGLResolverPixelSource::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushGLResolverPixelSource::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
}
//%outOfLineFunctions } qoplTn4svQXPIwDeos01Bw
