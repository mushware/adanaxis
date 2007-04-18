//%Header {
/*****************************************************************************
 *
 * File: src/GL/GLModeDef.cpp
 *
 * Author: Andy Southgate 2002-2007
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
//%Header } CPG6+kh7OORl3O4TDsbUNQ
/*
 * $Id: GLModeDef.cpp,v 1.13 2006/11/25 21:26:31 southa Exp $
 * $Log: GLModeDef.cpp,v $
 * Revision 1.13  2006/11/25 21:26:31  southa
 * Display mode definitions
 *
 */

#include "GLModeDef.h"

#include "GLSTL.h"

using namespace Mushware;
using namespace std;

GLModeDef::GLModeDef() :
    m_width(640),
    m_height(480),
    m_fullScreen(false)
{
}
//%outOfLineFunctions {

const char *GLModeDef::AutoName(void) const
{
    return "GLModeDef";
}

MushcoreVirtualObject *GLModeDef::AutoClone(void) const
{
    return new GLModeDef(*this);
}

MushcoreVirtualObject *GLModeDef::AutoCreate(void) const
{
    return new GLModeDef;
}

MushcoreVirtualObject *GLModeDef::AutoVirtualFactory(void)
{
    return new GLModeDef;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("GLModeDef", GLModeDef::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
bool
GLModeDef::AutoEquals(const GLModeDef& inObj) const
{
    return 1
        && (m_width == inObj.m_width)
        && (m_height == inObj.m_height)
        && (m_fullScreen == inObj.m_fullScreen)
    ;
}
void
GLModeDef::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "width=" << m_width << ", ";
    ioOut << "height=" << m_height << ", ";
    ioOut << "fullScreen=" << m_fullScreen;
    ioOut << "]";
}
bool
GLModeDef::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "width")
    {
        ioIn >> m_width;
    }
    else if (inTagStr == "height")
    {
        ioIn >> m_height;
    }
    else if (inTagStr == "fullScreen")
    {
        ioIn >> m_fullScreen;
    }
    else 
    {
        return false;
    }
    return true;
}
void
GLModeDef::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("width");
    ioOut << m_width;
    ioOut.TagSet("height");
    ioOut << m_height;
    ioOut.TagSet("fullScreen");
    ioOut << m_fullScreen;
}
//%outOfLineFunctions } q3E3Reip9yaMraqy0WNwrQ
