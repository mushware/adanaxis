//%includeGuardStart {
#ifndef MUSHGAMEJOBADMISSION_H
#define MUSHGAMEJOBADMISSION_H
//%includeGuardStart } yu6AJJDmPLuXA0KQ3WLErg
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameJobAdmission.h
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
//%Header } /JnTWRBmf5VDknf4HgxzxQ
/*
 * $Id: MushGameJobAdmission.h,v 1.4 2006/06/01 15:39:22 southa Exp $
 * $Log: MushGameJobAdmission.h,v $
 * Revision 1.4  2006/06/01 15:39:22  southa
 * DrawArray verification and fixes
 *
 * Revision 1.3  2005/07/02 00:42:37  southa
 * Conditioning tweaks
 *
 * Revision 1.2  2005/06/23 17:25:25  southa
 * MushGame link work
 *
 * Revision 1.1  2005/06/23 13:56:58  southa
 * MushGame link work
 *
 */

#include "MushGameStandard.h"

#include "MushGameJob.h"

#include "MushGameMessageJoinRequest.h"

//:xml1base MushGameJob
//:generate standard ostream xml1
class MushGameJobAdmission : public MushGameJob
{
public:
    explicit MushGameJobAdmission(const std::string& inID = "");
    virtual ~MushGameJobAdmission() {}
    
    virtual void MessageConsume(MushGameLogic& ioLogic, const MushGameMessage& inMessage);
    virtual void JoinRequestConsume(MushGameLogic& ioLogic, const MushGameMessageJoinRequest& inMessage);
    
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
operator<<(std::ostream& ioOut, const MushGameJobAdmission& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } 5rhtAOjHv4oNL6qR77ANeQ
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw

