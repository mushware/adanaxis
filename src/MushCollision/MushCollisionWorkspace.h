//%includeGuardStart {
#ifndef MUSHCOLLISIONWORKSPACE_H
#define MUSHCOLLISIONWORKSPACE_H
//%includeGuardStart } PcPOuVXCJDuUEvDz0vLtAQ
//%Header {
/*****************************************************************************
 *
 * File: src/MushCollision/MushCollisionWorkspace.h
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
//%Header } CqrAMDY0CcR/iEXbQBk/ZA
/*
 * $Id: MushCollisionWorkspace.h,v 1.1 2005/07/27 18:09:59 southa Exp $
 * $Log: MushCollisionWorkspace.h,v $
 * Revision 1.1  2005/07/27 18:09:59  southa
 * Collision checking
 *
 */

#include "MushCollisionStandard.h"

//:generate virtual standard ostream xml1
class MushCollisionWorkspace : public MushcoreVirtualObject
{
public:
    MushCollisionWorkspace();

    void Touch(void); // Called by constructor
    void ResetIfNeeded(Mushware::tMsec inFrameMsec);
    
private:
    Mushware::tMsec m_frameMsec; //:readwrite
    Mushware::t4Val m_centroid; //:readwrite :wref
    std::vector<Mushware::t4Val> m_chunkCentroids; //:readwrite :wref
    
    bool m_centroidValid;
    bool m_chunkCentroidsValid;
    
//%classPrototypes {
public:
    const Mushware::tMsec& FrameMsec(void) const { return m_frameMsec; }
    void FrameMsecSet(const Mushware::tMsec& inValue) { m_frameMsec=inValue; }
    const Mushware::t4Val& Centroid(void) const { return m_centroid; }
    void CentroidSet(const Mushware::t4Val& inValue) { m_centroid=inValue; }
    // Writable reference for m_centroid
    Mushware::t4Val& CentroidWRef(void) { return m_centroid; }
    const std::vector<Mushware::t4Val>& ChunkCentroids(void) const { return m_chunkCentroids; }
    void ChunkCentroidsSet(const std::vector<Mushware::t4Val>& inValue) { m_chunkCentroids=inValue; }
    // Writable reference for m_chunkCentroids
    std::vector<Mushware::t4Val>& ChunkCentroidsWRef(void) { return m_chunkCentroids; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } LiHeCqRN6Tc5e7cDR6BR9Q
};
//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushCollisionWorkspace& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } /+uw7H0WmUwZEJh3oyHk/g
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
