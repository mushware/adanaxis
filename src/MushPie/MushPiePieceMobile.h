//%includeGuardStart {
#ifndef MUSHPIEPIECEMOBILE_H
#define MUSHPIEPIECEMOBILE_H
//%includeGuardStart } EN3IDI1/oGAnSKUZSf9VkA
//%Header {
/*****************************************************************************
 *
 * File: src/MushPie/MushPiePieceMobile.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } fNBxnWioPfFaM/uScT3/eA
/*
 * $Id$
 * $Log$
 */

#include "MushPieStandard.h"

#include "MushPiePieceSimple.h"
#include "MushPiePosicity.h"

//:xml1base MushPiePiece
//:generate ostream xml1 standard
class MushPiePieceMobile : public MushPiePiece
{
public:
    MushPiePieceMobile();
    virtual ~MushPiePieceMobile() {}
    
    const MushPiePosicity& CurrentPosGet(void) const { return m_pos[m_currentPosIndex]; }
    const MushPiePosicity& NewPosGet(void) const { return m_pos[m_newPosIndex]; }
    void NewPosSet(const MushPiePosicity& inValue) { m_pos[m_newPosIndex]=inValue; }
    
    void PosSwap(void);
        
private:
    enum
    {
        kPosHistorySize = 2
    };
    MushPiePosicity m_pos[kPosHistorySize];
    Mushware::U32 m_currentPosIndex;
    Mushware::U32 m_newPosIndex;
    
//%classPrototypes {
public:
    virtual const char *AutoNameGet(void) const;
    virtual MushPiePieceMobile *AutoClone(void) const;
    virtual MushPiePieceMobile *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    void AutoPrint(std::ostream& ioOut) const;
    bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } V4OuYmqsW6oh7msFI8dQdg
};

void
MushPiePieceMobile::PosSwap(void)
{
    std::swap(m_currentPosIndex, m_newPosIndex);
    MUSHCOREASSERT(m_currentPosIndex < kPosHistorySize);
    MUSHCOREASSERT(m_newPosIndex < kPosHistorySize);
};


//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushPiePieceMobile& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } TbJaPMFRML9rFgeE6oksyQ
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
