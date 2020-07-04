//%includeGuardStart {
#ifndef MEDIAAUDIOCHANNELDEF_H
#define MEDIAAUDIOCHANNELDEF_H
//%includeGuardStart } qtX3xGLpkXjLsPrE7ZiS7w
//%Header {
/*****************************************************************************
 *
 * File: src/Media/MediaAudioChannelDef.h
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
//%Header } H5ULFxOhkt1qG5sXJuGO/Q
/*
 * $Id: MediaAudioChannelDef.h,v 1.2 2006/12/11 15:01:48 southa Exp $
 * $Log: MediaAudioChannelDef.h,v $
 * Revision 1.2  2006/12/11 15:01:48  southa
 * Snapshot
 *
 * Revision 1.1  2006/12/11 13:28:23  southa
 * Snapshot
 *
 */

#include "MediaStandard.h"

//:generate virtual standard ostream xml1
class MediaAudioChannelDef : public MushcoreVirtualObject
{
public:
    enum
    {
        kActivityInvalid,
        kActivityIdle,
        kActivityPlaying
    };

    MediaAudioChannelDef();

private:
    Mushware::U32 m_activity; //:readwrite
    Mushware::tVal m_volume; //:readwrite
    Mushware::t4Val m_position; //:readwrite
    bool m_positional; //:readwrite
    bool m_loop; //:readwrite
    bool m_voice; //:readwrite
    
//%classPrototypes {
public:
    const Mushware::U32& Activity(void) const { return m_activity; }
    void ActivitySet(const Mushware::U32& inValue) { m_activity=inValue; }
    const Mushware::tVal& Volume(void) const { return m_volume; }
    void VolumeSet(const Mushware::tVal& inValue) { m_volume=inValue; }
    const Mushware::t4Val& Position(void) const { return m_position; }
    void PositionSet(const Mushware::t4Val& inValue) { m_position=inValue; }
    const bool& Positional(void) const { return m_positional; }
    void PositionalSet(const bool& inValue) { m_positional=inValue; }
    const bool& Loop(void) const { return m_loop; }
    void LoopSet(const bool& inValue) { m_loop=inValue; }
    const bool& Voice(void) const { return m_voice; }
    void VoiceSet(const bool& inValue) { m_voice=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } KPq16VQdmmErseeau90Q6A
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MediaAudioChannelDef& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } /c83vxXnbNYxRT5u//qRwA
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
