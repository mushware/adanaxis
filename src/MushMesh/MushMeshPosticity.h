//%includeGuardStart {
#ifndef MUSHMESHPOSTICITY_H
#define MUSHMESHPOSTICITY_H
//%includeGuardStart } MAJj6AwYmIjvO2ep+BhajQ
//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMeshPosticity.h
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
//%Header } +eMrlpttHnUzQ/qPZM7tGQ
/*
 * $Id$
 * $Log$
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
    
private:
    Mushware::tQValPair m_angPos; //:readwrite
    Mushware::tQValPair m_angVel; //:readwrite
    Mushware::t4Val m_pos; //:readwrite
    Mushware::t4Val m_vel; //:readwrite
    Mushware::tUsec m_timestamp; //:readwrite
    bool m_timeValid; //:readwrite
    
//%classPrototypes {
public:
    const Mushware::tQValPair& AngPos(void) const { return m_angPos; }
    void AngPosSet(const Mushware::tQValPair& inValue) { m_angPos=inValue; }
    const Mushware::tQValPair& AngVel(void) const { return m_angVel; }
    void AngVelSet(const Mushware::tQValPair& inValue) { m_angVel=inValue; }
    const Mushware::t4Val& Pos(void) const { return m_pos; }
    void PosSet(const Mushware::t4Val& inValue) { m_pos=inValue; }
    const Mushware::t4Val& Vel(void) const { return m_vel; }
    void VelSet(const Mushware::t4Val& inValue) { m_vel=inValue; }
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
//%classPrototypes } ubocSCPQFmqeL6ODeb2p0A
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
