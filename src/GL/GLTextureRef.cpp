//%Header {
/*****************************************************************************
 *
 * File: src/GL/GLTextureRef.cpp
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
//%Header } asw/Xtq8JFLwPuHWwCzSHA
/*
 * $Id: GLTextureRef.cpp,v 1.20 2005/05/19 13:02:00 southa Exp $
 * $Log: GLTextureRef.cpp,v $
 * Revision 1.20  2005/05/19 13:02:00  southa
 * Mac release work
 *
 * Revision 1.19  2005/02/10 12:33:56  southa
 * Template fixes
 *
 * Revision 1.18  2004/01/10 20:29:34  southa
 * Form and rendering work
 *
 * Revision 1.17  2004/01/02 21:13:06  southa
 * Source conditioning
 *
 * Revision 1.16  2003/09/17 19:40:30  southa
 * Source conditioning upgrades
 *
 * Revision 1.15  2003/08/21 23:08:31  southa
 * Fixed file headers
 *
 * Revision 1.14  2003/01/20 10:45:24  southa
 * Singleton tidying
 *
 * Revision 1.13  2003/01/13 14:31:55  southa
 * Build frameworks for Mac OS X
 *
 * Revision 1.12  2003/01/12 17:32:51  southa
 * Mushcore work
 *
 * Revision 1.11  2002/12/29 20:59:53  southa
 * More build fixes
 *
 * Revision 1.10  2002/12/20 13:17:36  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.9  2002/10/22 20:42:01  southa
 * Source conditioning
 *
 * Revision 1.8  2002/10/12 15:25:09  southa
 * Facet renderer
 *
 * Revision 1.7  2002/08/27 08:56:21  southa
 * Source conditioning
 *
 * Revision 1.6  2002/08/07 13:36:47  southa
 * Conditioned source
 *
 * Revision 1.5  2002/07/06 18:04:18  southa
 * More designer work
 *
 * Revision 1.4  2002/06/27 12:36:05  southa
 * Build process fixes
 *
 * Revision 1.3  2002/06/04 20:29:43  southa
 * Pickles for game traits and graphics.  Removed mac libraries from archive.
 *
 * Revision 1.2  2002/06/04 17:02:24  southa
 * More work
 *
 * Revision 1.1  2002/05/28 16:37:39  southa
 * Texture references and decomposer
 *
 */

#include "GLTextureRef.h"
#include "GLData.h"
#include "GLTexture.h"

#include "GLSTL.h"

using namespace Mushware;
using namespace std;

void
GLTextureRef::TextureFetch(void) const
{
    m_texPtr=GLData::Sgl().TextureFind(m_name);
    if (m_texPtr == NULL)
    {
        throw(MushcoreLogicFail("Attempt to access non-existent texture '"+m_name+"'"));
    }
}

bool
GLTextureRef::Exists(void) const
{
    return (m_texPtr != NULL || GLData::Sgl().TextureFind(m_name) != NULL);
}

void
GLTextureRef::BindingNameFetch(void) const
{
    m_bindingName=TextureGet()->BindingNameGet();
}
//%outOfLineFunctions {

const char *GLTextureRef::AutoNameGet(void) const
{
    return "GLTextureRef";
}

MushcoreVirtualObject *GLTextureRef::AutoClone(void) const
{
    return new GLTextureRef(*this);
}

MushcoreVirtualObject *GLTextureRef::AutoCreate(void) const
{
    return new GLTextureRef;
}

MushcoreVirtualObject *GLTextureRef::AutoVirtualFactory(void)
{
    return new GLTextureRef;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("GLTextureRef", GLTextureRef::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
GLTextureRef::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "name=" << m_name;
    ioOut << "]";
}
bool
GLTextureRef::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
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
GLTextureRef::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("name");
    ioOut << m_name;
}
//%outOfLineFunctions } uqrTkjCXLubWyvnOcr1SFw
