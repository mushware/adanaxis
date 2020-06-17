//%includeGuardStart {
#ifndef GAMESOUNDSPEC_H
#define GAMESOUNDSPEC_H
//%includeGuardStart } 8VOnMjknA0Ul0JLxu/LGHQ
//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameSoundSpec.h
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
//%Header } 3fXo8qoaKVQ2q311FTqGQw
/*
 * $Id: GameSoundSpec.h,v 1.4 2006/06/01 15:39:00 southa Exp $
 * $Log: GameSoundSpec.h,v $
 * Revision 1.4  2006/06/01 15:39:00  southa
 * DrawArray verification and fixes
 *
 * Revision 1.3  2005/06/20 14:30:34  southa
 * Adanaxis work
 *
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
