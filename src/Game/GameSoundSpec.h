//%includeGuardStart {
#ifndef GAMESOUNDSPEC_H
#define GAMESOUNDSPEC_H
//%includeGuardStart } 8VOnMjknA0Ul0JLxu/LGHQ
//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameSoundSpec.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } vIBS9nsMlDQBmD0F/COFow
/*
 * $Id$
 * $Log$
 */

#include "mushMushcore.h"

#include "mushMedia.h"

//: generate virtual standard ostream xml1
class GameSoundSpec : public MushcoreVirtualObject
{
public:
    virtual ~GameSoundSpec() {}
    
private:
    MushcoreDataRef<MediaSound> m_soundRef; //:readwrite
    Mushware::tVal m_startTime; //:readwrite
    
//%classPrototypes {
public:
    const MushcoreDataRef<MediaSound>& SoundRef(void) const { return m_soundRef; }
    void SoundRefSet(const MushcoreDataRef<MediaSound>& inValue) { m_soundRef=inValue; }
    const Mushware::tVal& StartTime(void) const { return m_startTime; }
    void StartTimeSet(const Mushware::tVal& inValue) { m_startTime=inValue; }
    virtual const char *AutoNameGet(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } gV9xDDOCWutV/QNpQOiE3g
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const GameSoundSpec& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } aHt/ahyfExz5SWuo8r+JfA
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
