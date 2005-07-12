//%includeGuardStart {
#ifndef MUSHMESHLIBRARYBASE_H
#define MUSHMESHLIBRARYBASE_H
//%includeGuardStart } 7TvoyuqKMmfU8r+uqp/z2Q
//%Header {
/*****************************************************************************
 *
 * File: src/MushMeshLibrary/MushMeshLibraryBase.h
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
//%Header } mWHW4AKBymr/Qdcf+QHDiA
/*
 * $Id$
 * $Log$
 */

#include "MushMeshLibraryStandard.h"

//:generate virtual standard ostream xml1
class MushMeshLibraryBase : public MushcoreVirtualObject, public MushcoreSingleton<MushMeshLibraryBase>
{
public:
    virtual ~MushMeshLibraryBase() {}
    
    virtual void UnitTesseractVerticesCreate(MushMesh4Mesh& outMesh) const;
    virtual void UnitTesseractCreate(MushMesh4Mesh& outMesh) const;
    
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
