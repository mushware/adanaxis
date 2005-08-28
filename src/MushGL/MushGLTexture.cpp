//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLTexture.cpp
 *
 * Author: Andy Southgate 2002-2005
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
//%Header } x6YRzHVc1aFZ86XnvPhOUg
/*
 * $Id$
 * $Log$
 */

#include "MushGLTexture.h"

#include "MushGLPixelSource.h"
#include "MushGLResolverPixelSource.h"

using namespace Mushware;
using namespace std;

MUSHCORE_DATA_INSTANCE(MushGLTexture);

MushcoreInstaller MushGLTextureInstaller(MushGLTexture::Install);

void
MushGLTexture::Make(void)
{
    MushGLPixelSource *pSrc = NULL;
    for (U32 i=0;; ++i)
    {
        if (MushcoreData<MushGLPixelSource>::Sgl().GetIfExists(pSrc, m_srcName))
        {
            break;
        }
        if (i>0)
        {
            throw MushcoreRequestFail("Cannot resolve pixel source '"+m_srcName+"' for texture");
        }
        MushGLResolverPixelSource::Sgl().Resolve(m_srcName);
    }
    if (pSrc == NULL)
    {
        MUSHCOREASSERT(false);
        throw MushcoreRequestFail("MushGLTexture::Make failure");
    }
    pSrc->ToTextureCreate(*this);
}

void
MushGLTexture::PixelDataGLRGBAUse(void *pData)
{
    if (!m_bindingNameValid)
    {
        glGenTextures(1, &m_bindingName);
        m_bindingNameValid = true;
    }
    
    glBindTexture(GL_TEXTURE_2D, m_bindingName);

    if (1) // Use MIPMAP
    {
#ifdef GL_VERSION_1_4
        glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
        
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
            throw MushcoreRequestFail(std::string("Error building mipmaps: ") + gluErrorString(err));
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
MushGLTexture::PixelDataUse(void *pData)
{
    if (m_pixelType == kPixelTypeRGBA && m_storageType == kStorageTypeGL)
    {
        PixelDataGLRGBAUse(pData);
    }
    else
    {
        ostringstream message;
        message << "Cannot use data where pixelType=" << m_pixelType << " and storageType=" << m_storageType;
        throw MushcoreRequestFail(message.str());
    }
}

MushcoreScalar
MushGLTexture::Texture(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    string name;
    string srcName;
    if (ioCommand.NumParams() != 2)
    {
        throw(MushcoreCommandFail("Usage: mushgltexture(name, source)"));
    }
    ioCommand.PopParam(name);
    ioCommand.PopParam(srcName);
    
    MushGLTexture *pTexture = MushcoreData<MushGLTexture>::Sgl().Give(name, new MushGLTexture);
    pTexture->SrcNameSet(srcName);
    pTexture->Make();
    return MushcoreScalar(0);
}

void
MushGLTexture::Install(void)
{
    MushcoreInterpreter::Sgl().HandlerAdd("mushgltexture", Texture);
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
    ioOut << "srcName=" << m_srcName;
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
    else if (inTagStr == "srcName")
    {
        ioIn >> m_srcName;
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
    ioOut.TagSet("srcName");
    ioOut << m_srcName;
}
//%outOfLineFunctions } USQvYWdIJZ1BaqqlW1XrbQ
