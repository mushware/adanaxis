//%includeGuardStart {
#ifndef GAMESOUNDSTREAMSPEC_H
#define GAMESOUNDSTREAMSPEC_H
//%includeGuardStart } P0vrM/i8BvOU64EnFc8e2w
//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameSoundStreamSpec.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } LE7nx2dJ1izHO8uORAMl5g
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
    virtual const char *AutoNameGet(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } 0oaYNHkBWx3eM4JHOQTVJA
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
