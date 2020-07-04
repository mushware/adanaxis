//%includeGuardStart {
#ifndef MUSHMESH4EXTRUDER_H
#define MUSHMESH4EXTRUDER_H
//%includeGuardStart } swauch7vHRnanxOh3oyOqg
//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMesh4Extruder.h
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
//%Header } +0hZyIA4RbmY2kOnr12H2w
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
