//%includeGuardStart {
#ifndef MUSHCOLLISIONRESOLVER_H
#define MUSHCOLLISIONRESOLVER_H
//%includeGuardStart } jGGnAirmq717WeH6BtDTlw
//%Header {
/*****************************************************************************
 *
 * File: src/MushCollision/MushCollisionResolver.h
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
//%Header } OkLaKNsPzgty1sczCrbe0Q
/*
 * $Id$
 * $Log$
 */

#include "MushCollisionStandard.h"

#include "MushCollisionPiece.h"

//:generate standard ostream xml1
class MushCollisionResolver : public MushcoreVirtualObject, public MushcoreSingleton<MushCollisionResolver>
{
public:
    Mushware::tVal Resolve(const MushCollisionPiece& inPiece1, const MushCollisionPiece& inPiece2) const;

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
operator<<(std::ostream& ioOut, const MushCollisionResolver& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } HNNZFTynkudwCQk/JqIOBw
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
