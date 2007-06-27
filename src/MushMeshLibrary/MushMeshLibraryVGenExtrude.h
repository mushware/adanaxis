//%includeGuardStart {
#ifndef MUSHMESHLIBRARYVGENEXTRUDE_H
#define MUSHMESHLIBRARYVGENEXTRUDE_H
//%includeGuardStart } 5kvXF4mcUSjLO91GpoEfmA
//%Header {
/*****************************************************************************
 *
 * File: src/MushMeshLibrary/MushMeshLibraryVGenExtrude.h
 *
 * Copyright: Andy Southgate 2005-2007
 *
 * This file may be used and distributed under the terms of the Mushware
 * Software Licence version 1.4, under the terms for 'Proprietary original
 * source files'.  If not supplied with this software, a copy of the licence
 * can be obtained from Mushware Limited via http://www.mushware.com/.
 * One of your options under that licence is to use and distribute this file
 * under the terms of the GNU General Public Licence version 2.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } JAnzKn+vekZvZIis1+DKxw
/*
 * $Id: MushMeshLibraryVGenExtrude.h,v 1.6 2007/04/18 09:22:54 southa Exp $
 * $Log: MushMeshLibraryVGenExtrude.h,v $
 * Revision 1.6  2007/04/18 09:22:54  southa
 * Header and level fixes
 *
 * Revision 1.5  2006/08/01 17:21:36  southa
 * River demo
 *
 * Revision 1.4  2006/06/01 15:39:34  southa
 * DrawArray verification and fixes
 *
 * Revision 1.3  2005/07/14 12:50:31  southa
 * Extrusion work
 *
 * Revision 1.2  2005/07/13 20:35:48  southa
 * Extrusion work
 *
 * Revision 1.1  2005/07/12 20:39:05  southa
 * Mesh library work
 *
 */

#include "MushMeshLibraryStandard.h"

#include "MushMeshLibraryExtrusionContext.h"

//:xml1base MushMesh4VertexGenerator
//:generate virtual standard ostream xml1
class MushMeshLibraryVGenExtrude : public MushMesh4VertexGenerator
{
public:
    virtual void FaceExtrudeOne(MushMesh4Mesh& ioMesh, const MushMeshDisplacement& inDisp, Mushware::U32& ioFaceNum);
    virtual void FaceExtrude(MushMesh4Mesh& ioMesh, MushMeshLibraryExtrusionContext& ioContext, Mushware::U32 inNum);

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
