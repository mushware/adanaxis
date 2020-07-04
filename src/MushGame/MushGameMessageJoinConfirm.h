//%includeGuardStart {
#ifndef MUSHGAMEMESSAGEJOINCONFIRM_H
#define MUSHGAMEMESSAGEJOINCONFIRM_H
//%includeGuardStart } ncqNKv/Pw1HGEZ4QVCnOLA
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameMessageJoinConfirm.h
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
//%Header } mKXbedceJOmU/5VcLNmbhQ
/*
 * $Id: MushGameMessageJoinConfirm.h,v 1.4 2006/06/01 15:39:24 southa Exp $
 * $Log: MushGameMessageJoinConfirm.h,v $
 * Revision 1.4  2006/06/01 15:39:24  southa
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
class MushGameMessageJoinConfirm : public MushGameMessage
{
public:
    explicit MushGameMessageJoinConfirm(const std::string& inID = "") : MushGameMessage(inID) {}
    virtual ~MushGameMessageJoinConfirm() {}
    
private:
    std::string m_newPlayerID; //:readwrite
    std::string m_hostName; //:readwrite
    std::string m_playerName; //:readwrite
    std::string m_hostPackageID; //:readwrite
    
//%classPrototypes {
public:
    const std::string& NewPlayerID(void) const { return m_newPlayerID; }
    void NewPlayerIDSet(const std::string& inValue) { m_newPlayerID=inValue; }
    const std::string& HostName(void) const { return m_hostName; }
    void HostNameSet(const std::string& inValue) { m_hostName=inValue; }
    const std::string& PlayerName(void) const { return m_playerName; }
    void PlayerNameSet(const std::string& inValue) { m_playerName=inValue; }
    const std::string& HostPackageID(void) const { return m_hostPackageID; }
    void HostPackageIDSet(const std::string& inValue) { m_hostPackageID=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } ZROunlbn2p02d+AsWwVBBw
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushGameMessageJoinConfirm& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } viUsrq0dwybkoMu8vWWN6Q
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
