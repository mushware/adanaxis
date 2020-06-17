//%includeGuardStart {
#ifndef MUSHGAMECONFIGBASE_H
#define MUSHGAMECONFIGBASE_H
//%includeGuardStart } zQu2zIPg08TdUfi/So0AiQ
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameConfigBase.h
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
//%Header } rUgVj8no7UQ/2o5oAfcT9A
/*
 * $Id: MushGameConfigBase.h,v 1.5 2007/04/16 18:51:00 southa Exp $
 * $Log: MushGameConfigBase.h,v $
 * Revision 1.5  2007/04/16 18:51:00  southa
 * Voice work
 *
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
    bool m_showSubtitles; //:readwrite
    
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
    const bool& ShowSubtitles(void) const { return m_showSubtitles; }
    void ShowSubtitlesSet(const bool& inValue) { m_showSubtitles=inValue; }
    const Mushware::U32& SafeMode(void) const { return m_safeMode; }
    void SafeModeSet(const Mushware::U32& inValue) { m_safeMode=inValue; }
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } RAzJztO/4EE7b4w6LMjXNw
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
