/*****************************************************************************
 *
 * (Mushware file header version 1.3)
 *
 * Copyrighted work by Andy Southgate 2003
 *
 * This file may be redistributed and/or modified under the terms of the
 * Mushware licence which you should have received with this file.  For
 * information, please contact the author via http://www.mushware.com/.
 *
 ****************************************************************************/

/*
 * $Id: GLTextureRef.cpp,v 1.14 2003/01/20 10:45:24 southa Exp $
 * $Log: GLTextureRef.cpp,v $
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
