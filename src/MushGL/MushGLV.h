//%includeGuardStart {
#ifndef MUSHGLV_H
#define MUSHGLV_H
//%includeGuardStart } K1QTY7i/bd0PCTwNGG+ziA
//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLV.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } uiXTBqRVrI+qFoX2dUuamg
/*
 * $Id: MushGLV.h,v 1.2 2004/09/27 22:42:09 southa Exp $
 * $Log: MushGLV.h,v $
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
    
    void BindBuffer(GLenum target, GLuint buffer);
    
private:
    typedef void (*tfpBindBuffer)(GLenum target, GLuint buffer);
    tfpBindBuffer m_fpBindBuffer; // :aspointer
        
    std::string m_vendor;
    std::string m_renderer;
    std::string m_version;
    std::string m_extensions;
    
//%classPrototypes {
public:
    virtual void AutoPrint(std::ostream& ioOut) const;
//%classPrototypes } b86DSDsq8lQQbiM0rrNtkg
};

inline void
MushGLV::BindBuffer(GLenum target, GLuint buffer)
{
    if (m_fpBindBuffer != NULL)
    {
        m_fpBindBuffer(target, buffer);
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
