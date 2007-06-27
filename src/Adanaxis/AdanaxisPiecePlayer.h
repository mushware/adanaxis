//%includeGuardStart {
#ifndef ADANAXISPIECEPLAYER_H
#define ADANAXISPIECEPLAYER_H
//%includeGuardStart } mkIhmpvXKy3bQw9pOPV5Gw
//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisPiecePlayer.h
 *
 * Copyright: Andy Southgate 2005-2007
 *
 * This file may be used and distributed under the terms of the Mushware
 * Software Licence version 1.4, under the terms for 'Proprietary original
 * source files'.  If not supplied with this software, a copy of the licence
 * can be obtained from Mushware Limited via http://www.mushware.com/.
 * One of your options under that licence is to use and distribute this file
 * under the terms of the GNU General Public Licence version 2.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } dO0w0Nvfuqs4agZnWwM9Zg
/*
 * $Id: AdanaxisPiecePlayer.h,v 1.11 2007/06/13 14:08:48 southa Exp $
 * $Log: AdanaxisPiecePlayer.h,v $
 * Revision 1.11  2007/06/13 14:08:48  southa
 * Level 29
 *
 * Revision 1.10  2007/06/07 13:23:03  southa
 * Level 24
 *
 * Revision 1.9  2007/05/22 12:59:10  southa
 * Vortex effect on player
 *
 * Revision 1.8  2007/04/18 09:22:02  southa
 * Header and level fixes
 *
 * Revision 1.7  2007/04/16 08:41:08  southa
 * Level and header mods
 *
 * Revision 1.6  2007/03/07 16:59:44  southa
 * Khazi spawning and level ends
 *
 * Revision 1.5  2006/12/14 00:33:48  southa
 * Control fix and audio pacing
 *
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

    virtual void AxisDeltaHandle(MushGameLogic& ioLogic, Mushware::tVal inDelta, Mushware::U32 inAxisNum);
    virtual void KeyChangeHandle(MushGameLogic& ioLogic, bool inState, Mushware::U32 inKeyNum);
    virtual void ControlInfoConsume(MushGameLogic& ioLogic, const MushGameMessageControlInfo& inMessage);
    
    virtual void Load(Mushware::tRubyValue inSelf);
    virtual void Save(Mushware::tRubyValue inSelf);
    static Mushware::tRubyValue RubyCreate(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0);
    
    static Mushware::tRubyValue Klass(void);
    static void RubyInstall(void);
    
private:
    std::vector<Mushware::tVal> m_lastAxes;
    std::vector<bool> m_lastAxisValid;
	MushcoreDataRef<MushMesh4Mesh> m_projectileMeshRef;
    bool m_controlReleased; //:readwrite
    bool m_thrustReleased; //:readwrite
    
    static Mushware::tRubyValue m_rubyKlass; // Must duplicate this in derived classes

//%classPrototypes {
public:
    const bool& ControlReleased(void) const { return m_controlReleased; }
    void ControlReleasedSet(const bool& inValue) { m_controlReleased=inValue; }
    const bool& ThrustReleased(void) const { return m_thrustReleased; }
    void ThrustReleasedSet(const bool& inValue) { m_thrustReleased=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } wDA6Femhobd+J7OcG6hSOA
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
