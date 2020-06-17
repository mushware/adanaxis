//%includeGuardStart {
#ifndef ADANAXISPIECEPROJECTILE_H
#define ADANAXISPIECEPROJECTILE_H
//%includeGuardStart } tP6o2lew/9PZ78Rtte9Qvw
//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisPieceProjectile.h
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
//%Header } d+Xu7tWTx3atkSHbhJnzLg
/*
 * $Id: AdanaxisPieceProjectile.h,v 1.17 2007/04/18 09:22:02 southa Exp $
 * $Log: AdanaxisPieceProjectile.h,v $
 * Revision 1.17  2007/04/18 09:22:02  southa
 * Header and level fixes
 *
 * Revision 1.16  2006/11/12 20:09:54  southa
 * Missile guidance
 *
 * Revision 1.15  2006/11/12 14:39:50  southa
 * Player weapons amd audio fix
 *
 * Revision 1.14  2006/10/30 17:03:51  southa
 * Remnants creation
 *
 * Revision 1.13  2006/10/17 11:05:55  southa
 * Expiry events
 *
 * Revision 1.12  2006/10/12 22:04:47  southa
 * Collision events
 *
 * Revision 1.11  2006/10/03 14:06:51  southa
 * Khazi and projectile creation
 *
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

#include "AdanaxisPiece.h"

#include "API/mushMushCollision.h"
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
    
    virtual void MessageConsume(MushGameLogic& ioLogic, const MushGameMessage& inMessage);
    
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
    Mushware::tVal m_acceleration; //:readwrite
    Mushware::tVal m_speedLimit; //:readwrite
    
    static Mushware::tRubyValue m_rubyKlass; // Must duplicate this in derived classes
    
//%classPrototypes {
public:
    const std::string& Owner(void) const { return m_owner; }
    void OwnerSet(const std::string& inValue) { m_owner=inValue; }
    const Mushware::tMsec& LifeMsec(void) const { return m_lifeMsec; }
    void LifeMsecSet(const Mushware::tMsec& inValue) { m_lifeMsec=inValue; }
    const Mushware::tMsec& LaunchMsec(void) const { return m_launchMsec; }
    void LaunchMsecSet(const Mushware::tMsec& inValue) { m_launchMsec=inValue; }
    const Mushware::tVal& Acceleration(void) const { return m_acceleration; }
    void AccelerationSet(const Mushware::tVal& inValue) { m_acceleration=inValue; }
    const Mushware::tVal& SpeedLimit(void) const { return m_speedLimit; }
    void SpeedLimitSet(const Mushware::tVal& inValue) { m_speedLimit=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } MtjV2+K9DhQWeffIwjdnFw
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
