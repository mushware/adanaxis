//%includeGuardStart {
#ifndef MUSHMESHLIBRARYFGENEXTRUDE_H
#define MUSHMESHLIBRARYFGENEXTRUDE_H
//%includeGuardStart } Z1xfm1lBZkdDgXQlA5E8IA
//%Header {
/*****************************************************************************
 *
 * File: src/MushMeshLibrary/MushMeshLibraryFGenExtrude.h
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
//%Header } sQoBzDxjKZqr9M+dWMSXbQ
/*
 * $Id: MushMeshLibraryFGenExtrude.h,v 1.6 2006/08/01 17:21:34 southa Exp $
 * $Log: MushMeshLibraryFGenExtrude.h,v $
 * Revision 1.6  2006/08/01 17:21:34  southa
 * River demo
 *
 * Revision 1.5  2006/06/01 15:39:34  southa
 * DrawArray verification and fixes
 *
 * Revision 1.4  2005/07/18 13:13:36  southa
 * Extrude to point and projectile mesh
 *
 * Revision 1.3  2005/07/14 12:50:31  southa
 * Extrusion work
 *
 * Revision 1.2  2005/07/13 16:45:05  southa
 * Extrusion work
 *
 * Revision 1.1  2005/07/12 20:39:05  southa
 * Mesh library work
 *
 */

#include "MushMeshLibraryStandard.h"

#include "MushMeshLibraryExtrusionContext.h"

//:xml1base MushMesh4FaceGenerator
//:generate virtual standard ostream xml1
class MushMeshLibraryFGenExtrude : public MushMesh4FaceGenerator
{
public:
    virtual void FaceExtrudeOne(MushMesh4Mesh& ioMesh, Mushware::U32& ioFaceNum, bool inToPoint);
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
operator<<(std::ostream& ioOut, const MushMeshLibraryFGenExtrude& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } 0jMxmCKtw2pO5/9sCc2TeA
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
