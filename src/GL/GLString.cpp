//%Header {
/*****************************************************************************
 *
 * File: src/GL/GLString.cpp
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
//%Header } T2OnH6NbDcsuezTIwyt4FA
/*
 * $Id: GLString.cpp,v 1.14 2005/06/16 17:25:37 southa Exp $
 * $Log: GLString.cpp,v $
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
//%outOfLineFunctions } pXMsPnA56SnMYhN8Qt1WiQ
