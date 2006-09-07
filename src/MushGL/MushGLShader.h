//%includeGuardStart {
#ifndef MUSHGLSHADER_H
#define MUSHGLSHADER_H
//%includeGuardStart } cGhxNJ2AFr1cm+hRQsPfCg
//%Header {
/*****************************************************************************
 *
 * File: src/MushGL/MushGLShader.h
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
//%Header } MmuefLWPCIWvwCK7IfDibQ
/*
 * $Id$
 * $Log$
 */

#include "MushGLStandard.h"

#include "API/mushMushRuby.h"

//:generate standard ostream xml1
class MushGLShader : public MushcoreVirtualObject
{
public:
    MushGLShader();
    virtual ~MushGLShader() {}
    void Make(void);
    void Bind(void);
    void Dump(std::ostream& ioOut) const;
    void Test(void);
    void Purge(void);
    
protected:
    std::string SourceGet(Mushware::GLHandle inShader) const;
    std::string InfoLogGet(Mushware::GLHandle inShader) const;
    bool CompileStatusGet(Mushware::GLHandle inShader) const;
    bool LinkStatusGet(Mushware::GLHandle inProgram) const;
    
private:
    Mushware::GLHandle m_programHandle; //:xmlignore (because underlying type is void *)
    Mushware::GLHandle m_fragmentShaderHandle; //:xmlignore (because underlying type is void *)
    Mushware::GLHandle m_vertexShaderHandle; //:xmlignore (because underlying type is void *)
    std::string m_fragmentShader; //:readwrite
    std::string m_vertexShader; //:readwrite
    bool m_made;
    
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
