//%includeGuardStart {
#ifndef ADANAXISPIECEEFFECTOR_H
#define ADANAXISPIECEEFFECTOR_H
//%includeGuardStart } CRlHP3Q5exYgSUHkpC9S8A
//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisPieceEffector.h
 *
 * Copyright: Andy Southgate 2005-2007
 *
 * This file may be used and distributed under the terms of the Mushware
 * Software Licence version 1.3, under the terms for 'Proprietary original
 * source files'.  If not supplied with this software, a copy of the licence
 * can be obtained from Mushware Limited via http://www.mushware.com/.
 * One of your options under that licence is to use and distribute this file
 * under the terms of the GNU General Public Licence version 2.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 2V8zdOv3G5pN0LkrmNkusw
/*
 * $Id: AdanaxisPieceEffector.h,v 1.2 2006/11/14 20:28:37 southa Exp $
 * $Log: AdanaxisPieceEffector.h,v $
 * Revision 1.2  2006/11/14 20:28:37  southa
 * Added rail gun
 *
 * Revision 1.1  2006/11/03 18:46:33  southa
 * Damage effectors
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
class AdanaxisPieceEffector : public MushGamePiece, public MushCollisionPiece
{
public:
    explicit AdanaxisPieceEffector(const std::string& inID = "", const MushRubyValue& inParams = MushRubyValue());
    virtual ~AdanaxisPieceEffector();
    
    virtual void Move(MushGameLogic& ioLogic, const Mushware::tVal inFrameslice);
    virtual bool Render(MushGLJobRender& outRender, MushGameLogic& ioLogic, MushRenderMesh& inRender, const MushGameCamera& inCamera);
    
    virtual void MessageConsume(MushGameLogic& ioLogic, const MushGameMessage& inMessage);
    
    virtual const MushMesh4Mesh& CollisionMesh(void) const { return Mesh(); }
    virtual const MushMeshPosticity& CollisionPost(void) const { return Post(); }
    virtual bool CollisionIsWCylinder(void) const { return m_rail; }
    
    virtual void Load(Mushware::tRubyValue inSelf);
    virtual void Save(Mushware::tRubyValue inSelf);
    static Mushware::tRubyValue RubyCreate(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0);
    static Mushware::tRubyValue Klass(void);
    static void RubyInstall(void);
    
private:
    std::string m_owner; //:readwrite
    Mushware::tMsec m_lifeMsec; //:readwrite
    Mushware::tMsec m_launchMsec; //:readwrite
    bool m_rail; //:readwrite
    
    static Mushware::tRubyValue m_rubyKlass; // Must duplicate this in derived classes
//%classPrototypes {
public:
    const std::string& Owner(void) const { return m_owner; }
    void OwnerSet(const std::string& inValue) { m_owner=inValue; }
    const Mushware::tMsec& LifeMsec(void) const { return m_lifeMsec; }
    void LifeMsecSet(const Mushware::tMsec& inValue) { m_lifeMsec=inValue; }
    const Mushware::tMsec& LaunchMsec(void) const { return m_launchMsec; }
    void LaunchMsecSet(const Mushware::tMsec& inValue) { m_launchMsec=inValue; }
    const bool& Rail(void) const { return m_rail; }
    void RailSet(const bool& inValue) { m_rail=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } PSZu4FvT6dy/+sqPh4XLMQ
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const AdanaxisPieceEffector& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } DizxhLcDmZYcvq8ogp3+Ww
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
