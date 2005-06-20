//%includeGuardStart {
#ifndef GAMESOUNDSPEC_H
#define GAMESOUNDSPEC_H
//%includeGuardStart } 8VOnMjknA0Ul0JLxu/LGHQ
//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameSoundSpec.h
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
//%Header } FuIc9TOssVkth72yZpItlg
/*
 * $Id: GameSoundSpec.h,v 1.2 2005/05/19 13:02:03 southa Exp $
 * $Log: GameSoundSpec.h,v $
 * Revision 1.2  2005/05/19 13:02:03  southa
 * Mac release work
 *
 * Revision 1.1  2005/03/25 19:13:49  southa
 * GameDialogue work
 *
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
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } 3niTv5bvjf9z4kFJigspzg
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
