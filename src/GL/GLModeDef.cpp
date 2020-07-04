//%Header {
/*****************************************************************************
 *
 * File: src/GL/GLModeDef.cpp
 *
 * Copyright: Andy Southgate 2002-2007, 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/
//%Header } BqcLFfAELdJLtAZvfS6vTA
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
