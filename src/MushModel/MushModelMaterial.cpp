//%Header {
/*****************************************************************************
 *
 * File: src/MushModel/MushModelMaterial.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } kMzPo0tNkdWRsyion9xovw
/*
 * $Id$
 * $Log$
 */

#include "MushModelMaterial.h"

MUSHCORE_DATA_INSTANCE(MushModelMaterial);

//%outOfLineFunctions {
const char *MushModelMaterial::AutoNameGet(void) const
{
    return "MushModelMaterial";
}
MushModelMaterial *MushModelMaterial::AutoClone(void) const
{
    return new MushModelMaterial(*this);
}
MushModelMaterial *MushModelMaterial::AutoCreate(void) const
{
    return new MushModelMaterial;
}
MushcoreVirtualObject *MushModelMaterial::AutoVirtualFactory(void)
{
    return new MushModelMaterial;
}
namespace
{
void Install(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushModelMaterial", MushModelMaterial::AutoVirtualFactory);
}
MushcoreInstaller Installer(Install);
} // end anonymous namespace
void
MushModelMaterial::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "textureName=" << m_textureName;
    ioOut << "]";
}
bool
MushModelMaterial::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        ioIn >> *this;
    }
    else if (inTagStr == "textureName")
    {
        ioIn >> m_textureName;
    }
    else
    {
        return false;
    }
    return true;
}
void
MushModelMaterial::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("textureName");
    ioOut << m_textureName;
}
//%outOfLineFunctions } bn2gK2IR9NCBY+SXICiLOQ
