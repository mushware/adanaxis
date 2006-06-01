//%includeGuardStart {
#ifndef MUSHGAMEJOB_H
#define MUSHGAMEJOB_H
//%includeGuardStart } VOJcgDgNeH1hnRUnE//qVA
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameJob.h
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
//%Header } zW/rqa8yp3vrQbatCXTvpg
/*
 * $Id: MushGameJob.h,v 1.5 2005/07/02 00:42:37 southa Exp $
 * $Log: MushGameJob.h,v $
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
