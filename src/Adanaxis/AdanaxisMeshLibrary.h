//%includeGuardStart {
#ifndef ADANAXISMESHLIBRARY_H
#define ADANAXISMESHLIBRARY_H
//%includeGuardStart } cny6ATfwvXDCKlGwAm7+wg
//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisMeshLibrary.h
 *
 * Copyright: Andy Southgate 2002-2007, 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/
//%Header } g/+YiGySAXcWziUoQRtCEg
/*
 * $Id: AdanaxisMeshLibrary.h,v 1.6 2007/04/18 09:22:01 southa Exp $
 * $Log: AdanaxisMeshLibrary.h,v $
 * Revision 1.6  2007/04/18 09:22:01  southa
 * Header and level fixes
 *
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
