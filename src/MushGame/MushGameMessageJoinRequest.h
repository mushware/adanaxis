//%includeGuardStart {
#ifndef MUSHGAMEMESSAGEJOINREQUEST_H
#define MUSHGAMEMESSAGEJOINREQUEST_H
//%includeGuardStart } kXb2eEx91MHgRkrhpuhLuA
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameMessageJoinRequest.h
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
//%Header } rXRd7F8DnvTpUWdq+trMKw
/*
 * $Id$
 * $Log$
 */

#include "MushGameStandard.h"
#include "MushGameMessage.h"

//:xml1base MushGameMessage
//:generate virtual standard ostream xml1
class MushGameMessageJoinRequest : public MushGameMessage
{
public:
    virtual ~MushGameMessageJoinRequest() {}
    
private:
    std::string m_playerName; //:read
    std::string m_packageID; //:read
//%classPrototypes {
public:
    const std::string& PlayerName(void) const { return m_playerName; }
    const std::string& PackageID(void) const { return m_packageID; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } 6ilwKmHuV/0E2QocMRSOFA
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushGameMessageJoinRequest& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } dQQUqghoRVwgk6oCtNHS0Q
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
