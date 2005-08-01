//%includeGuardStart {
#ifndef MUSHMESH4UTIL_H
#define MUSHMESH4UTIL_H
//%includeGuardStart } a/ave7GSPVe/ckZ8GEFF1w
//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMesh4Util.h
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
//%Header } 2cFNAx1PC6mGg3Cf2ei4UQ
/*
 * $Id: MushMesh4Util.h,v 1.1 2005/07/18 13:13:36 southa Exp $
 * $Log: MushMesh4Util.h,v $
 * Revision 1.1  2005/07/18 13:13:36  southa
 * Extrude to point and projectile mesh
 *
 */

#include "MushMeshStandard.h"

#include "MushMesh4Mesh.h"

class MushMesh4Util
{
public:
    static void NewFaceCreate(MushMesh4Mesh& ioMesh,
                              MushMesh4Face *& outpFace,
                              MushMesh4Face::tVertexList *& outpVertexList,
                              MushMesh4Face::tVertexGroupSize *& outpVertexGroupSize);
    static void NewFaceClone(MushMesh4Mesh& ioMesh,
                             MushMesh4Face *& outpFace,
                             MushMesh4Face::tVertexList *& outpVertexList,
                             MushMesh4Face::tVertexGroupSize *& outpVertexGroupSize,
                             const MushMesh4Face& inFace);
    static void NewChunkCreate(MushMesh4Mesh& ioMesh);
    
    static void NullFacetsRemove(MushMesh4Mesh& ioMesh, Mushware::U32 inFaceNum);
    static void ChunkCopy(MushMesh4Mesh& ioMesh, const MushMesh4Mesh& inMesh, Mushware::U32 inChunkNum);
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
