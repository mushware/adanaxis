//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLPixelSource.cpp
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
//%Header } 4Bm7owQBC2swqTQDrpOFEA
/*
 * $Id: MushGLPixelSource.cpp,v 1.11 2007/03/09 19:50:12 southa Exp $
 * $Log: MushGLPixelSource.cpp,v $
 * Revision 1.11  2007/03/09 19:50:12  southa
 * Resident textures
 *
 * Revision 1.10  2006/11/09 23:53:59  southa
 * Explosion and texture loading
 *
 * Revision 1.9  2006/06/27 11:58:08  southa
 * Warning fixes
 *
 * Revision 1.8  2006/06/07 12:15:19  southa
 * Grid and test textures
 *
 * Revision 1.7  2006/06/06 17:58:32  southa
 * Ruby texture definition
 *
 * Revision 1.6  2006/05/02 17:32:13  southa
 * Texturing
 *
 * Revision 1.5  2005/08/28 22:41:51  southa
 * MushGLTexture work
 *
 * Revision 1.4  2005/07/02 00:42:37  southa
 * Conditioning tweaks
 *
 * Revision 1.3  2005/06/16 17:25:39  southa
 * Client/server work
 *
 * Revision 1.2  2005/05/19 13:02:09  southa
 * Mac release work
 *
 * Revision 1.1  2005/02/13 22:44:07  southa
 * Tesseract stuff
 *
 */

#include "MushGLPixelSource.h"

#include "MushGLResolverPixelSource.h"

using namespace Mushware;
using namespace std;

MUSHCORE_DATA_INSTANCE(MushGLPixelSource);

MUSHCORE_INSTALLER(MushGLPixelSource::Install);

MushGLPixelSource::MushGLPixelSource() :
    m_storageType("GL"),
	m_cacheable(true),
    m_compress(false),
    m_resident(false)
{
}

void
MushGLPixelSource::ParamDecode(const MushRubyValue& inName, const MushRubyValue& inValue)
{
	std::string nameStr = inName.String();
	
	if (nameStr == "name" || nameStr == "type")
    {
		// Ignore - already handled by the resolver
	}
	else if (nameStr == "storagetype")
	{
		m_storageType = inValue.String();
	}
	else if (nameStr == "size")
	{
		m_size = t4U32(inValue.U32Vector());
	}
	else if (nameStr == "cache")
	{
		m_cacheable = inValue.Bool();
	}
	else if (nameStr == "compress")
	{
		m_compress = inValue.Bool();
	}
	else if (nameStr == "resident")
	{
		m_resident = inValue.Bool();
	}
	else
	{
	    throw MushcoreSyntaxFail("Texture parameter '"+nameStr+"' not known by this texture type");	
	}
}

void
MushGLPixelSource::ParamHashDecode(const Mushware::tRubyHash& inHash)
{
    tRubyHash::const_iterator endIter = inHash.end();
    for (tRubyHash::const_iterator p = inHash.begin(); p != endIter; ++p)
    {
		ParamDecode(p->first, p->second);
	}
}

void
MushGLPixelSource::BufferFill(Mushware::U32 * const outPtr, const Mushware::t2U32 inSize) const
{
    throw MushcoreRequestFail("Cannot fill buffer from this pixel source");
}

std::vector<MediaJobId>
MushGLPixelSource::PrerequisitesCreate(MushGLTexture& outTexture)
{
    // No operation
    return std::vector<MediaJobId>();
}

void
MushGLPixelSource::ToTextureCreate(MushGLTexture& outTexture)
{
    throw MushcoreRequestFail("Cannot create texture from this pixel source");
}

void
MushGLPixelSource::ToTextureBind(MushGLTexture& outTexture)
{
    throw MushcoreRequestFail("Cannot bind texture from this pixel source");
}

void 
MushGLPixelSource::DataCreate(void)
{
    // No operation
}

void 
MushGLPixelSource::DataRelease(void)
{
    // No operation
}

const std::vector<Mushware::U8>&
MushGLPixelSource::DataRGBAU8Get(void) const
{
    throw MushcoreRequestFail("Cannot get data from this pixel source");
}

void
MushGLPixelSource::Install(void)
{
	MushGLResolverPixelSource::Sgl().PrefixAdd("MushGLPixelSource");
}

//%outOfLineFunctions {

const char *MushGLPixelSource::AutoName(void) const
{
    return "MushGLPixelSource";
}

MushcoreVirtualObject *MushGLPixelSource::AutoClone(void) const
{
    return new MushGLPixelSource(*this);
}

MushcoreVirtualObject *MushGLPixelSource::AutoCreate(void) const
{
    return new MushGLPixelSource;
}

MushcoreVirtualObject *MushGLPixelSource::AutoVirtualFactory(void)
{
    return new MushGLPixelSource;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGLPixelSource", MushGLPixelSource::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGLPixelSource::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "name=" << m_name << ", ";
    ioOut << "storageType=" << m_storageType << ", ";
    ioOut << "size=" << m_size << ", ";
    ioOut << "cacheable=" << m_cacheable << ", ";
    ioOut << "compress=" << m_compress << ", ";
    ioOut << "resident=" << m_resident;
    ioOut << "]";
}
bool
MushGLPixelSource::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "name")
    {
        ioIn >> m_name;
    }
    else if (inTagStr == "storageType")
    {
        ioIn >> m_storageType;
    }
    else if (inTagStr == "size")
    {
        ioIn >> m_size;
    }
    else if (inTagStr == "cacheable")
    {
        ioIn >> m_cacheable;
    }
    else if (inTagStr == "compress")
    {
        ioIn >> m_compress;
    }
    else if (inTagStr == "resident")
    {
        ioIn >> m_resident;
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushGLPixelSource::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("name");
    ioOut << m_name;
    ioOut.TagSet("storageType");
    ioOut << m_storageType;
    ioOut.TagSet("size");
    ioOut << m_size;
    ioOut.TagSet("cacheable");
    ioOut << m_cacheable;
    ioOut.TagSet("compress");
    ioOut << m_compress;
    ioOut.TagSet("resident");
    ioOut << m_resident;
}
//%outOfLineFunctions } e+oDlasCM53DxZHVQdIBjg
