//%includeGuardStart {
#ifndef MUSHMESHFACE_H
#define MUSHMESHFACE_H
//%includeGuardStart } mYM+bQDZbCCM0JHfxjwyuw
//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshFace.h
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
//%Header } SZXiiaJXfySyO3W0n6wFYA
/*
 * $Id: MushMeshFace.h,v 1.2 2006/06/01 15:39:29 southa Exp $
 * $Log: MushMeshFace.h,v $
 * Revision 1.2  2006/06/01 15:39:29  southa
 * DrawArray verification and fixes
 *
 * Revision 1.1  2005/06/30 12:04:55  southa
 * Mesh work
 *
 */

#include "MushMeshStandard.h"

//:generate virtual standard ostream xml1
class MushMeshFace : public MushcoreVirtualObject
{
public:
    virtual ~MushMeshFace() {}
    
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
operator<<(std::ostream& ioOut, const MushMeshFace& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } HCc9s3gWEZ38xP/BFPHuIA
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
