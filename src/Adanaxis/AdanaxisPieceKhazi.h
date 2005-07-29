//%includeGuardStart {
#ifndef ADANAXISPIECEKHAZI_H
#define ADANAXISPIECEKHAZI_H
//%includeGuardStart } 1DybVjjopcgdO65Z1fH//g
//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisPieceKhazi.h
 *
 * Copyright: Andy Southgate 2005
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
//%Header } ECoWMgOgfphFtEFoxlZ8Qg
/*
 * $Id: AdanaxisPieceKhazi.h,v 1.1 2005/07/19 10:08:06 southa Exp $
 * $Log: AdanaxisPieceKhazi.h,v $
 * Revision 1.1  2005/07/19 10:08:06  southa
 * Adanaxis work
 *
 */

#include "AdanaxisStandard.h"

#include "API/mushMushCollision.h"
#include "API/mushMushGame.h"
#include "API/mushMushGL.h"
#include "API/mushMushMesh.h"
#include "API/mushMushRender.h"

//:xml1base MushGamePiece
//:generate virtual standard ostream xml1
class AdanaxisPieceKhazi : public MushGamePiece, public MushCollisionPiece
{
public:
    explicit AdanaxisPieceKhazi(const std::string& inID = "");
    virtual ~AdanaxisPieceKhazi() {}

    virtual void Move(MushGameLogic& ioLogic, const Mushware::tVal inFrameslice);
    virtual void Render(MushGameLogic& ioLogic, MushRenderMesh& inRender, const MushGameCamera& inCamera);
    
    virtual const MushMesh4Mesh& CollisionMesh(void) const { return m_mesh; }
    virtual const MushMeshPosticity& CollisionPost(void) const { return Post(); }

private:
    std::string m_id;
    bool m_expireFlag; //:readwrite
    MushMesh4Mesh m_mesh; //:readwrite :wref
    MushGLBuffers::tDataRef m_buffersRef; //:readwrite
//%classPrototypes {
public:
    const bool& ExpireFlag(void) const { return m_expireFlag; }
    void ExpireFlagSet(const bool& inValue) { m_expireFlag=inValue; }
    const MushMesh4Mesh& Mesh(void) const { return m_mesh; }
    void MeshSet(const MushMesh4Mesh& inValue) { m_mesh=inValue; }
    // Writable reference for m_mesh
    MushMesh4Mesh& MeshWRef(void) { return m_mesh; }
    const MushGLBuffers::tDataRef& BuffersRef(void) const { return m_buffersRef; }
    void BuffersRefSet(const MushGLBuffers::tDataRef& inValue) { m_buffersRef=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } FjcY3+C7MWxGfZq26ztv9A
};

//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const AdanaxisPieceKhazi& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } blutLiRI/IwJMUW7CKPkuA
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
