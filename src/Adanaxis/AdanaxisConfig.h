//%includeGuardStart {
#ifndef ADANAXISCONFIG_H
#define ADANAXISCONFIG_H
//%includeGuardStart } U1cBAMbPpT8Nfh33tQ1jHA
//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisConfig.h
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
//%Header } XF1bjCN2eB/qdeJZOQQkxg
/*
 * $Id: AdanaxisConfig.h,v 1.13 2006/07/26 16:37:20 southa Exp $
 * $Log: AdanaxisConfig.h,v $
 * Revision 1.13  2006/07/26 16:37:20  southa
 * Options menu
 *
 * Revision 1.12  2006/07/12 11:22:40  southa
 * Advanced control menu
 *
 * Revision 1.11  2006/07/11 19:49:03  southa
 * Control menu
 *
 * Revision 1.10  2006/06/01 15:38:46  southa
 * DrawArray verification and fixes
 *
 * Revision 1.9  2005/08/02 14:37:44  southa
 * Adanaxis control demo work
 *
 * Revision 1.8  2005/08/02 11:11:47  southa
 * Adanaxis control demo work
 *
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
        kKeyScanner = 1,
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
    MushGameAxisDef& AxisDefWRef(Mushware::U32 inAxisDefNum) { MushcoreUtil::BoundsCheck(inAxisDefNum, m_axisDefs.size()); return m_axisDefs[inAxisDefNum]; }
    MushGameKeyDef& KeyDefWRef(Mushware::U32 inKeyDefNum) { MushcoreUtil::BoundsCheck(inKeyDefNum, m_keyDefs.size()); return m_keyDefs[inKeyDefNum]; }
    void AxisDefSet(const MushGameAxisDef& inDef, Mushware::U32 inAxisDefNum) { MushcoreUtil::BoundsCheck(inAxisDefNum, m_axisDefs.size()); m_axisDefs[inAxisDefNum] = inDef; }
    void KeyDefSet(const MushGameKeyDef& inDef, Mushware::U32 inKeyDefNum) { MushcoreUtil::BoundsCheck(inKeyDefNum, m_keyDefs.size()); m_keyDefs[inKeyDefNum] = inDef; }
    Mushware::tMsec RecordTime(const std::string& inName);
    void RecordTimeSet(const std::string& inName, Mushware::tMsec inTime) { m_recordTimes[inName] = inTime; }
    
private:
    enum
    {
        kVersion = 20060728,
    };
    typedef std::map< std::string, Mushware::tMsec > tRecordTimes;
    
    std::vector<MushGameAxisDef> m_axisDefs; //:read
    std::vector<MushGameKeyDef> m_keyDefs; //:read
    Mushware::U32 m_displayMode; //:readwrite
    tRecordTimes m_recordTimes;

//%classPrototypes {
public:
    const std::vector<MushGameAxisDef>& AxisDefs(void) const { return m_axisDefs; }
    const std::vector<MushGameKeyDef>& KeyDefs(void) const { return m_keyDefs; }
    const Mushware::U32& DisplayMode(void) const { return m_displayMode; }
    void DisplayModeSet(const Mushware::U32& inValue) { m_displayMode=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } o8V20dDJ/f6CPeqLqotZNA
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
