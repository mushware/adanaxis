//%includeGuardStart {
#ifndef GAMEDIALOGUE_H
#define GAMEDIALOGUE_H
//%includeGuardStart } tQ9gbrAH/MS6DEfkfqIY2w
//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameDialogue.h
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
//%Header } iPr3iVUkIZotRXQmnn7Wiw
/*
 * $Id: GameDialogue.h,v 1.25 2005/06/20 14:30:34 southa Exp $
 * $Log: GameDialogue.h,v $
 * Revision 1.25  2005/06/20 14:30:34  southa
 * Adanaxis work
 *
 * Revision 1.24  2005/05/19 13:02:02  southa
 * Mac release work
 *
 * Revision 1.23  2005/03/28 18:59:32  southa
 * Dialogues for Tesseract Trainer
 *
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
operator<<(std::ostream& ioOut, const GameDialogue& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } 8PYhO8hT9OSq4VBavHyFPA
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
