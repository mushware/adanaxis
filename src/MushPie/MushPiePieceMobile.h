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
 * $Id: MushPiePieceMobile.h,v 1.1 2004/01/04 17:02:30 southa Exp $
 * $Log: MushPiePieceMobile.h,v $
 * Revision 1.1  2004/01/04 17:02:30  southa
 * MushPie extras and MushcoreIO fixes
 *
 */

#include "MushPieStandard.h"

#include "MushPiePieceSimple.h"
#include "MushPiePosicity.h"

//:xml1base MushPiePiece
//:generate ostream xml1 standard basic
class MushPiePieceMobile : public MushPiePiece
{
public:
    MushPiePieceMobile();
    virtual ~MushPiePieceMobile() {}
    
    const MushPiePosicity& CurrentPosGet(void) const { return m_currentPosIndex?m_pos1:m_pos0; }
    const MushPiePosicity& NewPosGet(void) const { return m_newPosIndex?m_pos1:m_pos0; }
    void NewPosSet(const MushPiePosicity& inValue) { (m_newPosIndex?m_pos1:m_pos0)=inValue; }
    
    void PosSwap(void);
        
private:
    MushPiePosicity m_pos0;
    MushPiePosicity m_pos1;
    Mushware::U32 m_currentPosIndex;
    Mushware::U32 m_newPosIndex;
    
//%classPrototypes {
public:
    virtual const char *AutoNameGet(void) const;
    virtual MushPiePieceMobile *AutoClone(void) const;
    virtual MushPiePieceMobile *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    bool AutoEquals(const MushPiePieceMobile& inObj) const;
    void AutoPrint(std::ostream& ioOut) const;
    bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } glDtZguTeL3IT2tdBg1a/Q
};

inline void
MushPiePieceMobile::PosSwap(void)
{
    std::swap(m_currentPosIndex, m_newPosIndex);
};


//%inlineHeader {
inline bool
operator==(const MushPiePieceMobile& inA, const MushPiePieceMobile& inB)
{
    return inA.AutoEquals(inB);
}
inline bool
operator!=(const MushPiePieceMobile& inA, const MushPiePieceMobile& inB)
{
    return !inA.AutoEquals(inB);
}
inline std::ostream&
operator<<(std::ostream& ioOut, const MushPiePieceMobile& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } N8JAcQSg07YLIgaWXKxNvQ
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
