//%Header {
/*****************************************************************************
 *
 * File: src/MushSkin/MushSkinResolverPixelSource.cpp
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
//%Header } JKEnx9FBo7lsZ4SNGVymjg
/*
 * $Id: MushSkinResolverPixelSource.cpp,v 1.2 2006/05/01 17:39:01 southa Exp $
 * $Log: MushSkinResolverPixelSource.cpp,v $
 * Revision 1.2  2006/05/01 17:39:01  southa
 * Texture generation
 *
 * Revision 1.1  2006/04/11 23:30:11  southa
 * Created MushRuby from ruby-1.8.4
 *
 */

#include "MushSkinResolverPixelSource.h"

#include "MushSkinPixelSourceNoise.h"

using namespace Mushware;
using namespace std;

void
MushSkinResolverPixelSource::Resolve(const std::string& inSrcName)
{
    MushcoreRegExp regExp;
    MushcoreRegExp::tMatches matches;
    regExp.SearchPatternSet("\\btype=noise\\b");
    if (regExp.Search(matches, inSrcName))
    {
        MUSHCOREASSERT(matches.size() == 0);
        regExp.SearchPatternSet("\\bname=\"([^\"]*)\"");
        if (!regExp.Search(matches, inSrcName))
        {
            throw MushcoreSyntaxFail("No 'name=\"<name>\"' entry for noise texture '"+inSrcName+";");
        }
        MUSHCOREASSERT(matches.size() == 1);
        std::string nameStr = matches[0];
        
        regExp.SearchPatternSet("\\bsize=\"([^\"]*)\"");
        
        if (!regExp.Search(matches, inSrcName))
        {
            throw MushcoreSyntaxFail("No 'size=\"(<xsize>,<ysize>)\"' entry for noise texture '"+inSrcName+";");
        }
        MUSHCOREASSERT(matches.size() == 1);
        std::istringstream sizeStream(matches[0]);
        MushcoreXMLIStream xmlSizeStream(sizeStream);
        
        std::vector<U32> sizeVec;
        xmlSizeStream >> sizeVec;
        if (sizeVec.size() < 2)
        {
            throw MushcoreSyntaxFail("Malformed 'size=\"(<xsize>,<ysize>)\"' entry for noise texture '"+inSrcName+";");
        }
        
        std::string paletteName = "";
        regExp.SearchPatternSet("\\bpalette=\"([^\"]*)\"");
        if (regExp.Search(matches, inSrcName))
        {
            paletteName = matches[0];
        }
        
        t2Val paletteStart = t2Val(0, 0);
        regExp.SearchPatternSet("\\bpalettestart=\"([^\"]*)\"");
        
        if (regExp.Search(matches, inSrcName))
        {
            MUSHCOREASSERT(matches.size() == 1);
            std::istringstream vecStream(matches[0]);
            MushcoreXMLIStream xmlVecStream(vecStream);
                        
            xmlVecStream >> paletteStart;
        }
        
        t2Val paletteVector = t2Val(1, 0);
        regExp.SearchPatternSet("\\bpalettevector=\"([^\"]*)\"");
        
        if (regExp.Search(matches, inSrcName))
        {
            MUSHCOREASSERT(matches.size() == 1);
            std::istringstream vecStream(matches[0]);
            MushcoreXMLIStream xmlVecStream(vecStream);
            
            xmlVecStream >> paletteVector;
        }
        
        std::auto_ptr<MushSkinPixelSourceNoise> aResolver(new MushSkinPixelSourceNoise);
        aResolver->StringParameterSet(MushGLPixelSource::kParamSourceName, nameStr);
        aResolver->ValueParameterSet(MushGLPixelSource::kParamXSize, sizeVec[0]);
        aResolver->ValueParameterSet(MushGLPixelSource::kParamYSize, sizeVec[1]);
        aResolver->StringParameterSet(MushGLPixelSource::kParamPaletteName, paletteName);
        aResolver->ValueParameterSet(MushGLPixelSource::kParamPaletteStartX, paletteStart.X());
        aResolver->ValueParameterSet(MushGLPixelSource::kParamPaletteStartY, paletteStart.Y());
        aResolver->ValueParameterSet(MushGLPixelSource::kParamPaletteVectorX, paletteVector.X());
        aResolver->ValueParameterSet(MushGLPixelSource::kParamPaletteVectorY, paletteVector.Y());

        MushcoreData<MushGLPixelSource>::Sgl().Give(inSrcName, aResolver.release());
    }
    else
    {
        MushGLResolverPixelSource::Resolve(inSrcName);  
    }
}

// Install this object as the pixel source resolver singleton
namespace
{
    void Install(void)
    {
        MushGLResolverPixelSource::SingletonMutate(new MushSkinResolverPixelSource);
    }
    MushcoreInstaller Installer(Install);
} // end anonymous namespace

//%outOfLineFunctions {

const char *MushSkinResolverPixelSource::AutoName(void) const
{
    return "MushSkinResolverPixelSource";
}

MushcoreVirtualObject *MushSkinResolverPixelSource::AutoClone(void) const
{
    throw MushcoreRequestFail("Cannot clone 'MushSkinResolverPixelSource'");;
}

MushcoreVirtualObject *MushSkinResolverPixelSource::AutoCreate(void) const
{
    return new MushSkinResolverPixelSource;
}

MushcoreVirtualObject *MushSkinResolverPixelSource::AutoVirtualFactory(void)
{
    return new MushSkinResolverPixelSource;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushSkinResolverPixelSource", MushSkinResolverPixelSource::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushSkinResolverPixelSource::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "]";
}
bool
MushSkinResolverPixelSource::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
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
MushSkinResolverPixelSource::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
}
//%outOfLineFunctions } Ys+nwOSrKn4iRSObNEUX7g
