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
 * $Id: MushGLTexture.cpp,v 1.2 2005/08/29 18:40:57 southa Exp $
 * $Log: MushGLTexture.cpp,v $
 * Revision 1.2  2005/08/29 18:40:57  southa
 * Solid rendering work
 *
 * Revision 1.1  2005/08/28 22:41:52  southa
 * MushGLTexture work
 *
 */

#include "MushGLTexture.h"

#include "MushGLPixelSource.h"
#include "MushGLResolverPixelSource.h"
#include "MushGLV.h"

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
    m_made = true;
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
MushGLTexture::PixelDataU8RGBAUse(void *pData)
{
    m_bindingNameValid = false;
    m_bound = false;
    U32 storageSize = 4*m_size.X()*m_size.Y();
    m_u8Data.resize(storageSize);
    memcpy(&m_u8Data[0], pData, storageSize);
}        

Mushware::t4Val
MushGLTexture::U8RGBALookup(Mushware::t2Val inPos)
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

    U32 x0 = static_cast<U32>(xInteger);
    U32 y0 = static_cast<U32>(yInteger);
    
    U32 x1 = x0+1;
    if (x1 >= m_size.X()) x1 = 0;
    U32 y1 = y0+1;
    if (y1 >= m_size.Y()) y1 = 0;

    U8 *p00 = &m_u8Data[4*(y0*m_size.X()+x0)];
    U8 *p10 = &m_u8Data[4*(y0*m_size.X()+x1)];
    U8 *p01 = &m_u8Data[4*(y1*m_size.X()+x0)];
    U8 *p11 = &m_u8Data[4*(y1*m_size.X()+x1)];
    
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

MushcoreScalar
MushGLTexture::Texture(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    string name;
    string srcName;
    string flags;
    
    if (ioCommand.NumParams() != 2)
    {
        throw(MushcoreCommandFail("Usage: mushgltexture(name, source)"));
    }
    ioCommand.PopParam(name);
    ioCommand.PopParam(srcName);
    
    MushGLTexture *pTexture = MushcoreData<MushGLTexture>::Sgl().Give(name, new MushGLTexture);
    pTexture->SrcNameSet(srcName);
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
    ioOut << "srcName=" << m_srcName << ", ";
    ioOut << "made=" << m_made;
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
    else if (inTagStr == "made")
    {
        ioIn >> m_made;
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
    ioOut.TagSet("made");
    ioOut << m_made;
}
//%outOfLineFunctions } 9wwaTOCwgkS84wlF+YtV+A
