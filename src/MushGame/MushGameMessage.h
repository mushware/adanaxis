//%includeGuardStart {
#ifndef MUSHGAMEMESSAGE_H
#define MUSHGAMEMESSAGE_H
//%includeGuardStart } AuJtZN1+Qznoby6CEcmFkg
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameMessage.h
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
//%Header } 756M8M47RwhK0niyavwifw
/*
 * $Id: MushGameMessage.h,v 1.5 2006/06/01 15:39:24 southa Exp $
 * $Log
 */

#include "MushGameStandard.h"

#include "MushGameAddress.h"

//:generate virtual standard ostream xml1
class MushGameMessage : public MushcoreVirtualObject
{
public:
    explicit MushGameMessage(const std::string& inID = "") : m_id(inID) { ++m_instanceCounter; }
    
    MushGameMessage(const MushGameMessage& inObj) : MushcoreVirtualObject(),
        m_srcAddrRef(inObj.m_srcAddrRef),
        m_id(inObj.m_id)    
    {
            ++m_instanceCounter;
    }
    virtual ~MushGameMessage() { --m_instanceCounter; }
    
private:
    MushcoreDataRef<MushGameAddress> m_srcAddrRef; //:xmlignore :readwrite
    std::string m_id; //:readwrite
    static Mushware::S32 m_instanceCounter; //:readwrite
        
//%classPrototypes {
public:
    const MushcoreDataRef<MushGameAddress>& SrcAddrRef(void) const { return m_srcAddrRef; }
    void SrcAddrRefSet(const MushcoreDataRef<MushGameAddress>& inValue) { m_srcAddrRef=inValue; }
    const std::string& Id(void) const { return m_id; }
    void IdSet(const std::string& inValue) { m_id=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } 50R194PmRusVUXoMrok/1A
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushGameMessage& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } XHukHzRIO+OljzoePNw14w
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
