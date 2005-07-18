//%includeGuardStart {
#ifndef ADANAXISMESHLIBRARY_H
#define ADANAXISMESHLIBRARY_H
//%includeGuardStart } cny6ATfwvXDCKlGwAm7+wg
//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisMeshLibrary.h
 *
 * Copyright: Andy Southgate 2005
 *
 * This file may be used and distributed under the terms of the Mushware
 * software licence version 1.0, under the terms for 'Proprietary original
 * source files'.  If not supplied with this software, a copy of the licence
 * can be obtained from Mushware Limited via http://www.mushware.com/.
 * One of your options under that licence is to use and distribute this file
 * under the terms of the GNU General Public Licence version 2.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 8wu6JJaIcLGhv4Titc9Yww
/*
 * $Id$
 * $Log$
 */

#include "AdanaxisStandard.h"

#include "API/mushMushMeshLibrary.h"

//:xml1base MushMeshLibraryBase
//:generate virtual standard ostream xml1
class AdanaxisMeshLibrary : public MushMeshLibraryBase
{
public:
    virtual ~AdanaxisMeshLibrary() {}

    virtual void ProjectileCreate(MushMesh4Mesh& ioMesh) const;

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
operator<<(std::ostream& ioOut, const AdanaxisMeshLibrary& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } Xho13aScchP/mb9P6u0mnw
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
