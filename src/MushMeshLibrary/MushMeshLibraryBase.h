//%includeGuardStart {
#ifndef MUSHMESHLIBRARYBASE_H
#define MUSHMESHLIBRARYBASE_H
//%includeGuardStart } 7TvoyuqKMmfU8r+uqp/z2Q
//%Header {
/*****************************************************************************
 *
 * File: src/MushMeshLibrary/MushMeshLibraryBase.h
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
//%Header } PnI7OAn1POxxwCCtHBGJrA
/*
 * $Id: MushMeshLibraryBase.h,v 1.8 2007/04/18 09:22:53 southa Exp $
 * $Log: MushMeshLibraryBase.h,v $
 * Revision 1.8  2007/04/18 09:22:53  southa
 * Header and level fixes
 *
 * Revision 1.7  2006/09/12 15:28:50  southa
 * World sphere
 *
 * Revision 1.6  2006/08/01 17:21:33  southa
 * River demo
 *
 * Revision 1.5  2006/07/17 14:43:40  southa
 * Billboarded deco objects
 *
 * Revision 1.4  2006/06/01 15:39:33  southa
 * DrawArray verification and fixes
 *
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
    virtual void SingleFacetCreate(MushMesh4Mesh& ioMesh, Mushware::U32 inOrder, const MushMeshDisplacement& inDisp) const;
    virtual void SingleFacetCreate(MushMesh4Mesh& ioMesh, Mushware::U32 inOrder) const;
    
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
