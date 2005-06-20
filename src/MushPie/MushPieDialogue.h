//%includeGuardStart {
#ifndef MUSHPIEDIALOGUE_H
#define MUSHPIEDIALOGUE_H
//%includeGuardStart } vZTTqgEIY46zaNcoDf7cFw
//%Header {
/*****************************************************************************
 *
 * File: src/MushPie/MushPieDialogue.h
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
//%Header } JVAkXflC2hfHuxD+lJLniQ
/*
 * $Id: MushPieDialogue.h,v 1.2 2005/05/19 13:02:12 southa Exp $
 * $Log: MushPieDialogue.h,v $
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
