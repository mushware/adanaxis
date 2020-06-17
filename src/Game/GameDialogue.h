//%includeGuardStart {
#ifndef GAMEDIALOGUE_H
#define GAMEDIALOGUE_H
//%includeGuardStart } tQ9gbrAH/MS6DEfkfqIY2w
//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameDialogue.h
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
//%Header } hXzDhF4stLBXJ1WQauupCw
/*
 * $Id: GameDialogue.h,v 1.27 2006/06/01 15:38:57 southa Exp $
 * $Log: GameDialogue.h,v $
 * Revision 1.27  2006/06/01 15:38:57  southa
 * DrawArray verification and fixes
 *
 * Revision 1.26  2005/07/02 00:42:37  southa
 * Conditioning tweaks
 *
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
    std::vector<GameSoundSpec> m_voices;
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
