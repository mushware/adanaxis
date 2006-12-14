//%includeGuardStart {
#ifndef ADANAXISPIECEPLAYER_H
#define ADANAXISPIECEPLAYER_H
//%includeGuardStart } mkIhmpvXKy3bQw9pOPV5Gw
//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisPiecePlayer.h
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
//%Header } WMShka8Hj2wrlOceGnqYjw
/*
 * $Id: AdanaxisPiecePlayer.h,v 1.4 2006/10/30 17:03:51 southa Exp $
 * $Log: AdanaxisPiecePlayer.h,v $
 * Revision 1.4  2006/10/30 17:03:51  southa
 * Remnants creation
 *
 * Revision 1.3  2006/10/17 15:28:01  southa
 * Player collisions
 *
 * Revision 1.2  2006/10/02 20:28:10  southa
 * Object lookup and target selection
 *
 * Revision 1.1  2006/10/02 17:25:04  southa
 * Object lookup and target selection
 *
 * Revision 1.11  2006/08/01 17:21:26  southa
 * River demo
 *
 * Revision 1.10  2006/06/21 12:17:55  southa
 * Ruby object generation
 *
 * Revision 1.9  2006/06/01 15:38:48  southa
 * DrawArray verification and fixes
 *
 * Revision 1.8  2005/07/18 13:13:36  southa
 * Extrude to point and projectile mesh
 *
 * Revision 1.7  2005/07/12 12:18:17  southa
 * Projectile work
 *
 * Revision 1.6  2005/07/11 16:37:46  southa
 * Uplink control work
 *
 * Revision 1.5  2005/07/07 16:54:17  southa
 * Control tweaks
 *
 * Revision 1.4  2005/07/06 19:08:26  southa
 * Adanaxis control work
 *
 * Revision 1.3  2005/07/05 13:52:22  southa
 * Adanaxis work
 *
 * Revision 1.2  2005/06/23 17:25:24  southa
 * MushGame link work
 *
 * Revision 1.1  2005/06/20 14:46:41  southa
 * Adanaxis work
 *
 */

#include "AdanaxisStandard.h"

#include "AdanaxisPiece.h"

#include "API/mushMushCollision.h"
#include "API/mushMushGL.h"
#include "API/mushMushMesh.h"
#include "API/mushMushRender.h"

//:xml1base MushGamePiecePlayer
//:generate virtual standard ostream xml1
class AdanaxisPiecePlayer : public MushGamePiecePlayer
{
public:
    explicit AdanaxisPiecePlayer(const std::string& inID = "", const MushRubyValue& inParams = MushRubyValue());
    virtual ~AdanaxisPiecePlayer();
    
    virtual void PreControl(MushGameLogic& ioLogic);
    virtual void Move(MushGameLogic& ioLogic, const Mushware::tVal inFrameslice);

    virtual void AxisDeltaHandle(Mushware::tVal inDelta, Mushware::U32 inAxisNum);
    virtual void KeyChangeHandle(MushGameLogic& ioLogic, bool inState, Mushware::U32 inKeyNum);
    virtual void ControlInfoConsume(MushGameLogic& ioLogic, const MushGameMessageControlInfo& inMessage);
    virtual void FirePieceCreate(MushGameLogic& ioLogic, const MushGameMessageFire& inMessage);
    virtual void FireConsume(MushGameLogic& ioLogic, const MushGameMessageFire& inMessage);

    static Mushware::tRubyValue RubyCreate(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0);
    
    static Mushware::tRubyValue Klass(void);
    static void RubyInstall(void);
    
private:
    std::vector<Mushware::tVal> m_lastAxes;
    std::vector<bool> m_lastAxisValid;
	MushcoreDataRef<MushMesh4Mesh> m_projectileMeshRef;

    static Mushware::tRubyValue m_rubyKlass; // Must duplicate this in derived classes

//%classPrototypes {
public:
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } 1oBgFruy5qHAaudtV+Hcmg
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const AdanaxisPiecePlayer& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } bDdDahBZGjHq5u9heU/FPA
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
