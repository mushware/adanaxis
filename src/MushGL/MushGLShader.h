//%includeGuardStart {
#ifndef MUSHGLSHADER_H
#define MUSHGLSHADER_H
//%includeGuardStart } cGhxNJ2AFr1cm+hRQsPfCg
//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLShader.h
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
//%Header } 6rbxsQNRlyc0I9Osy3NHmw
/*
 * $Id: MushGLShader.h,v 1.4 2007/04/18 09:22:36 southa Exp $
 * $Log: MushGLShader.h,v $
 * Revision 1.4  2007/04/18 09:22:36  southa
 * Header and level fixes
 *
 * Revision 1.3  2006/09/09 15:59:28  southa
 * Shader colour calculations
 *
 * Revision 1.2  2006/09/07 16:38:51  southa
 * Vertex shader
 *
 * Revision 1.1  2006/09/07 10:02:37  southa
 * Shader interface
 *
 */

#include "MushGLStandard.h"

#include "API/mushMushRuby.h"

class MushGLAttribs;

//:generate standard ostream xml1
class MushGLShader : public MushcoreVirtualObject
{
public:
    typedef MushcoreData<MushGLShader> tData;
    typedef MushcoreDataRef<MushGLShader> tDataRef;
    
    enum
    {
        kNumColourAttrib = 8
    };
    
    MushGLShader();
    virtual ~MushGLShader() {}
    void Make(void);
    void Bind(void);
    void Dump(std::ostream& ioOut) const;
    void UniformDump(std::ostream& ioOut) const;
    void Test(void);
    void Purge(void);
    void AttribsApply(const MushGLAttribs& inAttribs);
    
protected:
    std::string SourceGet(Mushware::GLHandle inShader) const;
    std::string InfoLogGet(Mushware::GLHandle inShader) const;
    bool CompileStatusGet(Mushware::GLHandle inShader) const;
    bool LinkStatusGet(Mushware::GLHandle inProgram) const;
    bool ValidateStatusGet(Mushware::GLHandle inProgram) const;
    GLint UniformLocationGet(const std::string& inName);

private:
    Mushware::GLHandle m_programHandle; //:xmlignore (because underlying type is void *)
    Mushware::GLHandle m_fragmentShaderHandle; //:xmlignore (because underlying type is void *)
    Mushware::GLHandle m_vertexShaderHandle; //:xmlignore (because underlying type is void *)
    std::string m_fragmentShader; //:readwrite
    std::string m_vertexShader; //:readwrite
    bool m_made;
    
    // Uniform variable indices
    GLint m_mush_ProjectionOffset; //:xmlignore
    GLint m_mush_ModelViewOffset; //:xmlignore
    GLint m_mush_ModelViewProjectionOffset; //:xmlignore
    std::vector<GLint> m_mush_Colours; //:xmlignore
    GLint m_mush_FValue; //:xmlignore
    
//%classPrototypes {
public:
    const std::string& FragmentShader(void) const { return m_fragmentShader; }
    void FragmentShaderSet(const std::string& inValue) { m_fragmentShader=inValue; }
    const std::string& VertexShader(void) const { return m_vertexShader; }
    void VertexShaderSet(const std::string& inValue) { m_vertexShader=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } mFLgB3+mKnKTa52wxh20GA
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushGLShader& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } qoj6wxmjO+ijSvcH/pLO8g
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
