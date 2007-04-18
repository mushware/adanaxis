//%includeGuardStart {
#ifndef MUSHMESH4BASE_H
#define MUSHMESH4BASE_H
//%includeGuardStart } ERerg+tNIwIHTvdBHVaJ9Q
//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMesh4Base.h
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
//%Header } qFwbC+wPvrtWS8Ima2AFSQ
/*
 * $Id: MushMesh4Base.h,v 1.2 2006/06/16 12:11:04 southa Exp $
 * $Log: MushMesh4Base.h,v $
 * Revision 1.2  2006/06/16 12:11:04  southa
 * Ruby subclasses
 *
 * Revision 1.1  2006/06/16 01:02:31  southa
 * Ruby mesh generation
 *
 */

#include "MushMeshStandard.h"

class MushMesh4Mesh;

//:generate virtual standard ostream xml1
class MushMesh4Base : public MushcoreVirtualObject
{
public:
    virtual void Make(MushMesh4Mesh& ioMesh) const;
	
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
operator<<(std::ostream& ioOut, const MushMesh4Base& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } OPWKSOlt1+Vt28X5pXAt8Q
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
