//%includeGuardStart {
#ifndef GLTEXTUREREF_H
#define GLTEXTUREREF_H
//%includeGuardStart } 7kcCzGNBUbRNq9osHA8Qxw
//%Header {
/*****************************************************************************
 *
 * File: src/GL/GLTextureRef.h
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
//%Header } Qr/IPvbER9zkoS6bL9PcVw
/*
 * $Id: GLTextureRef.h,v 1.23 2006/06/01 15:38:54 southa Exp $
 * $Log: GLTextureRef.h,v $
 * Revision 1.23  2006/06/01 15:38:54  southa
 * DrawArray verification and fixes
 *
 * Revision 1.22  2005/06/30 14:26:36  southa
 * Adanaxis work
 *
 * Revision 1.21  2005/06/20 14:30:34  southa
 * Adanaxis work
 *
 * Revision 1.20  2005/05/19 13:02:00  southa
 * Mac release work
 *
 * Revision 1.19  2005/02/10 12:33:57  southa
 * Template fixes
 *
 * Revision 1.18  2004/01/10 20:29:34  southa
 * Form and rendering work
 *
 * Revision 1.17  2004/01/06 20:46:49  southa
 * Build fixes
 *
 * Revision 1.16  2004/01/02 21:13:06  southa
 * Source conditioning
 *
 * Revision 1.15  2003/09/17 19:40:30  southa
 * Source conditioning upgrades
 *
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
#include "mushMushcore.h"

class GLTexture;

//:generate virtual standard ostream xml1
class GLTextureRef : public MushcoreVirtualObject
{
public:
    GLTextureRef(): m_texPtr(NULL), m_bindingNameContext(0) {}
    virtual ~GLTextureRef() {}
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
    mutable GLTexture *m_texPtr; //:ignore
    mutable GLuint m_bindingName; //:ignore
    mutable Mushware::U32 m_bindingNameContext; //:ignore
//%classPrototypes {
public:
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } 1oBgFruy5qHAaudtV+Hcmg
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
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const GLTextureRef& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } 7Tcn23BbQg1X7vdx6W+7ew
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
