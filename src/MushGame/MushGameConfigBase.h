//%includeGuardStart {
#ifndef MUSHGAMECONFIGBASE_H
#define MUSHGAMECONFIGBASE_H
//%includeGuardStart } zQu2zIPg08TdUfi/So0AiQ
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameConfigBase.h
 *
 * Author: Andy Southgate 2002-2007
 *
 * This file contains original work by Andy Southgate.  The author and his
 * employer (Mushware Limited) irrevocably waive all of their copyright rights
 * vested in this particular version of this file to the furthest extent
 * permitted.  The author and Mushware Limited also irrevocably waive any and
 * all of their intellectual property rights arising from said file and its
 * creation that would otherwise restrict the rights of any party to use and/or
 * distribute the use of, the techniques and methods used herein.  A written
 * waiver can be obtained via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } Z5QT+HDEtycAF4WkJtjh4g
/*
 * $Id: MushGameConfigBase.h,v 1.4 2006/07/28 16:52:23 southa Exp $
 * $Log: MushGameConfigBase.h,v $
 * Revision 1.4  2006/07/28 16:52:23  southa
 * Options work
 *
 * Revision 1.3  2006/07/26 16:37:23  southa
 * Options menu
 *
 * Revision 1.2  2006/06/01 15:39:20  southa
 * DrawArray verification and fixes
 *
 * Revision 1.1  2005/06/14 20:39:41  southa
 * Adanaxis work
 *
 */

#include "MushGameStandard.h"

//:generate virtual ostream xml1
class MushGameConfigBase : public MushcoreVirtualObject
{
public:
    MushGameConfigBase();
    virtual void ToDefaultSet(void);
    virtual void AutoInputPrologue(MushcoreXMLIStream& ioIn);
    virtual void AutoOutputPrologue(MushcoreXMLOStream& ioOut) const;
    
private:
    Mushware::U32 m_version; //:readwrite
    Mushware::U32 m_textureDetail; //:readwrite
    Mushware::U32 m_audioVolume; //:readwrite
    Mushware::U32 m_musicVolume; //:readwrite
    Mushware::U32 m_voiceVolume; //:readwrite
    Mushware::tVal m_mouseSensitivity; //:readwrite
    Mushware::tVal m_brightness; //:readwrite
    
    // psuedo-config
    Mushware::U32 m_safeMode; //:readwrite
    
//%classPrototypes {
public:
    const Mushware::U32& Version(void) const { return m_version; }
    void VersionSet(const Mushware::U32& inValue) { m_version=inValue; }
    const Mushware::U32& TextureDetail(void) const { return m_textureDetail; }
    void TextureDetailSet(const Mushware::U32& inValue) { m_textureDetail=inValue; }
    const Mushware::U32& AudioVolume(void) const { return m_audioVolume; }
    void AudioVolumeSet(const Mushware::U32& inValue) { m_audioVolume=inValue; }
    const Mushware::U32& MusicVolume(void) const { return m_musicVolume; }
    void MusicVolumeSet(const Mushware::U32& inValue) { m_musicVolume=inValue; }
    const Mushware::U32& VoiceVolume(void) const { return m_voiceVolume; }
    void VoiceVolumeSet(const Mushware::U32& inValue) { m_voiceVolume=inValue; }
    const Mushware::tVal& MouseSensitivity(void) const { return m_mouseSensitivity; }
    void MouseSensitivitySet(const Mushware::tVal& inValue) { m_mouseSensitivity=inValue; }
    const Mushware::tVal& Brightness(void) const { return m_brightness; }
    void BrightnessSet(const Mushware::tVal& inValue) { m_brightness=inValue; }
    const Mushware::U32& SafeMode(void) const { return m_safeMode; }
    void SafeModeSet(const Mushware::U32& inValue) { m_safeMode=inValue; }
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } lgrtmWkCD91kTefxHNuxHg
};

//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushGameConfigBase& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } 3DZUQfm9aDXA3S2kw7plyA
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
