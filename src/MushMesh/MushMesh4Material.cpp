//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMesh4Material.cpp
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
//%Header } rKxqFRDUQ+hPECsMm6L1IA
/*
 * $Id$
 * $Log$
 */

#include "MushMesh4Material.h"

MUSHCORE_DATA_INSTANCE(MushMesh4Material);

//%outOfLineFunctions {

const char *MushMesh4Material::AutoName(void) const
{
    return "MushMesh4Material";
}

MushcoreVirtualObject *MushMesh4Material::AutoClone(void) const
{
    return new MushMesh4Material(*this);
}

MushcoreVirtualObject *MushMesh4Material::AutoCreate(void) const
{
    return new MushMesh4Material;
}

MushcoreVirtualObject *MushMesh4Material::AutoVirtualFactory(void)
{
    return new MushMesh4Material;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushMesh4Material", MushMesh4Material::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushMesh4Material::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "name=" << m_name;
    ioOut << "]";
}
bool
MushMesh4Material::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
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
    else 
    {
        return false;
    }
    return true;
}
void
MushMesh4Material::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("name");
    ioOut << m_name;
}
//%outOfLineFunctions } qjtGfw8Jp+t7x8ZpyLUBOg
