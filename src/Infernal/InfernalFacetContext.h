//%includeGuardStart {
#ifndef INFERNALFACETCONTEXT_H
#define INFERNALFACETCONTEXT_H
//%includeGuardStart } ekb3A6WkyyAMsRFKH4jwFw
//%Header {
/*****************************************************************************
 *
 * File: src/Infernal/InfernalFacetContext.h
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
//%Header } vpQbmMhRqB48EVFLblY+lQ
/*
 * $Id: InfernalFacetContext.h,v 1.6 2006/06/01 15:39:02 southa Exp $
 * $Log: InfernalFacetContext.h,v $
 * Revision 1.6  2006/06/01 15:39:02  southa
 * DrawArray verification and fixes
 *
 * Revision 1.5  2005/06/20 14:30:35  southa
 * Adanaxis work
 *
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
