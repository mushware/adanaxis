//%includeGuardStart {
#ifndef INFERNALFACETCONTEXT_H
#define INFERNALFACETCONTEXT_H
//%includeGuardStart } ekb3A6WkyyAMsRFKH4jwFw
//%Header {
/*****************************************************************************
 *
 * File: src/Infernal/InfernalFacetContext.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } UaBPyJihXb0nBhSdiIa4/Q
/*
 * $Id: InfernalFacetContext.h,v 1.1 2004/01/10 20:29:34 southa Exp $
 * $Log: InfernalFacetContext.h,v $
 * Revision 1.1  2004/01/10 20:29:34  southa
 * Form and rendering work
 *
 */

#include "InfernalStandard.h"

#include "mushGL.h"

//:generate standard ostream xml1
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
    virtual const char *AutoNameGet(void) const;
    virtual InfernalFacetContext *AutoClone(void) const;
    virtual InfernalFacetContext *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } NgdAtPbDceN3DvjhduPnqw
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
