//%includeGuardStart {
#ifndef ADANAXISMESHLIBRARY_H
#define ADANAXISMESHLIBRARY_H
//%includeGuardStart } cny6ATfwvXDCKlGwAm7+wg
//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisMeshLibrary.h
 *
 * Copyright: Andy Southgate 2005-2007
 *
 * This file may be used and distributed under the terms of the Mushware
 * Software Licence version 1.3, under the terms for 'Proprietary original
 * source files'.  If not supplied with this software, a copy of the licence
 * can be obtained from Mushware Limited via http://www.mushware.com/.
 * One of your options under that licence is to use and distribute this file
 * under the terms of the GNU General Public Licence version 2.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } n9J2Tzlieip/CTspWncEvQ
/*
 * $Id: AdanaxisMeshLibrary.h,v 1.5 2006/08/01 17:21:24 southa Exp $
 * $Log: AdanaxisMeshLibrary.h,v $
 * Revision 1.5  2006/08/01 17:21:24  southa
 * River demo
 *
 * Revision 1.4  2006/06/08 20:17:30  southa
 * Texture tile generation method 2
 *
 * Revision 1.3  2006/05/03 00:58:43  southa
 * Texturing updates
 *
 * Revision 1.2  2005/09/05 12:54:29  southa
 * Solid rendering work
 *
 * Revision 1.1  2005/07/18 13:13:35  southa
 * Extrude to point and projectile mesh
 *
 */

#include "AdanaxisStandard.h"

#include "API/mushMushMeshLibrary.h"

//:xml1base MushMeshLibraryBase
//:generate virtual standard ostream xml1
class AdanaxisMeshLibrary : public MushMeshLibraryBase
{
public:
    virtual ~AdanaxisMeshLibrary() {}

    virtual void TesseractCreate(MushMesh4Mesh& ioMesh) const;
    virtual void ProjectileCreate(MushMesh4Mesh& ioMesh) const;

    virtual void AttendantVerticesSet(MushMesh4Mesh& ioMesh, Mushware::tVal inAnim) const;
    virtual void AttendantCreate(MushMesh4Mesh& ioMesh) const;
	
    virtual void TestObjectVerticesSet(MushMesh4Mesh& ioMesh, Mushware::tVal inAnim) const;
    virtual void TestObjectCreate(MushMesh4Mesh& ioMesh) const;
	
    static AdanaxisMeshLibrary& AdanaxisSgl(void);
    
protected:
	virtual void AttendantExtrusionContext(MushMeshLibraryExtrusionContext& outContext, const MushMesh4Mesh& inMesh, Mushware::tVal inAnim) const;
    virtual void TestObjectExtrusionContext(MushMeshLibraryExtrusionContext& outContext, const MushMesh4Mesh& inMesh, Mushware::tVal inAnim) const;
    
private:
    enum
    {
        kAttendantLODFactor = 5,
		kTestObjectLODFactor = 3
    };
        
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

inline AdanaxisMeshLibrary&
AdanaxisMeshLibrary::AdanaxisSgl(void)
{
    AdanaxisMeshLibrary *pLibrary = dynamic_cast<AdanaxisMeshLibrary *>(&Sgl());
    if (pLibrary == NULL)
    {
        throw MushcoreRequestFail(std::string("MeshLibrary of wrong type (")+Sgl().AutoName()+")");
    }
    return *pLibrary;
}

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
