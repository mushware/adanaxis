//%includeGuardStart {
#ifndef MUSHPIEPIECEMOBILE_H
#define MUSHPIEPIECEMOBILE_H
//%includeGuardStart } EN3IDI1/oGAnSKUZSf9VkA
//%Header {
/*****************************************************************************
 *
 * File: src/MushPie/MushPiePieceMobile.h
 *
 * Author: Andy Southgate 2002-2006
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
//%Header } F/hKic/m36gJvD/PB79HLQ
/*
 * $Id: MushPiePieceMobile.h,v 1.7 2005/06/20 14:30:37 southa Exp $
 * $Log: MushPiePieceMobile.h,v $
 * Revision 1.7  2005/06/20 14:30:37  southa
 * Adanaxis work
 *
 * Revision 1.6  2005/05/19 13:02:13  southa
 * Mac release work
 *
 * Revision 1.5  2005/02/10 12:34:14  southa
 * Template fixes
 *
 * Revision 1.4  2005/02/01 13:40:37  southa
 * Rotating spheres and hypercube
 *
 * Revision 1.3  2004/09/27 22:42:10  southa
 * MSVC compilation fixes
 *
 * Revision 1.2  2004/01/06 00:34:56  southa
 * MushPie testing
 *
 * Revision 1.1  2004/01/04 17:02:30  southa
 * MushPie extras and MushcoreIO fixes
 *
 */

#include "MushPieStandard.h"

#include "MushPiePieceSimple.h"
#include "MushPiePosicity.h"

//:xml1base MushPiePiece
//:generate virtual ostream xml1 standard
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
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } 1oBgFruy5qHAaudtV+Hcmg
};

inline void
MushPiePieceMobile::PosSwap(void)
{
    std::swap(m_currentPosIndex, m_newPosIndex);
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
