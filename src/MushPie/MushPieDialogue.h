//%includeGuardStart {
#ifndef MUSHPIEDIALOGUE_H
#define MUSHPIEDIALOGUE_H
//%includeGuardStart } vZTTqgEIY46zaNcoDf7cFw
//%Header {
/*****************************************************************************
 *
 * File: src/MushPie/MushPieDialogue.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } aHyqXcDF+4/kUf/93xjJ9w
/*
 * $Id$
 * $Log$
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
    virtual const char *AutoNameGet(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } FwEN8XJox/Ejr30NeyHzCg
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
