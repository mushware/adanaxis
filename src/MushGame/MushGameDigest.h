//%includeGuardStart {
#ifndef MUSHGAMEDIGEST_H
#define MUSHGAMEDIGEST_H
//%includeGuardStart } UTdLACVl8zAuBSOebfTrvQ
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameDigest.h
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
//%Header } +iRpAW4o6x6kDIKGqiMxdg
/*
 * $Id$
 * $Log$
 */

#include "MushGameStandard.h"

#include "MushGameMessage.h"

//:generate virtual standard ostream xml1
class MushGameDigest : public MushcoreVirtualObject
{
public:
    MushGameDigest();
    virtual ~MushGameDigest() {}
    
private:
    Mushware::U32 m_digestID; //:readwrite
    std::vector<MushGameMessage> m_content; //:readwrite :wref
//%classPrototypes {
public:
    const Mushware::U32& DigestID(void) const { return m_digestID; }
    void DigestIDSet(const Mushware::U32& inValue) { m_digestID=inValue; }
    const std::vector<MushGameMessage>& Content(void) const { return m_content; }
    void ContentSet(const std::vector<MushGameMessage>& inValue) { m_content=inValue; }
    // Writable reference for m_content
    std::vector<MushGameMessage>& ContentWRef(void) { return m_content; }
    virtual const char *AutoNameGet(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } vFyhkRHCVPCTW3C2fNPEhA
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushGameDigest& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } RRbv32opygA93qNKNAusHw
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
