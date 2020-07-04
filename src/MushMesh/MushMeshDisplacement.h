//%includeGuardStart {
#ifndef MUSHMESHDISPLACEMENT_H
#define MUSHMESHDISPLACEMENT_H
//%includeGuardStart } v0vcp/ttab4sGjtSWLtmZQ
//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshDisplacement.h
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
//%Header } haaq3/Owix5pnf8D0txfnQ
/*
 * $Id: MushMeshDisplacement.h,v 1.6 2006/06/16 01:02:32 southa Exp $
 * $Log: MushMeshDisplacement.h,v $
 * Revision 1.6  2006/06/16 01:02:32  southa
 * Ruby mesh generation
 *
 * Revision 1.5  2006/06/14 18:45:48  southa
 * Ruby mesh generation
 *
 * Revision 1.4  2006/06/14 11:20:07  southa
 * Ruby mesh generation
 *
 * Revision 1.3  2006/06/01 15:39:29  southa
 * DrawArray verification and fixes
 *
 * Revision 1.2  2005/07/14 12:50:31  southa
 * Extrusion work
 *
 * Revision 1.1  2005/07/12 20:39:05  southa
 * Mesh library work
 *
 */

#include "MushMeshStandard.h"

#include "MushMeshQuaternionPair.h"
#include "MushMeshVector.h"

//:generate virtual standard ostream xml1
class MushMeshDisplacement : public MushcoreVirtualObject
{
public:
    MushMeshDisplacement() {}
    MushMeshDisplacement(const Mushware::t4Val& inOffset, const Mushware::tQValPair& inRotation, Mushware::t4Val inScale) :
        m_offset(inOffset), m_rotation(inRotation), m_scale(inScale) {}
    
	void ScaleSet(const Mushware::tVal& inValue) { m_scale = Mushware::t4Val(inValue, inValue, inValue, inValue); }
	
    void ToIdentitySet(void) { m_rotation.ToRotationIdentitySet(); m_offset.ToAdditiveIdentitySet(); m_scale.ToMultiplicativeIdentitySet();}
	
	void Displace(Mushware::t4Val& ioVec) const
    {
		m_rotation.VectorRotate(ioVec);
		ioVec.InPlaceElementwiseMultiply(m_scale);
		ioVec += m_offset;
	}
	
	static MushMeshDisplacement Identity(void)
    {
		return MushMeshDisplacement(Mushware::t4Val::AdditiveIdentity(),
									Mushware::tQValPair::RotationIdentity(),
                                    Mushware::t4Val::MultiplicativeIdentity()); 
	}

private:
    Mushware::t4Val m_offset; //:readwrite :wref
    Mushware::tQValPair m_rotation; //:readwrite :wref
    Mushware::t4Val m_scale; //:readwrite :wref
    
//%classPrototypes {
public:
    const Mushware::t4Val& Offset(void) const { return m_offset; }
    void OffsetSet(const Mushware::t4Val& inValue) { m_offset=inValue; }
    // Writable reference for m_offset
    Mushware::t4Val& OffsetWRef(void) { return m_offset; }
    const Mushware::tQValPair& Rotation(void) const { return m_rotation; }
    void RotationSet(const Mushware::tQValPair& inValue) { m_rotation=inValue; }
    // Writable reference for m_rotation
    Mushware::tQValPair& RotationWRef(void) { return m_rotation; }
    const Mushware::t4Val& Scale(void) const { return m_scale; }
    void ScaleSet(const Mushware::t4Val& inValue) { m_scale=inValue; }
    // Writable reference for m_scale
    Mushware::t4Val& ScaleWRef(void) { return m_scale; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } WXtqIO8rfew2XD7cQ6NgdA
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushMeshDisplacement& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } 2e6DCxwmnaulAhEB2fj4Zg

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
