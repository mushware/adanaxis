//%includeGuardStart {
#ifndef MUSHMESHLIBRARYEXTRUSIONCONTEXT_H
#define MUSHMESHLIBRARYEXTRUSIONCONTEXT_H
//%includeGuardStart } ArlkzbscdC0zoEgdEDpn4A
//%Header {
/*****************************************************************************
 *
 * File: src/MushMeshLibrary/MushMeshLibraryExtrusionContext.h
 *
 * Copyright: Andy Southgate 2005
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
//%Header } TE/rDUf2Sf89WHdHn2RHUA
/*
 * $Id: MushMeshLibraryExtrusionContext.h,v 1.1 2005/07/14 12:50:31 southa Exp $
 * $Log: MushMeshLibraryExtrusionContext.h,v $
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
        m_rollingDisp.ScaleWRef() += m_scaleVelocity;
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
