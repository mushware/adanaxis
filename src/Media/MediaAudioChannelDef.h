//%includeGuardStart {
#ifndef MEDIAAUDIOCHANNELDEF_H
#define MEDIAAUDIOCHANNELDEF_H
//%includeGuardStart } qtX3xGLpkXjLsPrE7ZiS7w
//%Header {
/*****************************************************************************
 *
 * File: src/Media/MediaAudioChannelDef.h
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
//%Header } J5P6c5krEP/NNUoFYmok/w
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
