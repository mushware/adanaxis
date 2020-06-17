//%includeGuardStart {
#ifndef MUSHGAMEJOB_H
#define MUSHGAMEJOB_H
//%includeGuardStart } VOJcgDgNeH1hnRUnE//qVA
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameJob.h
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
//%Header } YIjA+I8Zgk2Sg1DAaRb55Q
/*
 * $Id: MushGameJob.h,v 1.6 2006/06/01 15:39:22 southa Exp $
 * $Log: MushGameJob.h,v $
 * Revision 1.6  2006/06/01 15:39:22  southa
 * DrawArray verification and fixes
 *
 * Revision 1.5  2005/07/02 00:42:37  southa
 * Conditioning tweaks
 *
 * Revision 1.4  2005/06/23 13:56:58  southa
 * MushGame link work
 *
 * Revision 1.3  2005/06/22 20:01:58  southa
 * MushGame link work
 *
 * Revision 1.2  2005/06/21 15:57:48  southa
 * MushGame work
 *
 * Revision 1.1  2005/06/21 13:10:51  southa
 * MushGame work
 *
 */

#include "MushGameStandard.h"

#include "MushGameReceiver.h"

class MushGameData;
class MushGameLogic;

//:generate standard ostream xml1
class MushGameJob : public MushGameReceiver, public MushcoreVirtualObject
{
public:
    explicit MushGameJob(const std::string& inID = "");
    virtual ~MushGameJob() {}

    virtual void MessageConsume(MushGameLogic& ioLogic, const MushGameMessage& inMessage);

protected:
    
private:
    bool m_shouldWake; //:readwrite
    bool m_complete; //:readwrite
    Mushware::U32 m_wakeTime; //:readwrite
    std::string m_id; //:readwrite
    
//%classPrototypes {
public:
    const bool& ShouldWake(void) const { return m_shouldWake; }
    void ShouldWakeSet(const bool& inValue) { m_shouldWake=inValue; }
    const bool& Complete(void) const { return m_complete; }
    void CompleteSet(const bool& inValue) { m_complete=inValue; }
    const Mushware::U32& WakeTime(void) const { return m_wakeTime; }
    void WakeTimeSet(const Mushware::U32& inValue) { m_wakeTime=inValue; }
    const std::string& Id(void) const { return m_id; }
    void IdSet(const std::string& inValue) { m_id=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } gP2iRqmke68HfJx7psmP0g
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushGameJob& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } AM1BxnbmjjopfR/S6Pmvtg
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
