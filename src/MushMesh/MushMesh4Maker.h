//%includeGuardStart {
#ifndef MUSHMESH4MAKER_H
#define MUSHMESH4MAKER_H
//%includeGuardStart } ZP8CKcDc2On8BZqMaC7oLg
//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMesh4Maker.h
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
//%Header } TOsh5JcMd1L85/Q5VLLjVg
/*
 * $Id$
 * $Log$
 */

#include "MushMeshStandard.h"

#include "MushMesh4Mesh.h"

//:generate virtual standard ostream xml1
class MushMesh4Maker : public MushcoreVirtualObject, public MushcoreSingleton<MushMesh4Maker>
{
public:
    virtual void Make(MushMesh4Mesh& ioMesh);
	
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
operator<<(std::ostream& ioOut, const MushMesh4Maker& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } c003AhGwzl0KPceZDL7t2g
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw