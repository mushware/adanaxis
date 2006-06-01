//%includeGuardStart {
#ifndef MUSHGAMEDIGEST_H
#define MUSHGAMEDIGEST_H
//%includeGuardStart } UTdLACVl8zAuBSOebfTrvQ
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameDigest.h
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
//%Header } //jfMrVcr4z7p+6iE5VODQ
/*
 * $Id: MushGameDigest.h,v 1.3 2005/06/20 16:14:30 southa Exp $
 * $Log: MushGameDigest.h,v $
 * Revision 1.3  2005/06/20 16:14:30  southa
 * Adanaxis work
 *
 * Revision 1.2  2005/06/20 14:30:36  southa
 * Adanaxis work
 *
 * Revision 1.1  2005/06/16 10:48:59  southa
 * Client/server work
 *
 */

#include "MushGameStandard.h"

#include "MushGameMessage.h"

//:generate virtual standard ostream xml1
class MushGameDigest : public MushcoreVirtualObject
{
public:
    MushGameDigest();
    virtual ~MushGameDigest() {}
    virtual void Give(MushGameMessage *iopMessage);
    virtual bool TakeIfAvailable(MushGameMessage *& iopMessage);
    
private:
    Mushware::U32 m_digestID; //:readwrite
    std::deque<MushGameMessage *> m_deque;
    
//%classPrototypes {
public:
    const Mushware::U32& DigestID(void) const { return m_digestID; }
    void DigestIDSet(const Mushware::U32& inValue) { m_digestID=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } rYWAYE1irJJ/I55hzbYJew
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
