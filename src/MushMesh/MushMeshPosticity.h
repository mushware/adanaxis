//%includeGuardStart {
#ifndef MUSHMESHPOSTICITY_H
#define MUSHMESHPOSTICITY_H
//%includeGuardStart } MAJj6AwYmIjvO2ep+BhajQ
//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshPosticity.h
 *
 * Author: Andy Southgate 2002-2006
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
//%Header } t1Ub7qKwTGZ73wEUmUwLzw
/*
 * $Id: MushMeshPosticity.h,v 1.4 2005/07/19 10:07:00 southa Exp $
 * $Log: MushMeshPosticity.h,v $
 * Revision 1.4  2005/07/19 10:07:00  southa
 * Adanaxis work
 *
 * Revision 1.3  2005/07/04 15:59:00  southa
 * Adanaxis work
 *
 * Revision 1.2  2005/06/29 11:11:15  southa
 * Camera and rendering work
 *
 * Revision 1.1  2005/06/24 10:30:13  southa
 * MushGame camera work
 *
 */

#include "MushMeshStandard.h"

#include "MushMeshQuaternionPair.h"
#include "MushMeshVector.h"

//:generate virtual standard basic ostream xml1
class MushMeshPosticity : public MushcoreVirtualObject
{
public:
    virtual ~MushMeshPosticity() {}
    
    inline void ToIdentitySet(void);
    inline void InPlaceVelocityAdd(void);
    const MushMeshPosticity Inverse(void) const;
    void InPlaceInvert(void);
    
private:
    Mushware::tQValPair m_angPos; //:readwrite :wref
    Mushware::tQValPair m_angVel; //:readwrite :wref
    Mushware::t4Val m_pos; //:readwrite :wref
    Mushware::t4Val m_vel; //:readwrite :wref
    Mushware::tUsec m_timestamp; //:readwrite
    bool m_timeValid; //:readwrite
    
//%classPrototypes {
public:
    const Mushware::tQValPair& AngPos(void) const { return m_angPos; }
    void AngPosSet(const Mushware::tQValPair& inValue) { m_angPos=inValue; }
    // Writable reference for m_angPos
    Mushware::tQValPair& AngPosWRef(void) { return m_angPos; }
    const Mushware::tQValPair& AngVel(void) const { return m_angVel; }
    void AngVelSet(const Mushware::tQValPair& inValue) { m_angVel=inValue; }
    // Writable reference for m_angVel
    Mushware::tQValPair& AngVelWRef(void) { return m_angVel; }
    const Mushware::t4Val& Pos(void) const { return m_pos; }
    void PosSet(const Mushware::t4Val& inValue) { m_pos=inValue; }
    // Writable reference for m_pos
    Mushware::t4Val& PosWRef(void) { return m_pos; }
    const Mushware::t4Val& Vel(void) const { return m_vel; }
    void VelSet(const Mushware::t4Val& inValue) { m_vel=inValue; }
    // Writable reference for m_vel
    Mushware::t4Val& VelWRef(void) { return m_vel; }
    const Mushware::tUsec& Timestamp(void) const { return m_timestamp; }
    void TimestampSet(const Mushware::tUsec& inValue) { m_timestamp=inValue; }
    const bool& TimeValid(void) const { return m_timeValid; }
    void TimeValidSet(const bool& inValue) { m_timeValid=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual bool AutoEquals(const MushMeshPosticity& inObj) const;
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } ADMCTvufrE442yluUAf8QQ
};

inline void
MushMeshPosticity::ToIdentitySet(void)
{
    m_angPos.ToRotationIdentitySet();
    m_angVel.ToRotationIdentitySet();
    m_pos.ToAdditiveIdentitySet();
    m_vel.ToAdditiveIdentitySet();
    m_timeValid = false;
}

inline void
MushMeshPosticity::InPlaceVelocityAdd(void)
{
    m_pos += m_vel;
    m_angPos.OuterMultiplyBy(m_angVel);
}

inline const MushMeshPosticity
MushMeshPosticity::Inverse(void) const
{
    MushMeshPosticity retVal;
    retVal.PosSet(-Pos());
    retVal.VelSet(-Vel());
    retVal.AngPosSet(AngPos().Conjugate());
    retVal.AngVelSet(AngVel().Conjugate());

    // Leave timeValid false
    return retVal;
}

inline void
MushMeshPosticity::InPlaceInvert(void)
{
    m_pos = -m_pos;
    m_vel = -m_vel;
    m_angPos.InPlaceConjugate();
    m_angVel.InPlaceConjugate();
    m_timeValid = false;
}

//%inlineHeader {

inline bool
operator==(const MushMeshPosticity& inA, const MushMeshPosticity& inB)
{
    return inA.AutoEquals(inB);
}

inline bool
operator!=(const MushMeshPosticity& inA, const MushMeshPosticity& inB)
{
    return !inA.AutoEquals(inB);
}
inline std::ostream&
operator<<(std::ostream& ioOut, const MushMeshPosticity& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } Uebb2nRGfeVz7/aHX/Pxsg
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
