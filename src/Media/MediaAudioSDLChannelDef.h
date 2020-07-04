//%includeGuardStart {
#ifndef MEDIAAUDIOSDLCHANNELDEF_H
#define MEDIAAUDIOSDLCHANNELDEF_H
//%includeGuardStart } OHe1RJ+VjMQCDNKlbSVRvQ
//%Header {
/*****************************************************************************
 *
 * File: src/Media/MediaAudioSDLChannelDef.h
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
//%Header } yLPPf/Itiln0uVj5VEwM7w
/*
 * $Id: MediaAudioSDLChannelDef.h,v 1.3 2007/04/18 09:22:26 southa Exp $
 * $Log: MediaAudioSDLChannelDef.h,v $
 * Revision 1.3  2007/04/18 09:22:26  southa
 * Header and level fixes
 *
 * Revision 1.2  2006/12/11 18:54:18  southa
 * Positional audio
 *
 * Revision 1.1  2006/12/11 13:28:23  southa
 * Snapshot
 *
 */

#include "MediaStandard.h"

#include "MediaAudio.h"
#include "MediaAudioChannelDef.h"
#include "MediaSDL.h"

class MediaSound;
class MediaSoundStream;

//:xml1base MediaAudioChannelDef
//:generate virtual standard ostream xml1
class MediaAudioSDLChannelDef : public MediaAudioChannelDef
{
public:
    MediaAudioSDLChannelDef();

    MediaSound *ActiveSample(void) const { return m_pActiveSample; }
    void ActiveSampleSet(MediaSound *inpValue) { m_pActiveSample = inpValue; }

private:
    MediaSound *m_pActiveSample; //:ignore

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
operator<<(std::ostream& ioOut, const MediaAudioSDLChannelDef& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } Wu4Yxjl7Gzar0o36KJeb/w
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
