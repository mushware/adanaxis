//%includeGuardStart {
#ifndef MUSHGAMEMESSAGECONTROLINFO_H
#define MUSHGAMEMESSAGECONTROLINFO_H
//%includeGuardStart } gCGkj9mJmJXi0VgLnk9jXQ
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameMessageControlInfo.h
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
//%Header } hXDPerqDEMtxwpfpU4CQ3A
/*
 * $Id: MushGameMessageControlInfo.h,v 1.3 2006/06/01 15:39:24 southa Exp $
 * $Log: MushGameMessageControlInfo.h,v $
 * Revision 1.3  2006/06/01 15:39:24  southa
 * DrawArray verification and fixes
 *
 * Revision 1.2  2005/07/11 16:37:46  southa
 * Uplink control work
 *
 * Revision 1.1  2005/07/06 19:08:27  southa
 * Adanaxis control work
 *
 */

#include "MushGameStandard.h"

#include "MushGameMessage.h"

//:xml1base MushGameMessage
//:generate virtual standard ostream xml1
class MushGameMessageControlInfo : public MushGameMessage
{
public:
    typedef std::pair<Mushware::U32, Mushware::tVal> tAxisEvent;
    typedef std::pair<Mushware::U32, bool> tKeyEvent;
    
    explicit MushGameMessageControlInfo(const std::string& inID = "") : MushGameMessage(inID) {}
    virtual ~MushGameMessageControlInfo() {}
    
private:
    Mushware::tMsec m_timestamp; //:readwrite
    std::vector<tAxisEvent> m_axisEvents; //:read :wref
    std::vector<tKeyEvent> m_keyEvents; //:read :wref
//%classPrototypes {
public:
    const Mushware::tMsec& Timestamp(void) const { return m_timestamp; }
    void TimestampSet(const Mushware::tMsec& inValue) { m_timestamp=inValue; }
    const std::vector<tAxisEvent>& AxisEvents(void) const { return m_axisEvents; }
    // Writable reference for m_axisEvents
    std::vector<tAxisEvent>& AxisEventsWRef(void) { return m_axisEvents; }
    const std::vector<tKeyEvent>& KeyEvents(void) const { return m_keyEvents; }
    // Writable reference for m_keyEvents
    std::vector<tKeyEvent>& KeyEventsWRef(void) { return m_keyEvents; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } PkvSklsOzytLUcmkPGKkJA
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushGameMessageControlInfo& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } mMVFEAYvgk8lbOhsC+U+2g
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
