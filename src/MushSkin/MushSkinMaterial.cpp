//%Header {
/*****************************************************************************
 *
 * File: src/MushSkin/MushSkinMaterial.cpp
 *
 * Copyright: Andy Southgate 2005-2006
 *
 * This file may be used and distributed under the terms of the Mushware
 * software licence version 1.1, under the terms for 'Proprietary original
 * source files'.  If not supplied with this software, a copy of the licence
 * can be obtained from Mushware Limited via http://www.mushware.com/.
 * One of your options under that licence is to use and distribute this file
 * under the terms of the GNU General Public Licence version 2.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 2GW9ZU/jNVST8yYMj5AUyg
/*
 * $Id: MushSkinMaterial.cpp,v 1.1 2006/06/19 15:57:20 southa Exp $
 * $Log: MushSkinMaterial.cpp,v $
 * Revision 1.1  2006/06/19 15:57:20  southa
 * Materials
 *
 */

#include "MushSkinMaterial.h"


//%outOfLineFunctions {

const char *MushSkinMaterial::AutoName(void) const
{
    return "MushSkinMaterial";
}

MushcoreVirtualObject *MushSkinMaterial::AutoClone(void) const
{
    return new MushSkinMaterial(*this);
}

MushcoreVirtualObject *MushSkinMaterial::AutoCreate(void) const
{
    return new MushSkinMaterial;
}

MushcoreVirtualObject *MushSkinMaterial::AutoVirtualFactory(void)
{
    return new MushSkinMaterial;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushSkinMaterial", MushSkinMaterial::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushSkinMaterial::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushMesh4Material::AutoPrint(ioOut);
    ioOut << "texRef=" << m_texRef;
    ioOut << "]";
}
bool
MushSkinMaterial::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "texRef")
    {
        ioIn >> m_texRef;
    }
    else if (MushMesh4Material::AutoXMLDataProcess(ioIn, inTagStr))
    {
        // Tag consumed by base class
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushSkinMaterial::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushMesh4Material::AutoXMLPrint(ioOut);
    ioOut.TagSet("texRef");
    ioOut << m_texRef;
}
//%outOfLineFunctions } +trxpRQ4knQ4AytV6w0ktQ
