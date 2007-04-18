//%includeGuardStart {
#ifndef MUSHMESH4EXTRUDER_H
#define MUSHMESH4EXTRUDER_H
//%includeGuardStart } swauch7vHRnanxOh3oyOqg
//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMesh4Extruder.h
 *
 * Author: Andy Southgate 2002-2007
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
//%Header } a5NZnsHUryj0+dtHwX/1AA
/*
 * $Id: MushMesh4Extruder.h,v 1.3 2006/06/16 01:02:31 southa Exp $
 * $Log: MushMesh4Extruder.h,v $
 * Revision 1.3  2006/06/16 01:02:31  southa
 * Ruby mesh generation
 *
 * Revision 1.2  2006/06/14 18:45:47  southa
 * Ruby mesh generation
 *
 * Revision 1.1  2006/06/14 11:20:07  southa
 * Ruby mesh generation
 *
 */

#include "MushMeshStandard.h"

#include "MushMeshDisplacement.h"

//:generate virtual standard ostream xml1
class MushMesh4Extruder : public MushcoreVirtualObject
{
public:
	MushMesh4Extruder();
	
private:
	Mushware::U32 m_sourceFaceNum; //:readwrite
	MushMeshDisplacement m_disp; //:readwrite
	MushMeshDisplacement m_dispVel; //:readwrite
	Mushware::U32 m_numIterations; //:readwrite
	bool m_toPoint; //:readwrite
	
//%classPrototypes {
public:
    const Mushware::U32& SourceFaceNum(void) const { return m_sourceFaceNum; }
    void SourceFaceNumSet(const Mushware::U32& inValue) { m_sourceFaceNum=inValue; }
    const MushMeshDisplacement& Disp(void) const { return m_disp; }
    void DispSet(const MushMeshDisplacement& inValue) { m_disp=inValue; }
    const MushMeshDisplacement& DispVel(void) const { return m_dispVel; }
    void DispVelSet(const MushMeshDisplacement& inValue) { m_dispVel=inValue; }
    const Mushware::U32& NumIterations(void) const { return m_numIterations; }
    void NumIterationsSet(const Mushware::U32& inValue) { m_numIterations=inValue; }
    const bool& ToPoint(void) const { return m_toPoint; }
    void ToPointSet(const bool& inValue) { m_toPoint=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } batB7iGiqX5YLX7lT829ig
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushMesh4Extruder& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } ogKS66zaSz1vnzxF7zhfvA
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
