//%includeGuardStart {
#ifndef GAMEDIALOGUE_H
#define GAMEDIALOGUE_H
//%includeGuardStart } tQ9gbrAH/MS6DEfkfqIY2w
//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameDialogue.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } lXlUcR6hArOlUOSzmITEkA
/*
 * $Id: GameDialogue.h,v 1.22 2005/03/25 22:04:49 southa Exp $
 * $Log: GameDialogue.h,v $
 * Revision 1.22  2005/03/25 22:04:49  southa
 * Dialogue and MushcoreIO fixes
 *
 * Revision 1.21  2005/03/25 19:13:49  southa
 * GameDialogue work
 *
 */

#include "mushMushcore.h"

#include "mushGL.h"
#include "mushMushPie.h"
#include "mushMedia.h"

#include "GameStringSpec.h"
#include "GameSoundSpec.h"
#include "GameSoundStreamSpec.h"

//:generate standard ostream xml1
class GameDialogue : public MushcoreVirtualObject
{
public:
    GameDialogue();
    virtual ~GameDialogue() {}
    virtual void Render(void) const;
    virtual void Move(void);
    virtual bool ExpiredGet(void) { return m_expired; }
    virtual void TextSet(Mushware::U32 inWhich, const std::string& inStr);
    virtual void ExpireNow();
    
    static MushcoreScalar GameDialogueLoad(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static void Install(void);

private:
    std::vector<GameStringSpec> m_strings;
    std::vector<GameSoundSpec> m_sounds;
    std::vector<GameSoundStreamSpec> m_soundStreams;
    std::string m_killSound;
    Mushware::tVal m_age;
    bool m_expired;
//%classPrototypes {
public:
    const char *AutoNameGet(void) const;
    MushcoreVirtualObject *AutoClone(void) const;
    MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    void AutoPrint(std::ostream& ioOut) const;
    bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } +dlp9iU5VdVlU6oxJ9+vRg
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const GameDialogue& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } 8PYhO8hT9OSq4VBavHyFPA
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
