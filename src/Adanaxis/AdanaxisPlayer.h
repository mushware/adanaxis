//%includeGuardStart {
#ifndef ADANAXISPLAYER_H
#define ADANAXISPLAYER_H
//%includeGuardStart } pviqR78wvGstFrxNtSBrLA
//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisPlayer.h
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
//%Header } zqv5sDIS/YwQOY7KGL7Rww
/*
 * $Id: AdanaxisPlayer.h,v 1.5 2005/07/07 16:54:17 southa Exp $
 * $Log: AdanaxisPlayer.h,v $
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
    
    virtual void Move(MushGameLogic& ioLogic, const Mushware::tVal inFrameslice);

    virtual void AxisDeltaHandle(Mushware::tVal inDelta, Mushware::U32 inAxisNum);
    virtual void KeyChangeHandle(MushGameLogic& ioLogic, bool inState, Mushware::U32 inKeyNum);
    virtual void ControlInfoConsume(MushGameLogic& ioLogic, const MushGameMessageControlInfo& inMessage);

private:
    std::vector<Mushware::tVal> m_lastAxes;
        
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
