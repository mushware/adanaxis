//%includeGuardStart {
#ifndef MUSHPIEDIALOGUE_H
#define MUSHPIEDIALOGUE_H
//%includeGuardStart } vZTTqgEIY46zaNcoDf7cFw
//%Header {
/*****************************************************************************
 *
 * File: src/MushPie/MushPieDialogue.h
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
//%Header } O3439YK2YoRNJklchWcyXw
/*
 * $Id: MushPieDialogue.h,v 1.4 2006/06/01 15:39:36 southa Exp $
 * $Log: MushPieDialogue.h,v $
 * Revision 1.4  2006/06/01 15:39:36  southa
 * DrawArray verification and fixes
 *
 * Revision 1.3  2005/06/20 14:30:37  southa
 * Adanaxis work
 *
 * Revision 1.2  2005/05/19 13:02:12  southa
 * Mac release work
 *
 * Revision 1.1  2005/02/10 12:34:11  southa
 * Template fixes
 *
 */

#include "MushPieStandard.h"

#include "MushPiePiece.h"
#include "MushPiePosicity.h"

#include "mushMushcore.h"
#include "mushGL.h"

//:xml1base MushPiePiece
//:generate virtual standard ostream xml1
class MushPieDialogue : public MushPiePiece
{
public:
    virtual ~MushPieDialogue();
    virtual void Render(void) const;
    virtual void Move(void);
    virtual bool ExpiredGet(void) { return m_expired; }
    virtual void TextSet(Mushware::U32 inWhich, const std::string& inStr);
    virtual void ExpireNow();

    
protected:
    //StringSpec m_currentSpec;
    //std::vector<StringSpec> m_strings;
    //std::vector<SoundSpec> m_sounds;
    //std::vector<SoundStreamSpec> m_soundStreams;
    //GLFontRef m_fontRef;
    Mushware::tVal m_age;
    bool m_expired;
    //    MushcoreScript m_script;
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
operator<<(std::ostream& ioOut, const MushPieDialogue& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } klUNqanL9CtMOSNY60GWEg
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
