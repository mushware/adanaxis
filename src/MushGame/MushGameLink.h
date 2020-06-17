//%includeGuardStart {
#ifndef MUSHGAMELINK_H
#define MUSHGAMELINK_H
//%includeGuardStart } eq6oZOrSs0esIGJaMi39ug
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameLink.h
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
//%Header } jpmFpmsaLKk9DOnChgRFew
/*
 * $Id: MushGameLink.h,v 1.7 2006/06/01 15:39:23 southa Exp $
 * $Log: MushGameLink.h,v $
 * Revision 1.7  2006/06/01 15:39:23  southa
 * DrawArray verification and fixes
 *
 * Revision 1.6  2005/06/23 11:58:28  southa
 * MushGame link work
 *
 * Revision 1.5  2005/06/22 20:01:58  southa
 * MushGame link work
 *
 * Revision 1.4  2005/06/21 15:57:48  southa
 * MushGame work
 *
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

#include "MushGameAddress.h"

class MushGameLogic;
class MushGameMessage;
class MushGameMailbox;

//:generate virtual standard ostream xml1
class MushGameLink : public MushcoreVirtualObject
{
public:
    virtual ~MushGameLink() {}
    virtual void MessagesPump(MushGameLogic& ioLogic);
    virtual void SrcDestSet(const std::string& inSrcName, const std::string& inDestName);

    virtual bool OutboxSendUnlessEmpty(void);
    virtual bool InboxGetUnlessEmpty(MushGameMailbox& outMailbox);
    virtual void ToOutboxCopy(const MushGameMessage& inMessage);
    
private:
    MushcoreDataRef<MushGameAddress> m_srcAddrRef; //:readwrite :wref
    MushcoreDataRef<MushGameAddress> m_destAddrRef; //:readwrite :wref
    
//%classPrototypes {
public:
    const MushcoreDataRef<MushGameAddress>& SrcAddrRef(void) const { return m_srcAddrRef; }
    void SrcAddrRefSet(const MushcoreDataRef<MushGameAddress>& inValue) { m_srcAddrRef=inValue; }
    // Writable reference for m_srcAddrRef
    MushcoreDataRef<MushGameAddress>& SrcAddrRefWRef(void) { return m_srcAddrRef; }
    const MushcoreDataRef<MushGameAddress>& DestAddrRef(void) const { return m_destAddrRef; }
    void DestAddrRefSet(const MushcoreDataRef<MushGameAddress>& inValue) { m_destAddrRef=inValue; }
    // Writable reference for m_destAddrRef
    MushcoreDataRef<MushGameAddress>& DestAddrRefWRef(void) { return m_destAddrRef; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } YuMcpSl3FVW1enfHrZAlRQ
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushGameLink& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } lse6rc6/yrBS2SyQc7d5Hg
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
