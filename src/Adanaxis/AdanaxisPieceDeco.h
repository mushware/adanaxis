//%includeGuardStart {
#ifndef ADANAXISPIECEDECO_H
#define ADANAXISPIECEDECO_H
//%includeGuardStart } oqn4Y6tbxdOzvAL0fqtoXA
//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisPieceDeco.h
 *
 * Copyright: Andy Southgate 2005-2006
 *
 * This file may be used and distributed under the terms of the Mushware
 * software licence version 1.0, under the terms for 'Proprietary original
 * source files'.  If not supplied with this software, a copy of the licence
 * can be obtained from Mushware Limited via http://www.mushware.com/.
 * One of your options under that licence is to use and distribute this file
 * under the terms of the GNU General Public Licence version 2.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 6GdOb3M8gmTP56sPCf1YGA
/*
 * $Id: AdanaxisPieceDeco.h,v 1.6 2006/06/01 15:38:47 southa Exp $
 * $Log: AdanaxisPieceDeco.h,v $
 * Revision 1.6  2006/06/01 15:38:47  southa
 * DrawArray verification and fixes
 *
 * Revision 1.5  2005/07/12 12:18:17  southa
 * Projectile work
 *
 * Revision 1.4  2005/07/04 11:10:43  southa
 * Rendering pipeline
 *
 * Revision 1.3  2005/07/01 10:36:46  southa
 * MushRender work
 *
 * Revision 1.2  2005/06/30 16:29:24  southa
 * Adanaxis work
 *
 * Revision 1.1  2005/06/30 14:26:35  southa
 * Adanaxis work
 *
 */

#include "AdanaxisStandard.h"

#include "API/mushMushGame.h"
#include "API/mushMushGL.h"
#include "API/mushMushMesh.h"
#include "API/mushMushRender.h"

//:xml1base MushGamePiece
//:generate virtual standard ostream xml1
class AdanaxisPieceDeco : public MushGamePiece
{
public:
    explicit AdanaxisPieceDeco(const std::string& inID = "");
    virtual ~AdanaxisPieceDeco() {}
    
    virtual void Render(MushGameLogic& ioLogic, MushRenderMesh& inRender, const MushGameCamera& inCamera);
    
    virtual void TexCoordBuffersNameSet(const std::string& inName) { m_texCoordBuffersRef.NameSet(inName); }
    
private:
    std::string m_id;
    MushMesh4Mesh m_mesh; //:readwrite :wref
    MushGLBuffers::tDataRef m_buffersRef; //:readwrite
    MushGLBuffers::tSharedDataRef m_texCoordBuffersRef; //:readwrite
    
//%classPrototypes {
public:
    const MushMesh4Mesh& Mesh(void) const { return m_mesh; }
    void MeshSet(const MushMesh4Mesh& inValue) { m_mesh=inValue; }
    // Writable reference for m_mesh
    MushMesh4Mesh& MeshWRef(void) { return m_mesh; }
    const MushGLBuffers::tDataRef& BuffersRef(void) const { return m_buffersRef; }
    void BuffersRefSet(const MushGLBuffers::tDataRef& inValue) { m_buffersRef=inValue; }
    const MushGLBuffers::tSharedDataRef& TexCoordBuffersRef(void) const { return m_texCoordBuffersRef; }
    void TexCoordBuffersRefSet(const MushGLBuffers::tSharedDataRef& inValue) { m_texCoordBuffersRef=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } nRxow55pBICnEm4KzNz7NQ
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const AdanaxisPieceDeco& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } U59qcX7inEXnV9haw5/Q8Q
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
