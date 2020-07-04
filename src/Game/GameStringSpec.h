//%includeGuardStart {
#ifndef GAMESTRINGSPEC_H
#define GAMESTRINGSPEC_H
//%includeGuardStart } lYeCbKO0AipoYouEVf6enQ
//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameStringSpec.h
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
//%Header } +kYMA/fh2lz5Qx/naDs0pw
/*
 * $Id: GameStringSpec.h,v 1.6 2006/06/01 15:39:00 southa Exp $
 * $Log: GameStringSpec.h,v $
 * Revision 1.6  2006/06/01 15:39:00  southa
 * DrawArray verification and fixes
 *
 * Revision 1.5  2005/07/04 15:59:00  southa
 * Adanaxis work
 *
 * Revision 1.4  2005/06/20 14:30:34  southa
 * Adanaxis work
 *
 * Revision 1.3  2005/05/19 13:02:03  southa
 * Mac release work
 *
 * Revision 1.2  2005/03/25 22:04:49  southa
 * Dialogue and MushcoreIO fixes
 *
 * Revision 1.1  2005/03/25 19:13:49  southa
 * GameDialogue work
 *
 */

#include "API/mushMushcore.h"

#include "API/mushGL.h"
#include "API/mushMushMesh.h"

//:generate virtual standard ostream xml1
class GameStringSpec : public MushcoreVirtualObject
{
public:
    GameStringSpec();
    virtual ~GameStringSpec() {}
        
private:
    GLString m_string; //:readwrite :wref
    MushMeshPosticity m_posticity; //:readwrite :wref
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
    const MushMeshPosticity& Posticity(void) const { return m_posticity; }
    void PosticitySet(const MushMeshPosticity& inValue) { m_posticity=inValue; }
    // Writable reference for m_posticity
    MushMeshPosticity& PosticityWRef(void) { return m_posticity; }
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
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } ECrSpI49LDLt2PS0hhgSFA
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
