//%includeGuardStart {
#ifndef MUSHMESHLIBRARYFGENEXTRUDE_H
#define MUSHMESHLIBRARYFGENEXTRUDE_H
//%includeGuardStart } Z1xfm1lBZkdDgXQlA5E8IA
//%Header {
/*****************************************************************************
 *
 * File: src/MushMeshLibrary/MushMeshLibraryFGenExtrude.h
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
//%Header } rWTR9VGBEQumCT7LMzSnOw
/*
 * $Id$
 * $Log$
 */

#include "MushMeshLibraryStandard.h"

//:xml1base MushMesh4FaceGenerator
//:generate virtual standard ostream xml1
class MushMeshLibraryFGenExtrude : public MushMesh4FaceGenerator
{
public:
    virtual void FaceExtrudeOne(MushMesh4Mesh& ioMesh, Mushware::U32 inFace);
    virtual void FaceExtrude(MushMesh4Mesh& ioMesh, Mushware::U32 inFace, Mushware::U32 inNum);
    
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
