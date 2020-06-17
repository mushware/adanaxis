//%includeGuardStart {
#ifndef MUSHMESHLIBRARYEXTRUSIONCONTEXT_H
#define MUSHMESHLIBRARYEXTRUSIONCONTEXT_H
//%includeGuardStart } ArlkzbscdC0zoEgdEDpn4A
//%Header {
/*****************************************************************************
 *
 * File: src/MushMeshLibrary/MushMeshLibraryExtrusionContext.h
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
//%Header } sL5V56v2Dow1q8IaG4y3YA
/*
 * $Id: MushMeshLibraryExtrusionContext.h,v 1.7 2007/04/18 09:22:53 southa Exp $
 * $Log: MushMeshLibraryExtrusionContext.h,v $
 * Revision 1.7  2007/04/18 09:22:53  southa
 * Header and level fixes
 *
 * Revision 1.6  2006/08/01 17:21:34  southa
 * River demo
 *
 * Revision 1.5  2006/06/14 18:45:48  southa
 * Ruby mesh generation
 *
 * Revision 1.4  2006/06/01 15:39:34  southa
 * DrawArray verification and fixes
 *
 * Revision 1.3  2005/07/18 13:13:36  southa
 * Extrude to point and projectile mesh
 *
 * Revision 1.2  2005/07/14 16:55:09  southa
 * Mesh library work
 *
 * Revision 1.1  2005/07/14 12:50:31  southa
 * Extrusion work
 *
 */

#include "MushMeshLibraryStandard.h"

//:generate virtual standard ostream xml1
class MushMeshLibraryExtrusionContext : public MushcoreVirtualObject
{
public:
    MushMeshLibraryExtrusionContext() : m_scaleThreshold(0), m_scaleVelocity(0)  {}
    MushMeshLibraryExtrusionContext(const MushMeshDisplacement& inDisp, Mushware::U32 inFaceNum) :
        m_disp(inDisp), m_faceNum(inFaceNum), m_scaleThreshold(0), m_scaleVelocity(0)
    {
        Reset();
    }
    virtual ~MushMeshLibraryExtrusionContext() {}
    
    void DispSet(const MushMeshDisplacement& inValue) { m_disp=inValue; m_rollingDisp=inValue; }
    void FaceNumSet(const Mushware::U32& inValue) { m_faceNum=inValue; m_rollingFaceNum=inValue; }
    void Reset(void) { m_rollingDisp = m_disp; m_rollingFaceNum = m_faceNum; }
    void ResetNewDispFace(const MushMeshDisplacement& inDisp, Mushware::U32 inFaceNum)
    { 
        m_disp = inDisp;
        m_faceNum = inFaceNum;
        Reset();
    }
    void ResetNewDisp(const MushMeshDisplacement& inDisp)
    { 
        m_disp = inDisp;
        Reset();
    }
    void ResetNewFace(Mushware::U32 inFaceNum)
    {
        m_faceNum = inFaceNum;
        Reset();
    }
    void VelocityAdd(void)
    {
        
        Mushware::t4Val newScale = m_rollingDisp.Scale() + m_scaleVelocity;
        
		m_rollingDisp.ScaleSet(newScale);
        
        m_rollingDisp.Rotation().VectorRotate(m_rollingDisp.OffsetWRef());
    }
    
private:
    MushMeshDisplacement m_disp; //:read
    Mushware::U32 m_faceNum; //:read
    Mushware::tVal m_scaleThreshold; //:readwrite
    Mushware::tVal m_scaleVelocity; //:readwrite
    
    MushMeshDisplacement m_rollingDisp; //:readwrite :wref
    Mushware::U32 m_rollingFaceNum; //:readwrite :wref
    
//%classPrototypes {
public:
    const MushMeshDisplacement& Disp(void) const { return m_disp; }
    const Mushware::U32& FaceNum(void) const { return m_faceNum; }
    const Mushware::tVal& ScaleThreshold(void) const { return m_scaleThreshold; }
    void ScaleThresholdSet(const Mushware::tVal& inValue) { m_scaleThreshold=inValue; }
    const Mushware::tVal& ScaleVelocity(void) const { return m_scaleVelocity; }
    void ScaleVelocitySet(const Mushware::tVal& inValue) { m_scaleVelocity=inValue; }
    const MushMeshDisplacement& RollingDisp(void) const { return m_rollingDisp; }
    void RollingDispSet(const MushMeshDisplacement& inValue) { m_rollingDisp=inValue; }
    // Writable reference for m_rollingDisp
    MushMeshDisplacement& RollingDispWRef(void) { return m_rollingDisp; }
    const Mushware::U32& RollingFaceNum(void) const { return m_rollingFaceNum; }
    void RollingFaceNumSet(const Mushware::U32& inValue) { m_rollingFaceNum=inValue; }
    // Writable reference for m_rollingFaceNum
    Mushware::U32& RollingFaceNumWRef(void) { return m_rollingFaceNum; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } 4fv+ImoSsABNvAl0++Vp0A
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushMeshLibraryExtrusionContext& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } kifoZVeLWABs0+Xg5oyD6w
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
