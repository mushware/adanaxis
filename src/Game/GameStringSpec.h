//%includeGuardStart {
#ifndef GAMESTRINGSPEC_H
#define GAMESTRINGSPEC_H
//%includeGuardStart } lYeCbKO0AipoYouEVf6enQ
//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameStringSpec.h
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
//%Header } 9Me/nJIZR1YxOvHlqu+ysw
/*
 * $Id: GameStringSpec.h,v 1.2 2005/03/25 22:04:49 southa Exp $
 * $Log: GameStringSpec.h,v $
 * Revision 1.2  2005/03/25 22:04:49  southa
 * Dialogue and MushcoreIO fixes
 *
 * Revision 1.1  2005/03/25 19:13:49  southa
 * GameDialogue work
 *
 */

#include "mushMushcore.h"

#include "mushGL.h"
#include "mushMushPie.h"

//:generate virtual standard ostream xml1
class GameStringSpec : public MushcoreVirtualObject
{
public:
    virtual ~GameStringSpec() {}
        
private:
    GLString m_string; //:readwrite :wref
    MushPiePosicity m_posicity; //:readwrite :wref
    GLColour m_startColour; //:readwrite
    GLColour m_midColour; //:readwrite
    GLColour m_endColour; //:readwrite
    Mushware::tVal m_startTime; //:readwrite
    Mushware::tVal m_endTime; //:readwrite
    Mushware::tVal m_fadeTime; //:readwrite
    Mushware::tVal m_startSize; //:readwrite
    Mushware::tVal m_midSize; //:readwrite
    Mushware::tVal m_endSize; //:readwrite
//%classPrototypes {
public:
    const GLString& String(void) const { return m_string; }
    void StringSet(const GLString& inValue) { m_string=inValue; }
    // Writable reference for m_string
    GLString& StringWRef(void) { return m_string; }
    const MushPiePosicity& Posicity(void) const { return m_posicity; }
    void PosicitySet(const MushPiePosicity& inValue) { m_posicity=inValue; }
    // Writable reference for m_posicity
    MushPiePosicity& PosicityWRef(void) { return m_posicity; }
    const GLColour& StartColour(void) const { return m_startColour; }
    void StartColourSet(const GLColour& inValue) { m_startColour=inValue; }
    const GLColour& MidColour(void) const { return m_midColour; }
    void MidColourSet(const GLColour& inValue) { m_midColour=inValue; }
    const GLColour& EndColour(void) const { return m_endColour; }
    void EndColourSet(const GLColour& inValue) { m_endColour=inValue; }
    const Mushware::tVal& StartTime(void) const { return m_startTime; }
    void StartTimeSet(const Mushware::tVal& inValue) { m_startTime=inValue; }
    const Mushware::tVal& EndTime(void) const { return m_endTime; }
    void EndTimeSet(const Mushware::tVal& inValue) { m_endTime=inValue; }
    const Mushware::tVal& FadeTime(void) const { return m_fadeTime; }
    void FadeTimeSet(const Mushware::tVal& inValue) { m_fadeTime=inValue; }
    const Mushware::tVal& StartSize(void) const { return m_startSize; }
    void StartSizeSet(const Mushware::tVal& inValue) { m_startSize=inValue; }
    const Mushware::tVal& MidSize(void) const { return m_midSize; }
    void MidSizeSet(const Mushware::tVal& inValue) { m_midSize=inValue; }
    const Mushware::tVal& EndSize(void) const { return m_endSize; }
    void EndSizeSet(const Mushware::tVal& inValue) { m_endSize=inValue; }
    virtual const char *AutoNameGet(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } vCSDvHm6AGkXbT7eTOwvMw
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const GameStringSpec& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } D3yjR3svIPsn9R+m3ZXhfQ
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
