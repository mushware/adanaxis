//%includeGuardStart {
#ifndef ADANAXISPIECEPROJECTILE_H
#define ADANAXISPIECEPROJECTILE_H
//%includeGuardStart } tP6o2lew/9PZ78Rtte9Qvw
//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisPieceProjectile.h
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
//%Header } AFo2vzl87aFxQx3VFVpFzA
/*
 * $Id: AdanaxisPieceProjectile.h,v 1.5 2006/06/21 12:17:55 southa Exp $
 * $Log: AdanaxisPieceProjectile.h,v $
 * Revision 1.5  2006/06/21 12:17:55  southa
 * Ruby object generation
 *
 * Revision 1.4  2006/06/01 15:38:48  southa
 * DrawArray verification and fixes
 *
 * Revision 1.3  2005/08/01 13:09:57  southa
 * Collision messaging
 *
 * Revision 1.2  2005/07/27 18:10:17  southa
 * Collision checking
 *
 * Revision 1.1  2005/07/12 12:18:17  southa
 * Projectile work
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
class AdanaxisPieceProjectile : public MushGamePiece, public MushCollisionPiece
{
public:
    explicit AdanaxisPieceProjectile(const std::string& inID = "");
    virtual ~AdanaxisPieceProjectile() {}
    
    virtual void Move(MushGameLogic& ioLogic, const Mushware::tVal inFrameslice);
    virtual void Render(MushGameLogic& ioLogic, MushRenderMesh& inRender, const MushGameCamera& inCamera);
    
    virtual void CollisionFatalConsume(MushGameLogic& ioLogic, const MushGameMessageCollisionFatal& inMessage);
    virtual void MessageConsume(MushGameLogic& ioLogic, const MushGameMessage& inMessage);

    virtual const MushMesh4Mesh& CollisionMesh(void) const { return Mesh(); }
    virtual const MushMeshPosticity& CollisionPost(void) const { return Post(); }

private:
    std::string m_owner; //:readwrite
    Mushware::tVal m_initialVelocity; //:readwrite
    Mushware::tMsec m_lifeMsec; //:readwrite
    Mushware::tMsec m_expiryMsec; //:readwrite
    
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
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } rkJVCCgUhPodpSI00aAOLg
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
