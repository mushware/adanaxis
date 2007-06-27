//%includeGuardStart {
#ifndef MEDIAAUDIOSDLCHANNELDEF_H
#define MEDIAAUDIOSDLCHANNELDEF_H
//%includeGuardStart } OHe1RJ+VjMQCDNKlbSVRvQ
//%Header {
/*****************************************************************************
 *
 * File: src/Media/MediaAudioSDLChannelDef.h
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
//%Header } JL21oay8WaF85VbS6/8WOQ
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
