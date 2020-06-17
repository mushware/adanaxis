//%includeGuardStart {
#ifndef ADANAXISCONFIG_H
#define ADANAXISCONFIG_H
//%includeGuardStart } U1cBAMbPpT8Nfh33tQ1jHA
//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisConfig.h
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
//%Header } XALjWU8aQ8WCjBuubaf2UA
/*
 * $Id: AdanaxisConfig.h,v 1.24 2007/06/15 12:45:49 southa Exp $
 * $Log: AdanaxisConfig.h,v $
 * Revision 1.24  2007/06/15 12:45:49  southa
 * Prerelease work
 *
 * Revision 1.23  2007/04/18 09:22:00  southa
 * Header and level fixes
 *
 * Revision 1.22  2007/04/16 08:41:07  southa
 * Level and header mods
 *
 * Revision 1.21  2007/03/20 17:31:23  southa
 * Difficulty and GL options
 *
 * Revision 1.20  2007/03/12 21:05:59  southa
 * Scanner symbols
 *
 * Revision 1.19  2007/03/09 19:50:11  southa
 * Resident textures
 *
 * Revision 1.18  2007/03/07 11:29:24  southa
 * Level permission
 *
 * Revision 1.17  2006/11/25 21:26:31  southa
 * Display mode definitions
 *
 * Revision 1.16  2006/11/02 12:23:22  southa
 * Weapon selection
 *
 * Revision 1.15  2006/08/01 17:21:23  southa
 * River demo
 *
 * Revision 1.14  2006/07/28 11:14:26  southa
 * Records for multiple spaces
 *
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
        kKeyScanner,
        kKeyWeaponPrevious,
        kKeyWeaponNext,
        kKeyWeapon0,
        kKeyWeapon9 = kKeyWeapon0 + 9,
        kNumKeys
    };
    
    enum
    {
        kDisplayXSize = 1024,
        kDisplayYSize = 768
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
    
private:
    enum
    {
        kVersion = 20070615,
    };
    
    std::vector<MushGameAxisDef> m_axisDefs; //:read
    std::vector<MushGameKeyDef> m_keyDefs; //:read
    GLModeDef m_modeDef; //:readwrite
    Mushware::U32 m_configDifficulty; //:readwrite
    Mushware::U32 m_useGLCompression; //:readwrite
    Mushware::U32 m_useGLShader; //:readwrite
    
//%classPrototypes {
public:
    const std::vector<MushGameAxisDef>& AxisDefs(void) const { return m_axisDefs; }
    const std::vector<MushGameKeyDef>& KeyDefs(void) const { return m_keyDefs; }
    const GLModeDef& ModeDef(void) const { return m_modeDef; }
    void ModeDefSet(const GLModeDef& inValue) { m_modeDef=inValue; }
    const Mushware::U32& ConfigDifficulty(void) const { return m_configDifficulty; }
    void ConfigDifficultySet(const Mushware::U32& inValue) { m_configDifficulty=inValue; }
    const Mushware::U32& UseGLCompression(void) const { return m_useGLCompression; }
    void UseGLCompressionSet(const Mushware::U32& inValue) { m_useGLCompression=inValue; }
    const Mushware::U32& UseGLShader(void) const { return m_useGLShader; }
    void UseGLShaderSet(const Mushware::U32& inValue) { m_useGLShader=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } SMAZz30YFeMMxNGRa8cY0g
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
