//%Header {
/*****************************************************************************
 *
 * File: src/GL/GLFontRef.cpp
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
//%Header } Orfh3AmXjTsgV214s0UWmg
/*
 * $Id: GLFontRef.cpp,v 1.18 2006/06/01 15:38:50 southa Exp $
 * $Log: GLFontRef.cpp,v $
 * Revision 1.18  2006/06/01 15:38:50  southa
 * DrawArray verification and fixes
 *
 * Revision 1.17  2005/07/02 00:42:37  southa
 * Conditioning tweaks
 *
 * Revision 1.16  2005/06/30 12:34:58  southa
 * Mesh and source conditioner work
 *
 * Revision 1.15  2005/06/20 14:30:33  southa
 * Adanaxis work
 *
 * Revision 1.14  2005/06/16 17:25:37  southa
 * Client/server work
 *
 * Revision 1.13  2005/05/19 13:01:59  southa
 * Mac release work
 *
 * Revision 1.12  2005/03/25 19:13:48  southa
 * GameDialogue work
 *
 * Revision 1.11  2004/01/02 21:13:05  southa
 * Source conditioning
 *
 * Revision 1.10  2003/09/17 19:40:29  southa
 * Source conditioning upgrades
 *
 * Revision 1.9  2003/08/21 23:08:21  southa
 * Fixed file headers
 *
 * Revision 1.8  2003/01/20 10:45:23  southa
 * Singleton tidying
 *
 * Revision 1.7  2003/01/13 14:31:54  southa
 * Build frameworks for Mac OS X
 *
 * Revision 1.6  2003/01/12 17:32:50  southa
 * Mushcore work
 *
 * Revision 1.5  2002/12/29 20:59:52  southa
 * More build fixes
 *
 * Revision 1.4  2002/12/20 13:17:35  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.3  2002/10/22 20:42:00  southa
 * Source conditioning
 *
 * Revision 1.2  2002/08/27 08:56:19  southa
 * Source conditioning
 *
 * Revision 1.1  2002/08/08 13:39:09  southa
 * Text rendering
 *
 */

#include "GLFontRef.h"
#include "GLData.h"

#include "GLSTL.h"

using namespace Mushware;
using namespace std;

GLFont *
GLFontRef::FontGet(void) const
{
    if (m_fontPtr == NULL)
    {
        GetReference();
    }
    return m_fontPtr;
}

void
GLFontRef::GetReference(void) const
{
    m_fontPtr=GLData::Sgl().FontGet(m_name);
    if (m_fontPtr == NULL)
    {
        throw(MushcoreReferenceFail("Attempt to access non-existent font '"+m_name+"'"));
    }
}

bool
GLFontRef::Exists(void) const
{
    return (m_fontPtr != NULL || GLData::Sgl().FontGet(m_name) != NULL);
}
//%outOfLineFunctions {

const char *GLFontRef::AutoName(void) const
{
    return "GLFontRef";
}

MushcoreVirtualObject *GLFontRef::AutoClone(void) const
{
    return new GLFontRef(*this);
}

MushcoreVirtualObject *GLFontRef::AutoCreate(void) const
{
    return new GLFontRef;
}

MushcoreVirtualObject *GLFontRef::AutoVirtualFactory(void)
{
    return new GLFontRef;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("GLFontRef", GLFontRef::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
bool
GLFontRef::AutoEquals(const GLFontRef& inObj) const
{
    return 1
        && (m_name == inObj.m_name)
        && (m_size == inObj.m_size)
    ;
}
void
GLFontRef::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "name=" << m_name << ", ";
    ioOut << "size=" << m_size << ", ";
    ioOut << "]";
}
bool
GLFontRef::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
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
    else if (inTagStr == "size")
    {
        ioIn >> m_size;
    }
    else 
    {
        return false;
    }
    return true;
}
void
GLFontRef::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("name");
    ioOut << m_name;
    ioOut.TagSet("size");
    ioOut << m_size;
}
//%outOfLineFunctions } rx05BbB94qVLsgjoytUSDA
