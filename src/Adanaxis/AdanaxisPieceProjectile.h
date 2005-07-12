//%includeGuardStart {
#ifndef ADANAXISPIECEPROJECTILE_H
#define ADANAXISPIECEPROJECTILE_H
//%includeGuardStart } tP6o2lew/9PZ78Rtte9Qvw
//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisPieceProjectile.h
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
//%Header } oprIPxIlqMIU0R5tKHZ3SA
/*
 * $Id$
 * $Log$
 */

#include "AdanaxisStandard.h"

#include "API/mushMushGame.h"
#include "API/mushMushGL.h"
#include "API/mushMushMesh.h"
#include "API/mushMushRender.h"

//:xml1base MushGamePiece
//:generate virtual standard ostream xml1
class AdanaxisPieceProjectile : public MushGamePiece
{
public:
    explicit AdanaxisPieceProjectile(const std::string& inID = "");
    virtual ~AdanaxisPieceProjectile() {}
    
    virtual void Move(MushGameLogic& ioLogic, const Mushware::tVal inFrameslice);

    virtual void Render(MushGameLogic& ioLogic, MushRenderMesh& inRender, const MushGameCamera& inCamera);
    
private:
    std::string m_id;
    std::string m_owner; //:readwrite
    Mushware::tVal m_initialVelocity; //:readwrite
    Mushware::tMsec m_lifeMsec; //:readwrite
    Mushware::tMsec m_expiryMsec; //:readwrite
    bool m_expireFlag; //:readwrite
    MushMesh4Mesh m_mesh; //:readwrite :wref
    MushGLBuffers::tDataRef m_buffersRef; //:readwrite
    
//%classPrototypes {
public:
    const std::string& Owner(void) const { return m_owner; }
    void OwnerSet(const std::string& inValue) { m_owner=inValue; }
    const Mushware::tVal& InitialVelocity(void) const { return m_initialVelocity; }
    void InitialVelocitySet(const Mushware::tVal& inValue) { m_initialVelocity=inValue; }
    const Mushware::tMsec& LifeMsec(void) const { return m_lifeMsec; }
    void LifeMsecSet(const Mushware::tMsec& inValue) { m_lifeMsec=inValue; }
    const Mushware::tMsec& ExpiryMsec(void) const { return m_expiryMsec; }
    void ExpiryMsecSet(const Mushware::tMsec& inValue) { m_expiryMsec=inValue; }
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
//%classPrototypes } 70INbYWY3BiCbNYTAY7PYA
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const AdanaxisPieceProjectile& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } KpZ65HGy/OlB/f3k/Y6E3w
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
