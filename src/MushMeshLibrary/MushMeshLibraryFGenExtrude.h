//%includeGuardStart {
#ifndef MUSHMESHLIBRARYFGENEXTRUDE_H
#define MUSHMESHLIBRARYFGENEXTRUDE_H
//%includeGuardStart } Z1xfm1lBZkdDgXQlA5E8IA
//%Header {
/*****************************************************************************
 *
 * File: src/MushMeshLibrary/MushMeshLibraryFGenExtrude.h
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
//%Header } mw7NxOfLegMZOtmXcE+FGw
/*
 * $Id: MushMeshLibraryFGenExtrude.h,v 1.7 2007/04/18 09:22:53 southa Exp $
 * $Log: MushMeshLibraryFGenExtrude.h,v $
 * Revision 1.7  2007/04/18 09:22:53  southa
 * Header and level fixes
 *
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
