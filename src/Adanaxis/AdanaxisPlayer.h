//%includeGuardStart {
#ifndef ADANAXISPLAYER_H
#define ADANAXISPLAYER_H
//%includeGuardStart } pviqR78wvGstFrxNtSBrLA
//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisPlayer.h
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
//%Header } YOd+oyB0mEJTT9fPv/sRpw
/*
 * $Id: AdanaxisPlayer.h,v 1.11 2006/08/01 17:21:26 southa Exp $
 * $Log: AdanaxisPlayer.h,v $
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

#include "API/mushMushGame.h"

//:xml1base MushGamePlayer
//:generate virtual standard ostream xml1
class AdanaxisPlayer : public MushGamePlayer
{
public:
    explicit AdanaxisPlayer(const std::string& inPlayerID = "");
    
    virtual void PreControl(MushGameLogic& ioLogic);
    virtual void Move(MushGameLogic& ioLogic, const Mushware::tVal inFrameslice);

    virtual void AxisDeltaHandle(Mushware::tVal inDelta, Mushware::U32 inAxisNum);
    virtual void KeyChangeHandle(MushGameLogic& ioLogic, bool inState, Mushware::U32 inKeyNum);
    virtual void ControlInfoConsume(MushGameLogic& ioLogic, const MushGameMessageControlInfo& inMessage);
    virtual void FirePieceCreate(MushGameLogic& ioLogic, const MushGameMessageFire& inMessage);
    virtual void FireConsume(MushGameLogic& ioLogic, const MushGameMessageFire& inMessage);

private:
    std::vector<Mushware::tVal> m_lastAxes;
	MushcoreDataRef<MushMesh4Mesh> m_projectileMeshRef;
	
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
operator<<(std::ostream& ioOut, const AdanaxisPlayer& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } ECrhscROcwOFmOldSSmIWQ
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
