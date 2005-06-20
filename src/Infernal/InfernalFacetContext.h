//%includeGuardStart {
#ifndef INFERNALFACETCONTEXT_H
#define INFERNALFACETCONTEXT_H
//%includeGuardStart } ekb3A6WkyyAMsRFKH4jwFw
//%Header {
/*****************************************************************************
 *
 * File: src/Infernal/InfernalFacetContext.h
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
//%Header } CDbgvA4tSMWmMJpHdOog6g
/*
 * $Id: InfernalFacetContext.h,v 1.4 2005/05/19 13:02:04 southa Exp $
 * $Log: InfernalFacetContext.h,v $
 * Revision 1.4  2005/05/19 13:02:04  southa
 * Mac release work
 *
 * Revision 1.3  2005/02/10 12:34:01  southa
 * Template fixes
 *
 * Revision 1.2  2005/02/03 21:02:54  southa
 * Build fixes
 *
 * Revision 1.1  2004/01/10 20:29:34  southa
 * Form and rendering work
 *
 */

#include "InfernalStandard.h"

#include "mushGL.h"

//:generate virtual standard ostream xml1
class InfernalFacetContext : public MushcoreVirtualObject
{
public:
    InfernalFacetContext() : m_contextValid(false) {}
    virtual ~InfernalFacetContext() {}
    
    void RenderTypeImport(const std::string& inName);
    void VerticesImport(const std::vector<Mushware::t3Val>& inVertices);
    
private:
    GLTextureRef m_textureRef; //:readwrite
    Mushware::U32 m_listContextNum; //:readwrite
    GLuint m_listName; //:readwrite
    GLenum m_renderType; //:readwrite
    Mushware::U32 m_arraySize; //:readwrite
    std::vector<GLfloat> m_vertices; //:read
    std::vector<GLfloat> m_texCoords; //:read
    std::vector<GLfloat> m_normals; //:read
    bool m_contextValid; //:readwrite
//%classPrototypes {
public:
    const GLTextureRef& TextureRef(void) const { return m_textureRef; }
    void TextureRefSet(const GLTextureRef& inValue) { m_textureRef=inValue; }
    const Mushware::U32& ListContextNum(void) const { return m_listContextNum; }
    void ListContextNumSet(const Mushware::U32& inValue) { m_listContextNum=inValue; }
    const GLuint& ListName(void) const { return m_listName; }
    void ListNameSet(const GLuint& inValue) { m_listName=inValue; }
    const GLenum& RenderType(void) const { return m_renderType; }
    void RenderTypeSet(const GLenum& inValue) { m_renderType=inValue; }
    const Mushware::U32& ArraySize(void) const { return m_arraySize; }
    void ArraySizeSet(const Mushware::U32& inValue) { m_arraySize=inValue; }
    const std::vector<GLfloat>& Vertices(void) const { return m_vertices; }
    const std::vector<GLfloat>& TexCoords(void) const { return m_texCoords; }
    const std::vector<GLfloat>& Normals(void) const { return m_normals; }
    const bool& ContextValid(void) const { return m_contextValid; }
    void ContextValidSet(const bool& inValue) { m_contextValid=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } 8irSwWHgKc2fMeEv/JUYVw
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const InfernalFacetContext& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } SJBGo1BQ3Axxky8g3GUxYQ
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
