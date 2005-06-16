//%Header {
/*****************************************************************************
 *
 * File: src/GL/GLFontRef.cpp
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
//%Header } 03m51tzRRZ4J/ClESPY1sA
/*
 * $Id: GLFontRef.cpp,v 1.13 2005/05/19 13:01:59 southa Exp $
 * $Log: GLFontRef.cpp,v $
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

const char *GLFontRef::AutoNameGet(void) const
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
    ioOut << "size=" << m_size;
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
//%outOfLineFunctions } jy3kiciwKlF+m84uTz9w7A
