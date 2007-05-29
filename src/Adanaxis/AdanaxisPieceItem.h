//%includeGuardStart {
#ifndef ADANAXISPIECEITEM_H
#define ADANAXISPIECEITEM_H
//%includeGuardStart } GEeqJJ1SvMjMG9JQxm7Iew
//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisPieceItem.h
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
//%Header } ByFmTdqjKsHzSPC2ZgYt3A
/*
 * $Id: AdanaxisPieceItem.h,v 1.4 2007/04/18 09:22:02 southa Exp $
 * $Log: AdanaxisPieceItem.h,v $
 * Revision 1.4  2007/04/18 09:22:02  southa
 * Header and level fixes
 *
 * Revision 1.3  2006/10/30 17:03:51  southa
 * Remnants creation
 *
 * Revision 1.2  2006/10/20 15:38:52  southa
 * Item collection
 *
 * Revision 1.1  2006/10/19 15:41:36  southa
 * Item handling
 *
 */

#include "AdanaxisStandard.h"

#include "AdanaxisPiece.h"

#include "API/mushMushGL.h"
#include "API/mushMushMesh.h"
#include "API/mushMushRender.h"

//:xml1base MushGamePiece
//:generate virtual standard ostream xml1
class AdanaxisPieceItem : public MushGamePiece, public MushCollisionPiece
{
public:
    explicit AdanaxisPieceItem(const std::string& inID = "", const MushRubyValue& inParams = MushRubyValue());
    virtual ~AdanaxisPieceItem();
    
    virtual void Move(MushGameLogic& ioLogic, const Mushware::tVal inFrameSlice);
    virtual bool Render(MushGLJobRender& outRender,
                        MushGameLogic& ioLogic, MushRenderMesh& inRender, const MushGameCamera& inCamera);
    
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
    Mushware::tMsec m_creationMsec; //:readwrite
    
    static Mushware::tRubyValue m_rubyKlass; // Must duplicate this in derived classes
//%classPrototypes {
public:
    const std::string& Owner(void) const { return m_owner; }
    void OwnerSet(const std::string& inValue) { m_owner=inValue; }
    const Mushware::tMsec& LifeMsec(void) const { return m_lifeMsec; }
    void LifeMsecSet(const Mushware::tMsec& inValue) { m_lifeMsec=inValue; }
    const Mushware::tMsec& CreationMsec(void) const { return m_creationMsec; }
    void CreationMsecSet(const Mushware::tMsec& inValue) { m_creationMsec=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } 9X9ffiZuoqSSscug7FGgYQ
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const AdanaxisPieceItem& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } 4R2w5tefSPYQ87TTTPeWNg
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
