//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLMaterial.cpp
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
//%Header } 89CRHyqzGdmyRnU8sWf03w
/*
 * $Id: MushGLMaterial.cpp,v 1.1 2005/09/03 17:05:36 southa Exp $
 * $Log: MushGLMaterial.cpp,v $
 * Revision 1.1  2005/09/03 17:05:36  southa
 * Material work
 *
 */

#include "MushGLMaterial.h"

//%outOfLineFunctions {

const char *MushGLMaterial::AutoName(void) const
{
    return "MushGLMaterial";
}

MushcoreVirtualObject *MushGLMaterial::AutoClone(void) const
{
    return new MushGLMaterial(*this);
}

MushcoreVirtualObject *MushGLMaterial::AutoCreate(void) const
{
    return new MushGLMaterial;
}

MushcoreVirtualObject *MushGLMaterial::AutoVirtualFactory(void)
{
    return new MushGLMaterial;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGLMaterial", MushGLMaterial::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGLMaterial::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "textureHandles=" << m_textureHandles;
    ioOut << "]";
}
bool
MushGLMaterial::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "textureHandles")
    {
        ioIn >> m_textureHandles;
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushGLMaterial::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("textureHandles");
    ioOut << m_textureHandles;
}
//%outOfLineFunctions } iZG9tKYk5DXBuXrkz3Qydg
