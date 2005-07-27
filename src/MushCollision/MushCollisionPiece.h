//%includeGuardStart {
#ifndef MUSHCOLLISIONPIECE_H
#define MUSHCOLLISIONPIECE_H
//%includeGuardStart } ZJbqkRM28mIKtV3tbKXUeA
//%Header {
/*****************************************************************************
 *
 * File: src/MushCollision/MushCollisionPiece.h
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
//%Header } c2RtA/5bJ+a5yX6GTdYnag
/*
 * $Id$
 * $Log$
 */

#include "MushCollisionStandard.h"

//:generate virtual standard ostream xml1
class MushCollisionPiece : public virtual MushcoreVirtualObject
{
public:
    virtual const MushMesh4Mesh& CollisionMesh(void) const;
    virtual const MushMeshPosticity& CollisionPost(void) const;

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
operator<<(std::ostream& ioOut, const MushCollisionPiece& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } XQTIeqimgagFnNrboO+2uA

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
