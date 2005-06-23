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
 * $Id: MushGameMessageJoinRequest.h,v 1.2 2005/06/22 20:01:59 southa Exp $
 * $Log: MushGameMessageJoinRequest.h,v $
 * Revision 1.2  2005/06/22 20:01:59  southa
 * MushGame link work
 *
 * Revision 1.1  2005/06/20 14:30:36  southa
 * Adanaxis work
 *
 */

#include "MushGameStandard.h"
#include "MushGameMessage.h"

//:xml1base MushGameMessage
//:generate virtual standard ostream xml1
class MushGameMessageJoinRequest : public MushGameMessage
{
public:
    explicit MushGameMessageJoinRequest(const std::string& inID = "") : MushGameMessage(inID) {}
    virtual ~MushGameMessageJoinRequest() {}
    
private:
    std::string m_clientName; //:readwrite
    std::string m_playerName; //:readwrite
    std::string m_packageID; //:readwrite

//%classPrototypes {
public:
    const std::string& ClientName(void) const { return m_clientName; }
    void ClientNameSet(const std::string& inValue) { m_clientName=inValue; }
    const std::string& PlayerName(void) const { return m_playerName; }
    void PlayerNameSet(const std::string& inValue) { m_playerName=inValue; }
    const std::string& PackageID(void) const { return m_packageID; }
    void PackageIDSet(const std::string& inValue) { m_packageID=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } YLWjpsVnWAdA8KwwFEjhjA
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
