//%includeGuardStart {
#ifndef ADANAXISVOLATILEDATA_H
#define ADANAXISVOLATILEDATA_H
//%includeGuardStart } WOSmULytubQRWj1H0kbf4g
//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisVolatileData.h
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
//%Header } XrQEwpmtlp8SdmM5UHV3zg
/*
 * $Id: AdanaxisVolatileData.h,v 1.20 2007/06/14 18:55:11 southa Exp $
 * $Log: AdanaxisVolatileData.h,v $
 * Revision 1.20  2007/06/14 18:55:11  southa
 * Level and display tweaks
 *
 * Revision 1.19  2007/04/18 09:22:05  southa
 * Header and level fixes
 *
 * Revision 1.18  2007/04/16 08:41:09  southa
 * Level and header mods
 *
 * Revision 1.17  2007/03/19 16:01:36  southa
 * Damage indicators
 *
 * Revision 1.16  2007/03/16 19:50:44  southa
 * Damage indicators
 *
 * Revision 1.15  2007/03/13 18:21:37  southa
 * Scanner jamming
 *
 * Revision 1.14  2007/03/09 11:29:13  southa
 * Game end actions
 *
 * Revision 1.13  2007/03/07 16:59:44  southa
 * Khazi spawning and level ends
 *
 * Revision 1.12  2006/11/12 20:09:55  southa
 * Missile guidance
 *
 * Revision 1.11  2006/08/01 17:21:31  southa
 * River demo
 *
 * Revision 1.10  2006/07/28 16:52:20  southa
 * Options work
 *
 * Revision 1.9  2006/07/28 11:14:28  southa
 * Records for multiple spaces
 *
 * Revision 1.8  2006/07/26 16:37:21  southa
 * Options menu
 *
 * Revision 1.7  2006/07/19 10:22:16  southa
 * World objects
 *
 * Revision 1.6  2006/07/04 16:55:26  southa
 * Ruby key handling
 *
 * Revision 1.5  2006/07/02 21:08:54  southa
 * Ruby menu work
 *
 * Revision 1.4  2006/06/21 16:52:30  southa
 * Deco objects
 *
 * Revision 1.3  2006/06/01 15:38:49  southa
 * DrawArray verification and fixes
 *
 * Revision 1.2  2005/07/01 16:42:54  southa
 * Render work
 *
 * Revision 1.1  2005/06/30 14:26:35  southa
 * Adanaxis work
 *
 */

#include "AdanaxisStandard.h"
#include "AdanaxisPieceDeco.h"
#include "AdanaxisPieceWorld.h"

#include "API/mushGame.h"
#include "API/mushMushGame.h"

//:xml1base MushGameVolatileData
//:generate virtual nocopy standard ostream xml1
class AdanaxisVolatileData : public MushGameVolatileData
{
public:
    typedef AdanaxisPieceDeco tDeco;
    typedef MushcoreMaptor<tDeco> tDecoList;
    typedef AdanaxisPieceWorld tWorld;
    typedef MushcoreMaptor<tWorld> tWorldList;
    AdanaxisVolatileData();
    virtual ~AdanaxisVolatileData() {}
    
    void DamageIconSet(Mushware::U32 inIndex, Mushware::tVal inValue) { MushcoreUtil::BoundsCheck(inIndex, m_damageIcons.size()); m_damageIcons[inIndex] = inValue; }
    Mushware::tVal DamageIcon(Mushware::U32 inIndex) const { MushcoreUtil::BoundsCheck(inIndex, m_damageIcons.size()); return m_damageIcons[inIndex]; }
    Mushware::U32 NumDamageIcons(void) const { return m_damageIcons.size(); }
    
private:
    tDecoList m_decoList; //:read :wref
    tWorldList m_worldList; //:read :wref
    std::auto_ptr<MushRenderMesh> m_aRenderMesh; //:read :wref
	MushRubyValue m_rubySpace; //:readwrite
    Mushware::tVal m_brightness; //:readwrite
    bool m_showFps; //:readwrite
    bool m_scannerOn; //:readwrite
    std::string m_playerTargetID; //:readwrite
    Mushware::U32 m_khaziCount; //:readwrite
    Mushware::U32 m_khaziRedCount; //:readwrite
    Mushware::U32 m_khaziBlueCount; //:readwrite
    Mushware::U32 m_khaziRedTotal; //:readwrite
    Mushware::U32 m_khaziBlueTotal; //:readwrite
    Mushware::U32 m_jammerCount; //:readwrite
    Mushware::U32 m_playerCount; //:readwrite
    std::vector<Mushware::tVal> m_damageIcons;
    
//%classPrototypes {
public:
    const tDecoList& DecoList(void) const { return m_decoList; }
    // Writable reference for m_decoList
    tDecoList& DecoListWRef(void) { return m_decoList; }
    const tWorldList& WorldList(void) const { return m_worldList; }
    // Writable reference for m_worldList
    tWorldList& WorldListWRef(void) { return m_worldList; }
    const std::auto_ptr<MushRenderMesh>& ARenderMesh(void) const { return m_aRenderMesh; }
    // Writable reference for m_aRenderMesh
    std::auto_ptr<MushRenderMesh>& ARenderMeshWRef(void) { return m_aRenderMesh; }
    const MushRubyValue& RubySpace(void) const { return m_rubySpace; }
    void RubySpaceSet(const MushRubyValue& inValue) { m_rubySpace=inValue; }
    const Mushware::tVal& Brightness(void) const { return m_brightness; }
    void BrightnessSet(const Mushware::tVal& inValue) { m_brightness=inValue; }
    const bool& ShowFps(void) const { return m_showFps; }
    void ShowFpsSet(const bool& inValue) { m_showFps=inValue; }
    const bool& ScannerOn(void) const { return m_scannerOn; }
    void ScannerOnSet(const bool& inValue) { m_scannerOn=inValue; }
    const std::string& PlayerTargetID(void) const { return m_playerTargetID; }
    void PlayerTargetIDSet(const std::string& inValue) { m_playerTargetID=inValue; }
    const Mushware::U32& KhaziCount(void) const { return m_khaziCount; }
    void KhaziCountSet(const Mushware::U32& inValue) { m_khaziCount=inValue; }
    const Mushware::U32& KhaziRedCount(void) const { return m_khaziRedCount; }
    void KhaziRedCountSet(const Mushware::U32& inValue) { m_khaziRedCount=inValue; }
    const Mushware::U32& KhaziBlueCount(void) const { return m_khaziBlueCount; }
    void KhaziBlueCountSet(const Mushware::U32& inValue) { m_khaziBlueCount=inValue; }
    const Mushware::U32& KhaziRedTotal(void) const { return m_khaziRedTotal; }
    void KhaziRedTotalSet(const Mushware::U32& inValue) { m_khaziRedTotal=inValue; }
    const Mushware::U32& KhaziBlueTotal(void) const { return m_khaziBlueTotal; }
    void KhaziBlueTotalSet(const Mushware::U32& inValue) { m_khaziBlueTotal=inValue; }
    const Mushware::U32& JammerCount(void) const { return m_jammerCount; }
    void JammerCountSet(const Mushware::U32& inValue) { m_jammerCount=inValue; }
    const Mushware::U32& PlayerCount(void) const { return m_playerCount; }
    void PlayerCountSet(const Mushware::U32& inValue) { m_playerCount=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } Fb82n61Qlfr0MDYO+nDY1g
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const AdanaxisVolatileData& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } f8H5o1BtmcymrIW1lWAphw
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
