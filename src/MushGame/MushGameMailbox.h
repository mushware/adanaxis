//%includeGuardStart {
#ifndef MUSHGAMEMAILBOX_H
#define MUSHGAMEMAILBOX_H
//%includeGuardStart } BFwxta+0c2eXNnB5ocfSlA
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameMailbox.h
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
//%Header } kZyrudAIZwyg5fWAiaE1qw
/*
 * $Id: MushGameMailbox.h,v 1.7 2006/06/01 15:39:23 southa Exp $
 * $Log: MushGameMailbox.h,v $
 * Revision 1.7  2006/06/01 15:39:23  southa
 * DrawArray verification and fixes
 *
 * Revision 1.6  2005/07/06 19:08:27  southa
 * Adanaxis control work
 *
 * Revision 1.5  2005/06/23 11:58:28  southa
 * MushGame link work
 *
 * Revision 1.4  2005/06/22 20:01:59  southa
 * MushGame link work
 *
 * Revision 1.3  2005/06/20 16:14:31  southa
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
class MushGameMailbox : public MushcoreVirtualObject
{
public:
    MushGameMailbox() : m_messageCount(0), m_messageLimit(1000) {}
    virtual ~MushGameMailbox();
    virtual void Give(MushGameMessage *iopMessage);
    virtual bool TakeIfAvailable(MushGameMessage *& iopMessage);
    virtual bool TakeIfAvailable(std::auto_ptr<MushGameMessage>& ioaMessage);
    virtual bool IsEmpty(void) { return m_deque.empty(); }
    virtual void DiscardAll(void);
    
private:
    MushcoreDataRef<MushGameAddress> m_srcAddrRef; //:xmlignore :readwrite
    std::deque<MushGameMessage *> m_deque;
    Mushware::U32 m_messageCount; //:readwrite
    Mushware::U32 m_messageLimit; //:readwrite
    
//%classPrototypes {
public:
    const MushcoreDataRef<MushGameAddress>& SrcAddrRef(void) const { return m_srcAddrRef; }
    void SrcAddrRefSet(const MushcoreDataRef<MushGameAddress>& inValue) { m_srcAddrRef=inValue; }
    const Mushware::U32& MessageCount(void) const { return m_messageCount; }
    void MessageCountSet(const Mushware::U32& inValue) { m_messageCount=inValue; }
    const Mushware::U32& MessageLimit(void) const { return m_messageLimit; }
    void MessageLimitSet(const Mushware::U32& inValue) { m_messageLimit=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } Jl57Dk8ApazrafbogACMNg
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushGameMailbox& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } CJpY1w5JjdGfBhBU2h74gg
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
