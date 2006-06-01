//%includeGuardStart {
#ifndef MUSHGAMEJOBPLAYERCREATE_H
#define MUSHGAMEJOBPLAYERCREATE_H
//%includeGuardStart } 2CW9LTUtOg5wbcBm71geHQ
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameJobPlayerCreate.h
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
//%Header } OTnscqJ0DUU7D4BfVz7A7g
/*
 * $Id: MushGameJobPlayerCreate.h,v 1.6 2005/07/02 00:42:37 southa Exp $
 * $Log: MushGameJobPlayerCreate.h,v $
 * Revision 1.6  2005/07/02 00:42:37  southa
 * Conditioning tweaks
 *
 * Revision 1.5  2005/06/23 17:25:25  southa
 * MushGame link work
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

#include "MushGameJob.h"

#include "MushGameMessageWake.h"
#include "MushGameMessageJoinConfirm.h"
#include "MushGameMessageJoinDenied.h"

//:xml1base MushGameJob
//:generate standard ostream xml1
class MushGameJobPlayerCreate : public MushGameJob
{
public:
    explicit MushGameJobPlayerCreate(const std::string& inID = "");
    virtual ~MushGameJobPlayerCreate() {}

    virtual void MessageConsume(MushGameLogic& ioLogic, const MushGameMessage& inMessage);
    virtual void WakeConsume(MushGameLogic& ioLogic, const MushGameMessageWake& inMessage);
    virtual void JoinConfirmConsume(MushGameLogic& ioLogic, const MushGameMessageJoinConfirm& inMessage);
    virtual void JoinDeniedConsume(MushGameLogic& ioLogic, const MushGameMessageJoinDenied& inMessage);
    
private:
    enum
    {
        kStateInit = 2,
        kStateWait,
        kRetryMsec = 1000
    };

    Mushware::U32 m_state;
    
//%classPrototypes {
public:
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } 1oBgFruy5qHAaudtV+Hcmg
};

//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushGameJobPlayerCreate& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } jzJ6KzXHdMtYjy12LO7zIA
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw

