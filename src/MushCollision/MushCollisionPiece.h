//%includeGuardStart {
#ifndef MUSHCOLLISIONPIECE_H
#define MUSHCOLLISIONPIECE_H
//%includeGuardStart } ZJbqkRM28mIKtV3tbKXUeA
//%Header {
/*****************************************************************************
 *
 * File: src/MushCollision/MushCollisionPiece.h
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
//%Header } LX43K9AXZEla1+GuWUipSA
/*
 * $Id: MushCollisionPiece.h,v 1.6 2007/04/18 09:22:31 southa Exp $
 * $Log: MushCollisionPiece.h,v $
 * Revision 1.6  2007/04/18 09:22:31  southa
 * Header and level fixes
 *
 * Revision 1.5  2006/11/14 20:28:37  southa
 * Added rail gun
 *
 * Revision 1.4  2006/06/01 15:39:15  southa
 * DrawArray verification and fixes
 *
 * Revision 1.3  2005/07/30 19:06:14  southa
 * Collision checking
 *
 * Revision 1.2  2005/07/29 08:27:47  southa
 * Collision work
 *
 * Revision 1.1  2005/07/27 18:09:59  southa
 * Collision checking
 *
 */

#include "MushCollisionStandard.h"

#include "MushCollisionWorkspace.h"

//:generate virtual standard ostream xml1
class MushCollisionPiece : public virtual MushcoreVirtualObject
{
public:
    MushCollisionPiece() : m_shrinkFactor(1.0) {}
    virtual ~MushCollisionPiece() {}
    virtual const MushMesh4Mesh& CollisionMesh(void) const;
    virtual const MushMeshPosticity& CollisionPost(void) const;
    virtual bool CollisionIsWCylinder(void) const;
    const Mushware::t4Val& CollisionWorldCentroid(void) const;
    Mushware::tVal CollisionBoundingRadius(void) const;
    const MushCollisionWorkspace::tChunkCentroids& CollisionChunkWorldCentroids(void) const;
    
    void CollisionResetIfNeeded(Mushware::tMsec inFrameMsec) const { m_collSpace.ResetIfNeeded(inFrameMsec); }
    
protected:
    void CollisionChunkWorldCentroidsBuild(void) const;
        
private:
    Mushware::tVal m_shrinkFactor; //:readwrite
    mutable MushCollisionWorkspace m_collSpace;
    
//%classPrototypes {
public:
    const Mushware::tVal& ShrinkFactor(void) const { return m_shrinkFactor; }
    void ShrinkFactorSet(const Mushware::tVal& inValue) { m_shrinkFactor=inValue; }
    virtual const char *AutoName(void) const;
    virtual MushcoreVirtualObject *AutoClone(void) const;
    virtual MushcoreVirtualObject *AutoCreate(void) const;
    static MushcoreVirtualObject *AutoVirtualFactory(void);
    virtual void AutoPrint(std::ostream& ioOut) const;
    virtual bool AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr);
    virtual void AutoXMLPrint(MushcoreXMLOStream& ioOut) const;
//%classPrototypes } fuWU4SUp/NTWTjOSg8Cpzw
};

inline const Mushware::t4Val&
MushCollisionPiece::CollisionWorldCentroid(void) const
{
    if (!m_collSpace.CentroidValid())
    {
        m_collSpace.CentroidSet(CollisionMesh().Centroid());
        MushMeshOps::ObjectToWorld(m_collSpace.CentroidWRef(), CollisionPost());
        m_collSpace.CentroidValidSet(true);
    }
    MUSHCOREASSERT(m_collSpace.CentroidValid());
    return m_collSpace.Centroid();
}

inline Mushware::tVal
MushCollisionPiece::CollisionBoundingRadius(void) const
{
    return CollisionMesh().BoundingRadius();
}

inline const MushCollisionWorkspace::tChunkCentroids&
MushCollisionPiece::CollisionChunkWorldCentroids(void) const
{
    if (!m_collSpace.ChunkCentroidsValid())
    {
        CollisionChunkWorldCentroidsBuild();
    }
    MUSHCOREASSERT(m_collSpace.ChunkCentroidsValid());
    return m_collSpace.ChunkCentroids();
}


//%inlineHeader {
inline std::ostream&
operator<<(std::ostream& ioOut, const MushCollisionPiece& inObj)
{
    inObj.AutoPrint(ioOut);
    return ioOut;
}
//%inlineHeader } XQTIeqimgagFnNrboO+2uA

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
