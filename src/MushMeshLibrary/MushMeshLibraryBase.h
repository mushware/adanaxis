//%includeGuardStart {
#ifndef MUSHMESHLIBRARYBASE_H
#define MUSHMESHLIBRARYBASE_H
//%includeGuardStart } 7TvoyuqKMmfU8r+uqp/z2Q
//%Header {
/*****************************************************************************
 *
 * File: src/MushMeshLibrary/MushMeshLibraryBase.h
 *
 * Copyright: Andy Southgate 2005-2006
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
//%Header } JMQ6Bw79bYzUs+Ek4D1kZw
/*
 * $Id: MushMeshLibraryBase.h,v 1.3 2005/07/19 13:44:26 southa Exp $
 * $Log: MushMeshLibraryBase.h,v $
 * Revision 1.3  2005/07/19 13:44:26  southa
 * MushMesh4Chunk work
 *
 * Revision 1.2  2005/07/14 16:55:09  southa
 * Mesh library work
 *
 * Revision 1.1  2005/07/12 20:39:05  southa
 * Mesh library work
 *
 */

#include "MushMeshLibraryStandard.h"

//:generate virtual standard ostream xml1
class MushMeshLibraryBase : public MushcoreVirtualObject, public MushcoreSingleton<MushMeshLibraryBase>
{
public:
    virtual ~MushMeshLibraryBase() {}
    
    virtual void UnitTesseractVerticesCreate(MushMesh4Mesh& ioMesh) const;
    virtual void UnitTesseractCreate(MushMesh4Mesh& ioMesh) const;

    virtual void PolygonPrismVerticesCreate(MushMesh4Mesh& ioMesh, const Mushware::t4Val& inScale, Mushware::U32 inOrder) const;
    virtual void PolygonPrismCreate(MushMesh4Mesh& ioMesh, const Mushware::t4Val& inScale, Mushware::U32 inOrder) const;
    
protected:
    virtual void CongruentFacesJoin(MushMesh4Mesh& ioMesh, Mushware::U32 inFaceNum1, Mushware::U32 inFaceNum2) const;

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
operator<<(std::ostream& ioOut, const MushMeshLibraryBase& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } cvR89ynh7+FoOY3PYvv72w
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
