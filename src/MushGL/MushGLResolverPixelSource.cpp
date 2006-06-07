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
 * $Id: MushGLResolverPixelSource.cpp,v 1.5 2006/06/06 17:58:32 southa Exp $
 * $Log: MushGLResolverPixelSource.cpp,v $
 * Revision 1.5  2006/06/06 17:58:32  southa
 * Ruby texture definition
 *
 * Revision 1.4  2006/06/06 10:29:51  southa
 * Ruby texture definitions
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


#include "MushGLResolverPixelSource.h"

#include "MushGLPixelSourceTIFF.h"

MUSHCORE_SINGLETON_INSTANCE(MushGLResolverPixelSource);

using namespace Mushware;
using namespace std;

MushGLResolverPixelSource::MushGLResolverPixelSource()
{
	m_sourcePrefixes.push_front("");	
}

MushGLPixelSource&
MushGLResolverPixelSource::ParamHashResolve(const Mushware::tRubyHash& inHash)
{
	std::auto_ptr<MushGLPixelSource> aResolver(NULL);
	std::string textureName;
	
    tRubyHash::const_iterator endIter = inHash.end();
    for (tRubyHash::const_iterator p = inHash.begin(); p != endIter; ++p)
    {
		if (p->first.String() == "type")
		{
			bool found = false;

			for (tSourcePrefixes::const_iterator q = m_sourcePrefixes.begin();
				 !found && q != m_sourcePrefixes.end(); ++q)
			{
				std::string className = *q + p->second.String();

				if (MushcoreFactory::Sgl().Exists(className))
				{
					aResolver.reset(dynamic_cast<MushGLPixelSource *>(
						MushcoreFactory::Sgl().ObjectCreate(className)));
					found = true;
				}
			}
			
			if (!found || aResolver.get() == NULL)
			{
				throw MushcoreRequestFail("Unknown texture type '"+p->second.String()+"'");
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
	
	// Let the new pixel source process the parameter hash
	aResolver->ParamHashDecode(inHash);
	
	/* Keep this at the end, so that any exceptions delete the texture
	 * partially constructed texture via the auto_ptr
	 */
	MushGLPixelSource *pPixelSource = MushcoreData<MushGLPixelSource>::Sgl().Give(textureName, aResolver.release());
	pPixelSource->NameSet(textureName);
	
	return *pPixelSource;
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
    ioOut << "sourcePrefixes=" << m_sourcePrefixes;
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
    else if (inTagStr == "sourcePrefixes")
    {
        ioIn >> m_sourcePrefixes;
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
    ioOut.TagSet("sourcePrefixes");
    ioOut << m_sourcePrefixes;
}
//%outOfLineFunctions } crTFBe8DHkTzdc6ybmiMbA
