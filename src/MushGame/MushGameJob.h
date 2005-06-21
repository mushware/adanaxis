//%includeGuardStart {
#ifndef MUSHGAMEJOB_H
#define MUSHGAMEJOB_H
//%includeGuardStart } VOJcgDgNeH1hnRUnE//qVA
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameJob.h
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
//%Header } iI4TY+ZqKRCRDUBPoHinSg
/*
 * $Id$
 * $Log$
 */

#include "MushGameStandard.h"

#include "MushGameReceiver.h"

class MushGameData;

//:generate standard ostream xml1
class MushGameJob : public MushGameReceiver, public MushcoreVirtualObject
{
public:
    MushGameJob();
    explicit MushGameJob(const MushcoreDataRef<MushGameData>& inDataRef);
    virtual ~MushGameJob() {}

    virtual void MessageConsume(MushGameMailbox& outReplyBox, const MushGameMessage& inMessage);

protected:
    virtual MushGameData& Data(void) { return m_dataRef.WRef(); }
    
private:
    bool m_shouldWake; //:readwrite
    bool m_complete; //:readwrite
    Mushware::U32 m_wakeTime; //:readwrite
    MushcoreDataRef<MushGameData> m_dataRef;
    
//%classPrototypes {
public:
    const bool& ShouldWake(void) const { return m_shouldWake; }
    void ShouldWakeSet(const bool& inValue) { m_shouldWake=inValue; }
    const bool& Complete(void) const { return m_complete; }
    void CompleteSet(const bool& inValue) { m_complete=inValue; }
    const Mushware::U32& WakeTime(void) const { return m_wakeTime; }
    void WakeTimeSet(const Mushware::U32& inValue) { m_wakeTime=inValue; }
    const char *AutoName(void) const;
    MushcoreVirtualObject *AutoClone(void) const;
    MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    void AutoPrint(std::ostream& ioOut) const;
    bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } iYwJdmB4FZugbO9+NXiqCA
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
