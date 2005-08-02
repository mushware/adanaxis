//%includeGuardStart {
#ifndef ADANAXISCONFIG_H
#define ADANAXISCONFIG_H
//%includeGuardStart } U1cBAMbPpT8Nfh33tQ1jHA
//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisConfig.h
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
//%Header } 76Z23tD76SliFedbLacn1Q
/*
 * $Id: AdanaxisConfig.h,v 1.7 2005/07/11 16:37:46 southa Exp $
 * $Log: AdanaxisConfig.h,v $
 * Revision 1.7  2005/07/11 16:37:46  southa
 * Uplink control work
 *
 * Revision 1.6  2005/07/06 19:08:26  southa
 * Adanaxis control work
 *
 * Revision 1.5  2005/07/02 00:42:36  southa
 * Conditioning tweaks
 *
 * Revision 1.4  2005/06/20 14:30:33  southa
 * Adanaxis work
 *
 * Revision 1.3  2005/06/14 20:39:40  southa
 * Adanaxis work
 *
 * Revision 1.2  2005/06/14 13:25:33  southa
 * Adanaxis work
 *
 * Revision 1.1  2005/06/13 17:34:54  southa
 * Adanaxis creation
 *
 */

#include "AdanaxisStandard.h"

#include "API/mushMushGame.h"

//:xml1base MushGameConfigBase
//:generate standard ostream xml1
class AdanaxisConfig : public MushGameConfigBase
{
public:
    enum
    {
        kAxisX = 0,
        kAxisY = 1,
        kAxisZ = 2,
        kAxisW = 3,
        kAxisXY = 4,
        kAxisZW = 5,
        kAxisXZ = 6,
        kAxisYW = 7,
        kAxisXW = 8,
        kAxisYZ = 9,
        kNumAxes = 10
    };
    
    enum
    {
        kKeyFire = 0,
        kNumKeys
    };
    
    AdanaxisConfig();
    
    virtual void ToDefaultSet(void);
    virtual void AxesToDefaultSet(void);
    virtual void KeysToDefaultSet(void);
    virtual void AutoInputPrologue(MushcoreXMLIStream& ioIn);
    virtual void AutoInputEpilogue(MushcoreXMLIStream& ioIn);
    virtual void AutoOutputPrologue(MushcoreXMLOStream& ioOut) const;
    const MushGameAxisDef& AxisDefs(Mushware::U32 inAxisDefNum) const { MushcoreUtil::BoundsCheck(inAxisDefNum, m_axisDefs.size()); return m_axisDefs[inAxisDefNum]; }
    const MushGameKeyDef& KeyDefs(Mushware::U32 inKeyDefNum) const { MushcoreUtil::BoundsCheck(inKeyDefNum, m_keyDefs.size()); return m_keyDefs[inKeyDefNum]; }

private:
    enum
    {
        kVersion = 200506014,
    };
    
    std::vector<MushGameAxisDef> m_axisDefs; //:read
    std::vector<MushGameKeyDef> m_keyDefs; //:read
    Mushware::U32 m_displayMode; //:readwrite
    Mushware::tMsec m_recordTime; //:readwrite
    
//%classPrototypes {
public:
    const std::vector<MushGameAxisDef>& AxisDefs(void) const { return m_axisDefs; }
    const std::vector<MushGameKeyDef>& KeyDefs(void) const { return m_keyDefs; }
    const Mushware::U32& DisplayMode(void) const { return m_displayMode; }
    void DisplayModeSet(const Mushware::U32& inValue) { m_displayMode=inValue; }
    const Mushware::tMsec& RecordTime(void) const { return m_recordTime; }
    void RecordTimeSet(const Mushware::tMsec& inValue) { m_recordTime=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } 7/bmsZAzY6gfl7rJTjhB/Q
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const AdanaxisConfig& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } fTUu9zxKe0/BLgROv3OE8g

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
