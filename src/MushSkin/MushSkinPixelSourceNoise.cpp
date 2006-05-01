//%Header {
/*****************************************************************************
 *
 * File: src/MushSkin/MushSkinPixelSourceNoise.cpp
 *
 * Copyright: Andy Southgate 2005-2006
 *
 * This file may be used and distributed under the terms of the Mushware
 * software licence version 1.0, under the terms for 'Proprietary original
 * source files'.  If not supplied with this software, a copy of the licence
 * can be obtained from Mushware Limited via http://www.mushware.com/.
 * One of your options under that licence is to use and distribute this file
 * under the terms of the GNU General Public Licence version 2.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } IHi2qaicNzVbb+bqL7ZTVw
/*
 * $Id: MushSkinPixelSourceNoise.cpp,v 1.2 2006/04/11 23:30:11 southa Exp $
 * $Log: MushSkinPixelSourceNoise.cpp,v $
 * Revision 1.2  2006/04/11 23:30:11  southa
 * Created MushRuby from ruby-1.8.4
 *
 * Revision 1.1  2005/09/06 12:15:35  southa
 * Texture and rendering work
 *
 */

#include "MushSkinPixelSourceNoise.h"

using namespace Mushware;
using namespace std;

void
MushSkinPixelSourceNoise::ValueParameterSet(Mushware::U32 inNum, Mushware::tLongVal inVal)
{
    switch (inNum)
    {
        case kParamXSize:
            m_xSize = static_cast<U32>(inVal);
            break;
        
        case kParamYSize:
            m_ySize = static_cast<U32>(inVal);
            break;
        
        default:
            MushGLPixelSource::ValueParameterSet(inNum, inVal);
            break;
    }
}

void
MushSkinPixelSourceNoise::StringParameterSet(Mushware::U32 inNum, const std::string& inStr)
{
    switch (inNum)
    {
        case kParamSourceName:
            m_sourceName = inStr;
            break;
            
        default:
            MushGLPixelSource::StringParameterSet(inNum, inStr);
            break;
    }
}

void
MushSkinPixelSourceNoise::ToTextureCreate(MushGLTexture& outTexture)
{
    U32 pixelDataSize = 4*m_xSize*m_ySize;
    std::vector<U8> pixelData(pixelDataSize);
    
    MushMesh4Mesh *p4Mesh = MushcoreData<MushMesh4Mesh>::Sgl().Get(m_sourceName);
    
    U32 dataIndex = 0;
    for (U32 y=0; y<m_ySize; ++y)
    {
        for (U32 x=0; x<m_xSize; ++x)
        {
            tVal colourIndex = x+y;
            
            pixelData[dataIndex] = 128+MushcoreUtil::RandomU32(32,64)*sin(x * 1.0); // Red
            pixelData[++dataIndex] = 96+MushcoreUtil::RandomU32(0,127);//128+127*sin(colourIndex * 1.2); // Green
            pixelData[++dataIndex] = 224+MushcoreUtil::RandomU32(16,31)*sin(y*1.1); // Blue
            pixelData[++dataIndex] = 128+127*sin(colourIndex * 0.07); // Alpha
            ++dataIndex;
        }
    }
    
    // Bind the texture
    outTexture.SizeSet(t4U32(m_xSize, m_ySize, 1, 1));
    outTexture.PixelTypeRGBASet();
    outTexture.StorageTypeGLSet();
    outTexture.PixelDataUse(&pixelData[0]);
}

//%outOfLineFunctions {

const char *MushSkinPixelSourceNoise::AutoName(void) const
{
    return "MushSkinPixelSourceNoise";
}

MushcoreVirtualObject *MushSkinPixelSourceNoise::AutoClone(void) const
{
    return new MushSkinPixelSourceNoise(*this);
}

MushcoreVirtualObject *MushSkinPixelSourceNoise::AutoCreate(void) const
{
    return new MushSkinPixelSourceNoise;
}

MushcoreVirtualObject *MushSkinPixelSourceNoise::AutoVirtualFactory(void)
{
    return new MushSkinPixelSourceNoise;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushSkinPixelSourceNoise", MushSkinPixelSourceNoise::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushSkinPixelSourceNoise::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "xSize=" << m_xSize << ", ";
    ioOut << "ySize=" << m_ySize << ", ";
    ioOut << "sourceName=" << m_sourceName;
    ioOut << "]";
}
bool
MushSkinPixelSourceNoise::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "xSize")
    {
        ioIn >> m_xSize;
    }
    else if (inTagStr == "ySize")
    {
        ioIn >> m_ySize;
    }
    else if (inTagStr == "sourceName")
    {
        ioIn >> m_sourceName;
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushSkinPixelSourceNoise::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("xSize");
    ioOut << m_xSize;
    ioOut.TagSet("ySize");
    ioOut << m_ySize;
    ioOut.TagSet("sourceName");
    ioOut << m_sourceName;
}
//%outOfLineFunctions } /xdfP66fMW3hhQpZeaXGrA
