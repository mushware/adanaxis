//%includeGuardStart {
#ifndef GLTEXTUREREF_H
#define GLTEXTUREREF_H
//%includeGuardStart } 7kcCzGNBUbRNq9osHA8Qxw
//%Header {
/*****************************************************************************
 *
 * File: src/GL/GLTextureRef.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } OfivSYbFAgfjf7usj+dyLg
/*
 * $Id: GLTextureRef.h,v 1.14 2003/08/21 23:08:31 southa Exp $
 * $Log: GLTextureRef.h,v $
 * Revision 1.14  2003/08/21 23:08:31  southa
 * Fixed file headers
 *
 * Revision 1.13  2003/01/11 13:03:11  southa
 * Use Mushcore header
 *
 * Revision 1.12  2002/12/29 20:30:53  southa
 * Work for gcc 3.1 build
 *
 * Revision 1.11  2002/12/20 13:17:36  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.10  2002/10/22 20:42:01  southa
 * Source conditioning
 *
 * Revision 1.9  2002/10/15 14:02:29  southa
 * Mode changes
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

#include "GLStandard.h"
#include "GLUtils.h"
#include "Mushcore.h"

class GLTexture;

class GLTextureRef
{
public:
    GLTextureRef(): m_texPtr(NULL), m_bindingNameContext(0) {}
    GLTextureRef(const std::string& inName): m_name(inName), m_texPtr(NULL) {}
    void NameSet(const std::string& inName) {m_name=inName;m_texPtr=NULL;}
    const std::string& NameGet(void) const {return m_name;}
    GLTexture *TextureGet(void) const;
    GLuint BindingNameGet(void) const;
    bool Exists(void) const;
    
private:
    void TextureFetch(void) const;
    void BindingNameFetch(void) const;

    std::string m_name;
    mutable GLTexture *m_texPtr;
    mutable GLuint m_bindingName;
    mutable Mushware::U32 m_bindingNameContext;
};

inline GLTexture *
GLTextureRef::TextureGet(void) const
{
    if (m_texPtr != NULL) return m_texPtr;
    TextureFetch();
    return m_texPtr;
}

inline GLuint
GLTextureRef::BindingNameGet(void) const
{
    // if (m_bindingNameContext == GLUtils::TextureContextGet()) return m_bindingName;
    BindingNameFetch();
    m_bindingNameContext = GLUtils::TextureContextGet();
    return m_bindingName;
}
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
