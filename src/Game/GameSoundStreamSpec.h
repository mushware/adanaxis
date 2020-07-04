//%includeGuardStart {
#ifndef GAMESOUNDSTREAMSPEC_H
#define GAMESOUNDSTREAMSPEC_H
//%includeGuardStart } P0vrM/i8BvOU64EnFc8e2w
//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameSoundStreamSpec.h
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
//%Header } LDKS69V27qCB43p0sbJ+Fg
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
