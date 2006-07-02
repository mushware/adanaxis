//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLFont.cpp
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
//%Header } Zq+IM0uOYEygMymunhBN6w
/*
 * $Id: MushGLFont.cpp,v 1.1 2006/04/21 00:10:43 southa Exp $
 * $Log: MushGLFont.cpp,v $
 * Revision 1.1  2006/04/21 00:10:43  southa
 * MushGLFont ruby module
 *
 */

#include "MushGLFont.h"

#include "mushMushRuby.h"

using namespace Mushware;
using namespace std;

MUSHCORE_DATA_INSTANCE(MushGLFont);
//%outOfLineFunctions {

const char *MushGLFont::AutoName(void) const
{
    return "MushGLFont";
}

MushcoreVirtualObject *MushGLFont::AutoClone(void) const
{
    return new MushGLFont(*this);
}

MushcoreVirtualObject *MushGLFont::AutoCreate(void) const
{
    return new MushGLFont;
}

MushcoreVirtualObject *MushGLFont::AutoVirtualFactory(void)
{
    return new MushGLFont;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGLFont", MushGLFont::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGLFont::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "textureRef=" << m_textureRef << ", ";
    ioOut << "divide=" << m_divide << ", ";
    ioOut << "extent=" << m_extent;
    ioOut << "]";
}
bool
MushGLFont::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "textureRef")
    {
        ioIn >> m_textureRef;
    }
    else if (inTagStr == "divide")
    {
        ioIn >> m_divide;
    }
    else if (inTagStr == "extent")
    {
        ioIn >> m_extent;
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushGLFont::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("textureRef");
    ioOut << m_textureRef;
    ioOut.TagSet("divide");
    ioOut << m_divide;
    ioOut.TagSet("extent");
    ioOut << m_extent;
}
//%outOfLineFunctions } yxsjyVD4hkOYSzd3O476iw
