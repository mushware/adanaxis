//%includeGuardStart {
#ifndef MUSHGLV_H
#define MUSHGLV_H
//%includeGuardStart } K1QTY7i/bd0PCTwNGG+ziA
//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLV.h
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
//%Header } rJ9tD80YuXvw1PL2FTvOKQ
/*
 * $Id: MushGLV.h,v 1.23 2006/09/07 16:38:51 southa Exp $
 * $Log: MushGLV.h,v $
 * Revision 1.23  2006/09/07 16:38:51  southa
 * Vertex shader
 *
 * Revision 1.22  2006/09/07 10:02:38  southa
 * Shader interface
 *
 * Revision 1.21  2006/09/06 17:33:18  southa
 * Shader interface
 *
 * Revision 1.20  2006/07/28 16:52:22  southa
 * Options work
 *
 * Revision 1.19  2006/06/30 15:05:34  southa
 * Texture and buffer purge
 *
 * Revision 1.18  2006/06/23 00:35:06  southa
 * win32 build fixes
 *
 * Revision 1.17  2006/06/01 20:13:00  southa
 * Initial texture caching
 *
 * Revision 1.16  2006/06/01 15:39:19  southa
 * DrawArray verification and fixes
 *
 * Revision 1.15  2005/09/05 17:14:23  southa
 * Solid rendering
 *
 * Revision 1.14  2005/08/31 23:57:27  southa
 * Texture coordinate work
 *
 * Revision 1.13  2005/08/29 18:40:57  southa
 * Solid rendering work
 *
 * Revision 1.12  2005/07/04 11:10:43  southa
 * Rendering pipeline
 *
 * Revision 1.11  2005/07/02 00:42:37  southa
 * Conditioning tweaks
 *
 * Revision 1.10  2005/06/08 20:59:51  southa
 * X11 release
 *
 * Revision 1.9  2005/05/26 16:05:29  southa
 * win32 support
 *
 * Revision 1.8  2005/05/26 00:46:40  southa
 * Made buildable on win32
 *
 * Revision 1.7  2005/05/19 13:02:09  southa
 * Mac release work
 *
 * Revision 1.6  2005/04/10 00:09:22  southa
 * Registration
 *
 * Revision 1.5  2005/02/10 12:34:03  southa
 * Template fixes
 *
 * Revision 1.4  2005/01/29 18:27:31  southa
 * Vertex buffer stuff
 *
 * Revision 1.3  2005/01/29 14:06:12  southa
 * OpenGL buffers and extensions
 *
 * Revision 1.2  2004/09/27 22:42:09  southa
 * MSVC compilation fixes
 *
 * Revision 1.1  2004/09/20 21:50:47  southa
 * Added GLV
 *
 */

#include "MushGLStandard.h"
#include "MushGLV.h"

//:generate ostream
class MushGLV : public MushcoreSingleton<MushGLV>
{
public:
    MushGLV();
    virtual ~MushGLV() {};
    virtual void Acquaint(void);
    virtual void Purge(void);
    
    void DrawArrays(GLenum inMode, GLint inFirst, GLsizei inCount);
    void BindTexture2D(GLuint inBindingName) { glBindTexture(GL_TEXTURE_2D, inBindingName); }
    void DeleteTexture(GLuint inBindingName) { glDeleteTextures(1, &inBindingName); }
    void ActiveTextureZeroBased(Mushware::U32 inTexNum);
    void ClientActiveTextureZeroBased(Mushware::U32 inTexNum);
    
    bool HasVertexBuffer(void) const { return m_hasVertexBuffer; }
    bool UseVertexBuffer(void) const { return m_hasVertexBuffer; }
    bool UseS3TC(void) const { return m_hasS3TC && m_useS3TC; }
    bool UseShader(void) const { return m_hasShader && m_useShader; }
    void BindBuffer(GLenum target, GLuint buffer) const { if (m_fpBindBuffer != NULL) m_fpBindBuffer(target, buffer); }
    
    void BufferData(GLenum target, GLsizeiptr size, const GLvoid *data, GLenum usage) const { if (m_fpBufferData != NULL) m_fpBufferData(target, size, data, usage); }
    
    void BufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid *data) const { if (m_fpBufferSubData != NULL) m_fpBufferSubData(target, offset, size, data); }
    
    void DeleteBuffers(GLsizei n, const GLuint *buffers) const { if (m_fpDeleteBuffers != NULL) m_fpDeleteBuffers(n, buffers); }
    
    void GenBuffers(GLsizei n, GLuint *buffers) const { if (m_fpGenBuffers != NULL) m_fpGenBuffers(n, buffers); }
    
    void *MapBuffer(GLenum target, GLenum access) const { if (m_fpMapBuffer != NULL) return m_fpMapBuffer(target, access); else throw MushcoreLogicFail("MushGLV::MapBuffer"); }
    
    bool UnmapBuffer(GLenum target) const { if (m_fpUnmapBuffer != NULL) return (m_fpUnmapBuffer(target) != GL_FALSE); else return true; }

	void GetBufferParameteriv(GLenum target, GLenum value, GLint *data) const { if (m_fpGetBufferParameteriv != NULL) return m_fpGetBufferParameteriv(target, value, data); else throw MushcoreLogicFail("MushGLV::GetBufferParameteriv"); }
	
    GLhandleARB CreateShaderObject(GLenum shaderType) const { if (m_fpCreateShaderObject != NULL) return m_fpCreateShaderObject(shaderType); else throw MushcoreLogicFail("MushGLV: CreateShaderObject"); }
    void ShaderSource(GLhandleARB shader, GLuint nstrings, const GLcharARB **strings, GLint *lengths) const { if (m_fpShaderSource != NULL) m_fpShaderSource(shader, nstrings, strings, lengths); else throw MushcoreLogicFail("MushGLV: ShaderSource"); }
    void CompileShader(GLhandleARB shader) const { if (m_fpCompileShader != NULL) m_fpCompileShader(shader); else throw MushcoreLogicFail("MushGLV: CompileShader"); }
    GLhandleARB CreateProgramObject(void) const { if (m_fpCreateProgramObject != NULL) return m_fpCreateProgramObject(); else throw MushcoreLogicFail("MushGLV: CreateProgramObject"); }
    void AttachObject(GLhandleARB program, GLhandleARB shader) const { if (m_fpAttachObject != NULL) m_fpAttachObject(program, shader); else throw MushcoreLogicFail("MushGLV: AttachObject"); }
    void LinkProgram(GLhandleARB shader) const { if (m_fpLinkProgram != NULL) m_fpLinkProgram(shader); else throw MushcoreLogicFail("MushGLV: LinkProgram"); }
    void UseProgramObject(GLhandleARB program) const { if (m_fpUseProgramObject != NULL) m_fpUseProgramObject(program); else throw MushcoreLogicFail("MushGLV: UseProgramObject"); }
    void DeleteObject(GLhandleARB object) const { if (m_fpDeleteObject != NULL) m_fpDeleteObject(object); else throw MushcoreLogicFail("MushGLV: DeleteObject"); }
    void GetObjectParameterfv(GLhandleARB object, GLenum pname, GLfloat *params) const { if (m_fpGetObjectParameterfv != NULL) m_fpGetObjectParameterfv(object, pname, params); else throw MushcoreLogicFail("MushGLV: GetObjectParameterfv"); }
    void GetObjectParameteriv(GLhandleARB object, GLenum pname, GLint *params) const { if (m_fpGetObjectParameteriv != NULL) m_fpGetObjectParameteriv(object, pname, params); else throw MushcoreLogicFail("MushGLV: GetObjectParameteriv"); }
    void GetShaderSource(GLhandleARB object, GLsizei maxLength, GLsizei *length, GLcharARB *source) const { if (m_fpGetShaderSource != NULL) m_fpGetShaderSource(object, maxLength, length, source); else throw MushcoreLogicFail("MushGLV: GetShaderSource"); }
    void GetInfoLog(GLhandleARB object, GLsizei maxLength, GLsizei *length, GLcharARB *infoLog) const { if (m_fpGetInfoLog != NULL) m_fpGetInfoLog(object, maxLength, length, infoLog); else throw MushcoreLogicFail("MushGLV: GetInfoLog"); }
    void VertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normlized, GLsizei stride, const GLvoid *pointer) const { if (m_fpVertexAttribPointer != NULL) m_fpVertexAttribPointer(index, size, type, normlized, stride, pointer); else throw MushcoreLogicFail("MushGLV: VertexAttribPointer"); }
    void EnableVertexAttribArray(GLuint index) const { if (m_fpEnableVertexAttribArray != NULL) m_fpEnableVertexAttribArray(index); else throw MushcoreLogicFail("MushGLV: EnableVertexAttribArray"); }
    void DisableVertexAttribArray(GLuint index) const { if (m_fpDisableVertexAttribArray != NULL) m_fpDisableVertexAttribArray(index); else throw MushcoreLogicFail("MushGLV: DisableVertexAttribArray"); }
    void BindAttribLocation(GLhandleARB progam, const GLcharARB *name) const { if (m_fpBindAttribLocation != NULL) m_fpBindAttribLocation(progam, name); else throw MushcoreLogicFail("MushGLV: BindAttribLocation"); }
    GLint GetAttribLocation(GLhandleARB progam, const GLcharARB *name) const { if (m_fpGetAttribLocation != NULL) return m_fpGetAttribLocation(progam, name); else throw MushcoreLogicFail("MushGLV: GetAttribLocation"); }
    void GetActiveAttrib(GLhandleARB progam, GLuint index, GLsizei maxLength, GLsizei *length, GLint *size, GLenum *type, GLcharARB *name) const { if (m_fpGetActiveAttrib != NULL) m_fpGetActiveAttrib(progam, index, maxLength, length, size, type, name); else throw MushcoreLogicFail("MushGLV: GetActiveAttrib"); }
    void VertexAttrib4fv(GLuint index, GLenum pname, GLfloat *params) const { if (m_fpVertexAttrib4fv != NULL) m_fpVertexAttrib4fv(index, pname, params); else throw MushcoreLogicFail("MushGLV: VertexAttrib4fv"); }
    void VertexAttrib4iv(GLuint index, GLenum pname, GLint *params) const { if (m_fpVertexAttrib4iv != NULL) m_fpVertexAttrib4iv(index, pname, params); else throw MushcoreLogicFail("MushGLV: VertexAttrib4iv"); }
    void GetVertexAttribPointerv(GLuint index, GLenum pname, GLvoid **pointer) const { if (m_fpGetVertexAttribPointerv != NULL) m_fpGetVertexAttribPointerv(index, pname, pointer); else throw MushcoreLogicFail("MushGLV: GetVertexAttribPointerv"); }
    GLint GetUniformLocation(GLhandleARB progam, const GLcharARB *name) const { if (m_fpGetUniformLocation != NULL) return m_fpGetUniformLocation(progam, name); else throw MushcoreLogicFail("MushGLV: GetUniformLocation"); }
    void Uniform1i(GLint location, GLint v0) const { if (m_fpUniform1i != NULL) m_fpUniform1i(location, v0); else throw MushcoreLogicFail("MushGLV: Uniform1i"); }
    void Uniform4iv(GLint location, GLsizei count, const GLint *v) const { if (m_fpUniform4iv != NULL) m_fpUniform4iv(location, count, v); else throw MushcoreLogicFail("MushGLV: Uniform4iv"); }
    void Uniform1f(GLint location, GLfloat v0) const { if (m_fpUniform1f != NULL) m_fpUniform1f(location, v0); else throw MushcoreLogicFail("MushGLV: Uniform1f"); }
    void Uniform4fv(GLint location, GLsizei count, const GLfloat *v) const { if (m_fpUniform4fv != NULL) m_fpUniform4fv(location, count, v); else throw MushcoreLogicFail("MushGLV: Uniform4fv"); }
    void UniformMatrix4fv(GLint location, GLuint count, GLboolean transpose, const GLfloat *v) const { if (m_fpUniformMatrix4fv != NULL) m_fpUniformMatrix4fv(location, count, transpose, v); else throw MushcoreLogicFail("MushGLV: UniformMatrix4fv"); }
    void GetActiveUniform(GLhandleARB progam, GLuint index, GLsizei maxLength, GLsizei *length, GLint *size, GLenum *type, GLcharARB *name) const { if (m_fpGetActiveUniform != NULL) m_fpGetActiveUniform(progam, index, maxLength, length, size, type, name); else throw MushcoreLogicFail("MushGLV: GetActiveUniform"); }
    void ValidateProgram(GLhandleARB program) const { if (m_fpValidateProgram != NULL) m_fpValidateProgram(program); else throw MushcoreLogicFail("MushGLV: ValidateProgram"); }

protected:
    void ContextValidAssert(void) const;
    void DrawArraysVerify(GLenum inMode, GLint inFirst, GLsizei inCount) const;
    void BufferValidate(Mushware::U32 inSize) const;
	
private:
    bool m_hasVertexBuffer;
    typedef void (MUSHCORE_APIENTRY *tfpBindBuffer)(GLenum target, GLuint buffer);
    tfpBindBuffer m_fpBindBuffer; // :fnpointer
    typedef void (MUSHCORE_APIENTRY *tfpBufferData)(GLenum target, GLsizeiptr size, const GLvoid *data, GLenum usage);
    tfpBufferData m_fpBufferData; // :fnpointer
    typedef void (MUSHCORE_APIENTRY *tfpBufferSubData)(GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid *data);
    tfpBufferSubData m_fpBufferSubData; // :fnpointer
    typedef void (MUSHCORE_APIENTRY *tfpDeleteBuffers)(GLsizei n, const GLuint *buffers);
    tfpDeleteBuffers m_fpDeleteBuffers; // :fnpointer
    typedef void (MUSHCORE_APIENTRY *tfpGenBuffers)(GLsizei n, GLuint *buffers);
    tfpGenBuffers m_fpGenBuffers; // :fnpointer
    typedef GLvoid *(MUSHCORE_APIENTRY *tfpMapBuffer)(GLenum target, GLenum access);
    tfpMapBuffer m_fpMapBuffer; // :fnpointer
    typedef GLboolean (MUSHCORE_APIENTRY *tfpUnmapBuffer)(GLenum target);
    tfpUnmapBuffer m_fpUnmapBuffer; // :fnpointer
    typedef void (MUSHCORE_APIENTRY *tfpGetBufferParameteriv)(GLenum target, GLenum value, GLint *data);
    tfpGetBufferParameteriv m_fpGetBufferParameteriv; // :fnpointer
        
    bool m_hasActiveTexture;
    typedef void (MUSHCORE_APIENTRY *tfpActiveTexture)(GLenum texture);
    tfpActiveTexture m_fpActiveTexture; // :fnpointer
    typedef void (MUSHCORE_APIENTRY *tfpClientActiveTexture)(GLenum texture);
    tfpClientActiveTexture m_fpClientActiveTexture; // :fnpointer

    bool m_hasShader; //:read
	bool m_useShader; //:write
    typedef GLhandleARB (MUSHCORE_APIENTRY *tfpCreateShaderObject)(GLenum shaderType);
    tfpCreateShaderObject m_fpCreateShaderObject; // :fnpointer
    typedef void (MUSHCORE_APIENTRY *tfpShaderSource)(GLhandleARB shader, GLuint nstrings, const GLcharARB **strings, GLint *lengths);
    tfpShaderSource m_fpShaderSource; // :fnpointer
    typedef void (MUSHCORE_APIENTRY *tfpCompileShader)(GLhandleARB shader);
    tfpCompileShader m_fpCompileShader; // :fnpointer
    typedef GLhandleARB (MUSHCORE_APIENTRY *tfpCreateProgramObject)(void);
    tfpCreateProgramObject m_fpCreateProgramObject; // :fnpointer
    typedef void (MUSHCORE_APIENTRY *tfpAttachObject)(GLhandleARB program, GLhandleARB shader);
    tfpAttachObject m_fpAttachObject; // :fnpointer
    typedef void (MUSHCORE_APIENTRY *tfpLinkProgram)(GLhandleARB shader);
    tfpLinkProgram m_fpLinkProgram; // :fnpointer  
    typedef void (MUSHCORE_APIENTRY *tfpUseProgramObject)(GLhandleARB program);
    tfpUseProgramObject m_fpUseProgramObject; // :fnpointer  
    typedef void (MUSHCORE_APIENTRY *tfpDeleteObject)(GLhandleARB object);
    tfpDeleteObject m_fpDeleteObject; // :fnpointer  
    typedef void (MUSHCORE_APIENTRY *tfpGetObjectParameterfv)(GLhandleARB object, GLenum pname, GLfloat *params);
    tfpGetObjectParameterfv m_fpGetObjectParameterfv; // :fnpointer  
    typedef void (MUSHCORE_APIENTRY *tfpGetObjectParameteriv)(GLhandleARB object, GLenum pname, GLint *params);
    tfpGetObjectParameteriv m_fpGetObjectParameteriv; // :fnpointer  
    typedef void (MUSHCORE_APIENTRY *tfpGetShaderSource)(GLhandleARB object, GLsizei maxLength, GLsizei *length, GLcharARB *source);
    tfpGetShaderSource m_fpGetShaderSource; // :fnpointer  
    typedef void (MUSHCORE_APIENTRY *tfpGetInfoLog)(GLhandleARB object, GLsizei maxLength, GLsizei *length, GLcharARB *infoLog);
    tfpGetInfoLog m_fpGetInfoLog; // :fnpointer  
    typedef void (MUSHCORE_APIENTRY *tfpVertexAttribPointer)(GLuint index, GLint size, GLenum type, GLboolean normlized, GLsizei stride, const GLvoid *pointer);
    tfpVertexAttribPointer m_fpVertexAttribPointer; // :fnpointer  
    typedef void (MUSHCORE_APIENTRY *tfpEnableVertexAttribArray)(GLuint index);
    tfpEnableVertexAttribArray m_fpEnableVertexAttribArray; // :fnpointer  
    typedef void (MUSHCORE_APIENTRY *tfpDisableVertexAttribArray)(GLuint index);
    tfpDisableVertexAttribArray m_fpDisableVertexAttribArray; // :fnpointer  
    typedef void (MUSHCORE_APIENTRY *tfpBindAttribLocation)(GLhandleARB progam, const GLcharARB *name);
    tfpBindAttribLocation m_fpBindAttribLocation; // :fnpointer  
    typedef GLint (MUSHCORE_APIENTRY *tfpGetAttribLocation)(GLhandleARB progam, const GLcharARB *name);
    tfpGetAttribLocation m_fpGetAttribLocation; // :fnpointer  
    typedef void (MUSHCORE_APIENTRY *tfpGetActiveAttrib)(GLhandleARB progam, GLuint index, GLsizei maxLength, GLsizei *length, GLint *size, GLenum *type, GLcharARB *name);
    tfpGetActiveAttrib m_fpGetActiveAttrib; // :fnpointer  
    typedef void (MUSHCORE_APIENTRY *tfpVertexAttrib4fv)(GLuint index, GLenum pname, GLfloat *params);
    tfpVertexAttrib4fv m_fpVertexAttrib4fv; // :fnpointer  
    typedef void (MUSHCORE_APIENTRY *tfpVertexAttrib4iv)(GLuint index, GLenum pname, GLint *params);
    tfpVertexAttrib4iv m_fpVertexAttrib4iv; // :fnpointer  
    typedef void (MUSHCORE_APIENTRY *tfpGetVertexAttribPointerv)(GLuint index, GLenum pname, GLvoid **pointer);
    tfpGetVertexAttribPointerv m_fpGetVertexAttribPointerv; // :fnpointer  
    typedef GLint (MUSHCORE_APIENTRY *tfpGetUniformLocation)(GLhandleARB progam, const GLcharARB *name);
    tfpGetUniformLocation m_fpGetUniformLocation; // :fnpointer  
    typedef void (MUSHCORE_APIENTRY *tfpUniform1i)(GLint location, GLint v0);
    tfpUniform1i m_fpUniform1i; // :fnpointer  
    typedef void (MUSHCORE_APIENTRY *tfpUniform4iv)(GLint location, GLsizei count, const GLint *v);
    tfpUniform4iv m_fpUniform4iv; // :fnpointer  
    typedef void (MUSHCORE_APIENTRY *tfpUniform1f)(GLint location, GLfloat v0);
    tfpUniform1f m_fpUniform1f; // :fnpointer  
    typedef void (MUSHCORE_APIENTRY *tfpUniform4fv)(GLint location, GLsizei count, const GLfloat *v);
    tfpUniform4fv m_fpUniform4fv; // :fnpointer  
    typedef void (MUSHCORE_APIENTRY *tfpUniformMatrix4fv)(GLint location, GLuint count, GLboolean transpose, const GLfloat *v);
    tfpUniformMatrix4fv m_fpUniformMatrix4fv; // :fnpointer  
    typedef void (MUSHCORE_APIENTRY *tfpGetActiveUniform)(GLhandleARB progam, GLuint index, GLsizei maxLength, GLsizei *length, GLint *size, GLenum *type, GLcharARB *name);
    tfpGetActiveUniform m_fpGetActiveUniform; // :fnpointer
    typedef void (MUSHCORE_APIENTRY *tfpValidateProgram)(GLhandleARB program);
    tfpValidateProgram m_fpValidateProgram; // :fnpointer  
    Mushware::U32 m_maxFragmentUniformComponents; //:read
    
    
    void *GetProcAddressWithARB(const std::string& inName) const;
    
    std::string m_vendor;
    std::string m_renderer;
    std::string m_version;
    std::string m_extensions;
    Mushware::U32 m_numTextureUnits; //:read
    bool m_hasS3TC; //:read
	bool m_useS3TC; //:write
    
    Mushware::U32 m_contextNum; //:read
    bool m_contextValid; //:read
    
//%classPrototypes {
public:
    const bool& HasShader(void) const { return m_hasShader; }
    void UseShaderSet(const bool& inValue) { m_useShader=inValue; }
    const Mushware::U32& MaxFragmentUniformComponents(void) const { return m_maxFragmentUniformComponents; }
    const Mushware::U32& NumTextureUnits(void) const { return m_numTextureUnits; }
    const bool& HasS3TC(void) const { return m_hasS3TC; }
    void UseS3TCSet(const bool& inValue) { m_useS3TC=inValue; }
    const Mushware::U32& ContextNum(void) const { return m_contextNum; }
    const bool& ContextValid(void) const { return m_contextValid; }
    virtual void AutoPrint(std::ostream& ioOut) const;
//%classPrototypes } V7083U4lmtjlDOlJNceWlA
};

inline void
MushGLV::DrawArrays(GLenum inMode, GLint inFirst, GLsizei inCount)
{
#ifndef NDEBUG
	DrawArraysVerify(inMode, inFirst, inCount);
#endif
    glDrawArrays(inMode, inFirst, inCount);
}

inline void
MushGLV::ContextValidAssert(void) const
{
    if (!ContextValid())
    {
        throw MushcoreLogicFail("MushGLV operation on invalid context");
    }
}

inline void
MushGLV::ActiveTextureZeroBased(Mushware::U32 inTexNum)
{
    ContextValidAssert();
    if (m_hasActiveTexture)
    {
        if (inTexNum >= m_numTextureUnits)
        {
            std::ostringstream message;
            message << "Texture number too high (" << inTexNum << " >= " << m_numTextureUnits << ")";
            throw MushcoreRequestFail(message.str());
        }
        MUSHCOREASSERT(m_fpActiveTexture != NULL);
        m_fpActiveTexture(GL_TEXTURE0 + inTexNum);
    }
}

inline void
MushGLV::ClientActiveTextureZeroBased(Mushware::U32 inTexNum)
{
    ContextValidAssert();
    if (m_hasActiveTexture)
    {
        if (inTexNum >= m_numTextureUnits)
        {
            std::ostringstream message;
            message << "Texture number too high (" << inTexNum << " >= " << m_numTextureUnits << ")";
            throw MushcoreRequestFail(message.str());
        }
        MUSHCOREASSERT(m_fpClientActiveTexture != NULL);
        m_fpClientActiveTexture(GL_TEXTURE0 + inTexNum);
    }
}

//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushGLV& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } ChyHizCPHmjy087L19xK6g
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
