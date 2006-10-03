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
 * software licence version 1.1, under the terms for 'Proprietary original
 * source files'.  If not supplied with this software, a copy of the licence
 * can be obtained from Mushware Limited via http://www.mushware.com/.
 * One of your options under that licence is to use and distribute this file
 * under the terms of the GNU General Public Licence version 2.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } yAaZbixiy4nfgXOSFEVzQQ
/*
 * $Id: AdanaxisPieceProjectile.h,v 1.10 2006/08/25 01:44:57 southa Exp $
 * $Log: AdanaxisPieceProjectile.h,v $
 * Revision 1.10  2006/08/25 01:44:57  southa
 * Khazi fire
 *
 * Revision 1.9  2006/08/01 17:21:26  southa
 * River demo
 *
 * Revision 1.8  2006/07/24 18:46:47  southa
 * Depth sorting
 *
 * Revision 1.7  2006/07/19 14:34:51  southa
 * Flare effects
 *
 * Revision 1.6  2006/06/30 15:05:32  southa
 * Texture and buffer purge
 *
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
    explicit AdanaxisPieceProjectile(const std::string& inID = "", const MushRubyValue& inParams = MushRubyValue());
    virtual ~AdanaxisPieceProjectile();
    
    virtual void Move(MushGameLogic& ioLogic, const Mushware::tVal inFrameslice);
    virtual bool Render(MushGLJobRender& outRender, MushGameLogic& ioLogic, MushRenderMesh& inRender, const MushGameCamera& inCamera);
    
    virtual void CollisionFatalConsume(MushGameLogic& ioLogic, const MushGameMessageCollisionFatal& inMessage);
    virtual void MessageConsume(MushGameLogic& ioLogic, const MushGameMessage& inMessage);
    virtual void Explode(MushGameLogic& ioLogic);
    
    virtual const MushMesh4Mesh& CollisionMesh(void) const { return Mesh(); }
    virtual const MushMeshPosticity& CollisionPost(void) const { return Post(); }

    virtual void Load(Mushware::tRubyValue inSelf);
    virtual void Save(Mushware::tRubyValue inSelf);
    static Mushware::tRubyValue RubyCreate(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0);
    static Mushware::tRubyValue Klass(void);
    static void RubyInstall(void);

private:
    std::string m_owner; //:readwrite
    Mushware::tMsec m_lifeMsec; //:readwrite
    Mushware::tMsec m_launchMsec; //:readwrite

    static Mushware::tRubyValue m_rubyKlass; // Must duplicate this in derived classes
    
//%classPrototypes {
public:
    const std::string& Owner(void) const { return m_owner; }
    void OwnerSet(const std::string& inValue) { m_owner=inValue; }
    const Mushware::tMsec& LifeMsec(void) const { return m_lifeMsec; }
    void LifeMsecSet(const Mushware::tMsec& inValue) { m_lifeMsec=inValue; }
    const Mushware::tMsec& LaunchMsec(void) const { return m_launchMsec; }
    void LaunchMsecSet(const Mushware::tMsec& inValue) { m_launchMsec=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } /+wEvZoaKvn7hVFWv+ug0w
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
