//%includeGuardStart {
#ifndef MUSHCOLLISIONLISTENTRY_H
#define MUSHCOLLISIONLISTENTRY_H
//%includeGuardStart } 05gSd/I/glrhh57Pu0bjSQ
//%Header {
/*****************************************************************************
 *
 * File: src/MushCollision/MushCollisionListEntry.h
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
//%Header } AJ81q6IJvO8a5UHj5Vismw
/*
 * $Id: MushCollisionListEntry.h,v 1.2 2005/08/01 13:09:58 southa Exp $
 * $Log: MushCollisionListEntry.h,v $
 * Revision 1.2  2005/08/01 13:09:58  southa
 * Collision messaging
 *
 * Revision 1.1  2005/07/27 18:09:59  southa
 * Collision checking
 *
 */

#include "MushCollisionStandard.h"

#include "MushCollisionPiece.h"

//:generate virtual standard ostream xml1
class MushCollisionListEntry : public MushcoreVirtualObject
{
public:

    
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
operator<<(std::ostream& ioOut, const MushCollisionListEntry& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } HC2K01FWAJ1bkEftyMU/og
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
