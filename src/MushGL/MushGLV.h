//%includeGuardStart {
#ifndef MUSHGLV_H
#define MUSHGLV_H
//%includeGuardStart } K1QTY7i/bd0PCTwNGG+ziA
//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLV.h
 *
 * Author: Andy Southgate 2002-2006
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
//%Header } JUBCCFXz/CzIx64ACD8wjA
/*
 * $Id: MushGLV.h,v 1.16 2006/06/01 15:39:19 southa Exp $
 * $Log: MushGLV.h,v $
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
    virtual void Acquaint();
    
    void DrawArrays(GLenum inMode, GLint inFirst, GLsizei inCount);
    void BindTexture2D(GLuint inBindingName) { glBindTexture(GL_TEXTURE_2D, inBindingName); }
    void ActiveTextureZeroBased(Mushware::U32 inTexNum);
    void ClientActiveTextureZeroBased(Mushware::U32 inTexNum);
    
    bool HasVertexBuffer() const { return m_hasVertexBuffer; }
    bool UseVertexBuffer() const { return m_hasVertexBuffer; }
    
    void BindBuffer(GLenum target, GLuint buffer) const { if (m_fpBindBuffer != NULL) m_fpBindBuffer(target, buffer); }
    
    void BufferData(GLenum target, GLsizeiptr size, const GLvoid *data, GLenum usage) const { if (m_fpBufferData != NULL) m_fpBufferData(target, size, data, usage); }
    
    void BufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid *data) const { if (m_fpBufferSubData != NULL) m_fpBufferSubData(target, offset, size, data); }
    
    void DeleteBuffers(GLsizei n, const GLuint *buffers) const { if (m_fpDeleteBuffers != NULL) m_fpDeleteBuffers(n, buffers); }
    
    void GenBuffers(GLsizei n, GLuint *buffers) const { if (m_fpGenBuffers != NULL) m_fpGenBuffers(n, buffers); }
    
    void *MapBuffer(GLenum target, GLenum access) const { if (m_fpMapBuffer != NULL) return m_fpMapBuffer(target, access); else throw MushcoreLogicFail("MushGLV::MapBuffer"); }
    
    bool UnmapBuffer(GLenum target) const { if (m_fpUnmapBuffer != NULL) return (m_fpUnmapBuffer(target) != GL_FALSE); else return true; }

	void GetBufferParameteriv(GLenum target, GLenum value, GLint *data) const { if (m_fpGetBufferParameteriv != NULL) return m_fpGetBufferParameteriv(target, value, data); else throw MushcoreLogicFail("MushGLV::GetBufferParameteriv"); }
	
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
        
    void *GetProcAddressWithARB(const std::string& inName) const;
    
    std::string m_vendor;
    std::string m_renderer;
    std::string m_version;
    std::string m_extensions;
    Mushware::U32 m_numTextureUnits; //:read
    bool m_hasS3TC; //:read
	
    Mushware::U32 m_contextNum; //:read
    bool m_contextValid; //:read
    
//%classPrototypes {
public:
    const Mushware::U32& NumTextureUnits(void) const { return m_numTextureUnits; }
    const bool& HasS3TC(void) const { return m_hasS3TC; }
    const Mushware::U32& ContextNum(void) const { return m_contextNum; }
    const bool& ContextValid(void) const { return m_contextValid; }
    virtual void AutoPrint(std::ostream& ioOut) const;
//%classPrototypes } xh5aSPuEY0XhVV6xBEZ5rQ
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
    if (inTexNum >= m_numTextureUnits)
    {
        std::ostringstream message;
        message << "Texture number too high (" << inTexNum << " >= " << m_numTextureUnits << ")";
        throw MushcoreRequestFail(message.str());
    }
    glActiveTexture(GL_TEXTURE0 + inTexNum);
}

inline void
MushGLV::ClientActiveTextureZeroBased(Mushware::U32 inTexNum)
{
    ContextValidAssert();
    if (inTexNum >= m_numTextureUnits)
    {
        std::ostringstream message;
        message << "Texture number too high (" << inTexNum << " >= " << m_numTextureUnits << ")";
        throw MushcoreRequestFail(message.str());
    }
    glClientActiveTexture(GL_TEXTURE0 + inTexNum);
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
