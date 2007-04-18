//%includeGuardStart {
#ifndef MUSHGAMELOGICLOCAL_H
#define MUSHGAMELOGICLOCAL_H
//%includeGuardStart } gX86MOXtLh2LiVRaAbr5dQ
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameLogicLocal.h
 *
 * Author: Andy Southgate 2002-2007
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
//%Header } 5CHfYNOUXdIsyKmlZqDKog
/*
 * $Id: MushGameLogicLocal.h,v 1.5 2006/06/01 15:39:23 southa Exp $
 * $Log: MushGameLogicLocal.h,v $
 * Revision 1.5  2006/06/01 15:39:23  southa
 * DrawArray verification and fixes
 *
 * Revision 1.4  2005/06/23 17:25:25  southa
 * MushGame link work
 *
 * Revision 1.3  2005/06/22 20:01:59  southa
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

#include "MushGameLogic.h"

//:xml1base MushGameLogic
//:generate virtual standard ostream xml1
class MushGameLogicLocal : public MushGameLogic
{
public:
    MushGameLogicLocal();
    virtual ~MushGameLogicLocal() {}
    
    virtual void SinglePlayerCheck(void);
    virtual void PerFrameProcessing(void);
    virtual void JobMessageConsume(MushGameLogic& ioLogic, const MushGameMessage& inMessage);

protected:    
private:

    
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
operator<<(std::ostream& ioOut, const MushGameLogicLocal& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } LEOGPdjIWn5fvNU2FWiMZg
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
