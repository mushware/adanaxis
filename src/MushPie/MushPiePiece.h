//%includeGuardStart {
#ifndef MUSHPIEPIECE_H
#define MUSHPIEPIECE_H
//%includeGuardStart } 0PLScWvXTetFOnepxmZBkg
//%Header {
/*****************************************************************************
 *
 * File: src/MushPie/MushPiePiece.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } natnLnIxDQDAAFW/Brzh3g
/*
 * $Id: MushPiePiece.h,v 1.1 2004/01/02 11:57:47 southa Exp $
 * $Log: MushPiePiece.h,v $
 * Revision 1.1  2004/01/02 11:57:47  southa
 * Created
 *
 */

#include "MushPieStandard.h"

#include "MushMesh.h"

// Concrete base class for pieces containing only the mandatory elements

//:generate standard ostream xml1
class MushPiePiece : public MushcoreVirtualObject
{
public:
    enum tSleepState
    {
        kSleepStateInvalid,
        kSleepStateSleeping,
        kSleepStateAwake
    };
    
    MushPiePiece() {}
    virtual ~MushPiePiece() {}
    
protected:
        
private:
    Mushware::t3Val m_position; //:readwrite
    Mushware::t3Val m_velocity; //:readwrite
    tSleepState m_sleepState; //:readwrite
    MushcoreDataRef<Mushware::U32> m_templateRef; //:readwrite
    
//%classPrototypes {
public:
    const Mushware::t3Val& PositionGet(void) const { return m_position; }
    void PositionSet(const Mushware::t3Val& inValue) { m_position=inValue; }
    const Mushware::t3Val& VelocityGet(void) const { return m_velocity; }
    void VelocitySet(const Mushware::t3Val& inValue) { m_velocity=inValue; }
    const tSleepState& SleepStateGet(void) const { return m_sleepState; }
    void SleepStateSet(const tSleepState& inValue) { m_sleepState=inValue; }
    const MushcoreDataRef<Mushware::U32>& TemplateRefGet(void) const { return m_templateRef; }
    void TemplateRefSet(const MushcoreDataRef<Mushware::U32>& inValue) { m_templateRef=inValue; }
    virtual const char *AutoNameGet(void) const;
    virtual MushPiePiece *AutoClone(void) const;
    virtual MushPiePiece *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    void AutoPrint(std::ostream& ioOut) const;
    void AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } fSB++Z1YwICUdAjl1SHYzA
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushPiePiece& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } nfyVPwbvNF3FkNhxbB3/pw
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
