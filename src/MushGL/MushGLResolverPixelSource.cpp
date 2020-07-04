//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLResolverPixelSource.cpp
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
//%Header } BhD9jTy6jMlsKqTkVsqX0g
/*
 * $Id: MushGLResolverPixelSource.cpp,v 1.6 2006/06/07 12:15:19 southa Exp $
 * $Log: MushGLResolverPixelSource.cpp,v $
 * Revision 1.6  2006/06/07 12:15:19  southa
 * Grid and test textures
 *
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
