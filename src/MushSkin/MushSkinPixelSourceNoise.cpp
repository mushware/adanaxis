//%Header {
/*****************************************************************************
 *
 * File: src/MushSkin/MushSkinPixelSourceNoise.cpp
 *
 * Copyright: Andy Southgate 2005
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
//%Header } TdUdiTjja8uY1Ei6cDI06Q
/*
 * $Id$
 * $Log$
 */

#include "MushSkinPixelSourceNoise.h"

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
    else 
    {
        return false;
    }
    return true;
}
void
MushSkinPixelSourceNoise::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
}
//%outOfLineFunctions } 7+fZOCxEk9CU2K94uDVA7A
