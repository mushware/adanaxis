//%includeGuardStart {
#ifndef MUSHMESHLIBRARYUTIL_H
#define MUSHMESHLIBRARYUTIL_H
//%includeGuardStart } RsojrpT3oal1DIS1EOEsIQ
//%Header {
/*****************************************************************************
 *
 * File: src/MushMeshLibrary/MushMeshLibraryUtil.h
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
//%Header } dTepjkjze3ED1TtgNY790w
/*
 * $Id$
 * $Log$
 */

#include "MushMeshLibraryStandard.h"

class MushMeshLibraryUtil
{
public:
    static void NewFaceCreate(MushMesh4Mesh& ioMesh,
                              MushMesh4Face *& outpFace,
                              MushMesh4Face::tVertexList *& outpVertexList,
                              MushMesh4Face::tVertexGroupSize *& outpVertexGroupSize);
    static void NewChunkCreate(MushMesh4Mesh& ioMesh);
    
private:
    
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
