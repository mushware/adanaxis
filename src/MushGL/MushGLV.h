//%includeGuardStart {
#ifndef MUSHGLV_H
#define MUSHGLV_H
//%includeGuardStart } K1QTY7i/bd0PCTwNGG+ziA
//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLV.h
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
//%Header } 7iEHHdeOPdV1ZH7aSJ/mHA
/*
 * $Id: MushGLV.h,v 1.7 2005/05/19 13:02:09 southa Exp $
 * $Log: MushGLV.h,v $
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
    
    bool HasVertexBuffer() const { return m_hasVertexBuffer; }
    bool UseVertexBuffer() const { return m_hasVertexBuffer; }
    
    void BindBuffer(GLenum target, GLuint buffer) const { if (m_fpBindBuffer != NULL) m_fpBindBuffer(target, buffer); }
    
    void BufferData(GLenum target, GLsizeiptr size, const GLvoid *data, GLenum usage) const { if (m_fpBufferData != NULL) m_fpBufferData(target, size, data, usage); }
    
    void BufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid *data) const { if (m_fpBufferSubData != NULL) m_fpBufferSubData(target, offset, size, data); }
    
    void DeleteBuffers(GLsizei n, const GLuint *buffers) const { if (m_fpDeleteBuffers != NULL) m_fpDeleteBuffers(n, buffers); }
    
    void GenBuffers(GLsizei n, GLuint *buffers) const { if (m_fpGenBuffers != NULL) m_fpGenBuffers(n, buffers); }
    
    void *MapBuffer(GLenum target, GLenum access) const { if (m_fpMapBuffer != NULL) return m_fpMapBuffer(target, access); else throw MushcoreLogicFail("MushGLV::MapBuffer"); }
    
    bool UnmapBuffer(GLenum target) const { if (m_fpUnmapBuffer != NULL) return (m_fpUnmapBuffer(target) != GL_FALSE); else return true; }
    
private:
    bool m_hasVertexBuffer;
    typedef void (*tfpBindBuffer)(GLenum target, GLuint buffer);
    tfpBindBuffer m_fpBindBuffer; // :fnpointer
    typedef void (*tfpBufferData)(GLenum target, GLsizeiptr size, const GLvoid *data, GLenum usage);
    tfpBufferData m_fpBufferData; // :fnpointer
    typedef void (*tfpBufferSubData)(GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid *data);
    tfpBufferSubData m_fpBufferSubData; // :fnpointer
    typedef void (*tfpDeleteBuffers)(GLsizei n, const GLuint *buffers);
    tfpDeleteBuffers m_fpDeleteBuffers; // :fnpointer
    typedef void (*tfpGenBuffers)(GLsizei n, GLuint *buffers);
    tfpGenBuffers m_fpGenBuffers; // :fnpointer
    typedef GLvoid *(*tfpMapBuffer)(GLenum target, GLenum access);
    tfpMapBuffer m_fpMapBuffer; // :fnpointer
    typedef GLboolean (*tfpUnmapBuffer)(GLenum target);
    tfpUnmapBuffer m_fpUnmapBuffer; // :fnpointer
        
    std::string m_vendor;
    std::string m_renderer;
    std::string m_version;
    std::string m_extensions;
    
    Mushware::U32 m_contextNum; //:read
//%classPrototypes {
public:
    const Mushware::U32& ContextNum(void) const { return m_contextNum; }
    void AutoPrint(std::ostream& ioOut) const;
//%classPrototypes } tZpXkTA5BVxgV6b1/yA+aA
};

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
