//%includeGuardStart {
#ifndef MUSHMESHLIBRARYVGENEXTRUDE_H
#define MUSHMESHLIBRARYVGENEXTRUDE_H
//%includeGuardStart } 5kvXF4mcUSjLO91GpoEfmA
//%Header {
/*****************************************************************************
 *
 * File: src/MushMeshLibrary/MushMeshLibraryVGenExtrude.h
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
//%Header } tPEzc8nLw6dNYeKlc4A5WQ
/*
 * $Id: MushMeshLibraryVGenExtrude.h,v 1.1 2005/07/12 20:39:05 southa Exp $
 * $Log: MushMeshLibraryVGenExtrude.h,v $
 * Revision 1.1  2005/07/12 20:39:05  southa
 * Mesh library work
 *
 */

#include "MushMeshLibraryStandard.h"

//:xml1base MushMesh4VertexGenerator
//:generate virtual standard ostream xml1
class MushMeshLibraryVGenExtrude : public MushMesh4VertexGenerator
{
public:
    virtual void FaceExtrudeOne(MushMesh4Mesh& ioMesh, const MushMeshDisplacement& inDisp, Mushware::U32 inFaceNum);
    virtual void FaceExtrude(MushMesh4Mesh& ioMesh, MushMeshDisplacement& ioDisp, Mushware::U32 inFaceNum, Mushware::U32 inNum);

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
operator<<(std::ostream& ioOut, const MushMeshLibraryVGenExtrude& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } anyYAdtHRl790WFFrgz+rQ
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
