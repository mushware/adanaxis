//%includeGuardStart {
#ifndef MUSHGAMEMESSAGEJOINREQUEST_H
#define MUSHGAMEMESSAGEJOINREQUEST_H
//%includeGuardStart } kXb2eEx91MHgRkrhpuhLuA
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameMessageJoinRequest.h
 *
 * Copyright: Andy Southgate 2002-2007, 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/
//%Header } 6yCaqT4KweAvEsnMVBmj3A
/*
 * $Id: MushGameMessageJoinRequest.h,v 1.4 2006/06/01 15:39:25 southa Exp $
 * $Log: MushGameMessageJoinRequest.h,v $
 * Revision 1.4  2006/06/01 15:39:25  southa
 * DrawArray verification and fixes
 *
 * Revision 1.3  2005/06/23 17:25:25  southa
 * MushGame link work
 *
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
