//%includeGuardStart {
#ifndef GAMESOUNDSTREAMSPEC_H
#define GAMESOUNDSTREAMSPEC_H
//%includeGuardStart } P0vrM/i8BvOU64EnFc8e2w
//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameSoundStreamSpec.h
 *
 * Author: Andy Southgate 2002-2005
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
//%Header } FJm8JAS+Z05eUrILOvEHlg
#include "mushMushcore.h"

#include "mushMedia.h"

//: generate virtual standard ostream xml1
class GameSoundStreamSpec : public MushcoreVirtualObject
{
public:
    virtual ~GameSoundStreamSpec() {}
    
private:
    MushcoreDataRef<MediaSoundStream> m_soundStreamRef; //:readwrite
    Mushware::U32 loop; //:readwrite
    Mushware::tVal startTime; //:readwrite
//%classPrototypes {
public:
    const MushcoreDataRef<MediaSoundStream>& SoundStreamRef(void) const { return m_soundStreamRef; }
    void SoundStreamRefSet(const MushcoreDataRef<MediaSoundStream>& inValue) { m_soundStreamRef=inValue; }
    const Mushware::U32& Loop(void) const { return loop; }
    void LoopSet(const Mushware::U32& inValue) { loop=inValue; }
    const Mushware::tVal& StartTime(void) const { return startTime; }
    void StartTimeSet(const Mushware::tVal& inValue) { startTime=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } nLrqeRA+tv6+1kro+z4rLw
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const GameSoundStreamSpec& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } oETO+5ibqapCUI8p6DtBiQ
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
