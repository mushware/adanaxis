//%includeGuardStart {
#ifndef MUSHGAMELINKLOCAL_H
#define MUSHGAMELINKLOCAL_H
//%includeGuardStart } 0/YY5aWWhNBrwLukR235Qw
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameLinkLocal.h
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
//%Header } j3xn31mxAz8yE9n9qEZG6g
/*
 * $Id: MushGameLinkLocal.h,v 1.4 2005/06/23 11:58:28 southa Exp $
 * $Log: MushGameLinkLocal.h,v $
 * Revision 1.4  2005/06/23 11:58:28  southa
 * MushGame link work
 *
 * Revision 1.3  2005/06/22 20:01:59  southa
 * MushGame link work
 *
 * Revision 1.2  2005/06/21 15:57:48  southa
 * MushGame work
 *
 * Revision 1.1  2005/06/20 16:14:31  southa
 * Adanaxis work
 *
 */

#include "MushGameStandard.h"

#include "MushGameClient.h"
#include "MushGameMailbox.h"
#include "MushGameLink.h"
#include "MushGameServer.h"

class MushGameLogic;

//:xml1base MushGameLink
//:generate virtual standard ostream xml1
class MushGameLinkLocal : public MushGameLink
{
public:
    typedef MushcoreData< MushcorePipe<MushGameMailbox> > tPipeData;
    typedef MushcoreDataRef< MushcorePipe<MushGameMailbox> > tPipeDataRef;
   
    MushGameLinkLocal();
    virtual ~MushGameLinkLocal() {}
    virtual void SrcDestSet(const std::string& inSrcName, const std::string& inDestName);

    virtual bool OutboxSendUnlessEmpty(void);
    virtual bool InboxGetUnlessEmpty(MushGameMailbox& outMailbox);
    virtual void ToOutboxCopy(const MushGameMessage& inMessage);
    
protected:
    // Pipe database for connecting links
    static tPipeData m_pipeData;
    
private:
    MushGameMailbox m_outBox; //:ignore
    MushGameMailbox m_inBox; //:ignore

    tPipeDataRef m_uplinkRef; //:ignore
    tPipeDataRef m_downlinkRef; //:ignore
    
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
operator<<(std::ostream& ioOut, const MushGameLinkLocal& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } GJAmucyBlwTyaWsSpOPcGw
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
