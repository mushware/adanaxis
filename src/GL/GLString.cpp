//%Header {
/*****************************************************************************
 *
 * File: src/GL/GLString.cpp
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
//%Header } 1yTrE8HG49Uue+dQpQ85DA
/*
 * $Id: GLString.cpp,v 1.17 2006/06/01 15:38:53 southa Exp $
 * $Log: GLString.cpp,v $
 * Revision 1.17  2006/06/01 15:38:53  southa
 * DrawArray verification and fixes
 *
 * Revision 1.16  2005/07/02 00:42:37  southa
 * Conditioning tweaks
 *
 * Revision 1.15  2005/06/20 14:30:33  southa
 * Adanaxis work
 *
 * Revision 1.14  2005/06/16 17:25:37  southa
 * Client/server work
 *
 * Revision 1.13  2005/05/19 13:02:00  southa
 * Mac release work
 *
 * Revision 1.12  2005/03/25 19:13:48  southa
 * GameDialogue work
 *
 * Revision 1.11  2004/01/02 21:13:05  southa
 * Source conditioning
 *
 * Revision 1.10  2003/10/04 15:32:08  southa
 * Module split
 *
 * Revision 1.9  2003/09/17 19:40:30  southa
 * Source conditioning upgrades
 *
 * Revision 1.8  2003/08/21 23:08:29  southa
 * Fixed file headers
 *
 * Revision 1.7  2003/01/13 14:31:55  southa
 * Build frameworks for Mac OS X
 *
 * Revision 1.6  2002/12/29 20:59:53  southa
 * More build fixes
 *
 * Revision 1.5  2002/12/20 13:17:35  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.4  2002/10/22 20:42:01  southa
 * Source conditioning
 *
 * Revision 1.3  2002/08/27 08:56:20  southa
 * Source conditioning
 *
 * Revision 1.2  2002/08/09 17:09:02  southa
 * InfernalDialogue added
 *
 * Revision 1.1  2002/08/08 13:39:09  southa
 * Text rendering
 *
 */

#include "GLString.h"
#include "GLFont.h"
#include "GLUtils.h"

#include "GLSTL.h"

using namespace Mushware;
using namespace std;

GLString::GLString(const string& inValue, const GLFontRef& inFont, tVal inAlign):
    m_fontRef(inFont),
    m_value(inValue),
    m_alignment(inAlign)
{
}

void
GLString::Render(void) const
{
    tVal size=m_fontRef.SizeGet();
    GLUtils::PushMatrix();
    GLUtils::Scale(size, size, 1);
    m_fontRef.FontGet()->RenderString(m_value, m_alignment);
    GLUtils::PopMatrix();
}
//%outOfLineFunctions {

const char *GLString::AutoName(void) const
{
    return "GLString";
}

MushcoreVirtualObject *GLString::AutoClone(void) const
{
    return new GLString(*this);
}

MushcoreVirtualObject *GLString::AutoCreate(void) const
{
    return new GLString;
}

MushcoreVirtualObject *GLString::AutoVirtualFactory(void)
{
    return new GLString;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("GLString", GLString::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
bool
GLString::AutoEquals(const GLString& inObj) const
{
    return 1
        && (m_fontRef == inObj.m_fontRef)
        && (m_value == inObj.m_value)
        && (m_alignment == inObj.m_alignment)
    ;
}
void
GLString::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "fontRef=" << m_fontRef << ", ";
    ioOut << "value=" << m_value << ", ";
    ioOut << "alignment=" << m_alignment;
    ioOut << "]";
}
bool
GLString::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "fontRef")
    {
        ioIn >> m_fontRef;
    }
    else if (inTagStr == "value")
    {
        ioIn >> m_value;
    }
    else if (inTagStr == "alignment")
    {
        ioIn >> m_alignment;
    }
    else 
    {
        return false;
    }
    return true;
}
void
GLString::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("fontRef");
    ioOut << m_fontRef;
    ioOut.TagSet("value");
    ioOut << m_value;
    ioOut.TagSet("alignment");
    ioOut << m_alignment;
}
//%outOfLineFunctions } GAGZ4tgQtD9cwGKJ9X+Kbg
