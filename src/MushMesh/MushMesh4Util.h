//%includeGuardStart {
#ifndef MUSHMESH4UTIL_H
#define MUSHMESH4UTIL_H
//%includeGuardStart } a/ave7GSPVe/ckZ8GEFF1w
//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMesh4Util.h
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
//%Header } +uUR7rbL2rltWokU3LkyQA
/*
 * $Id: MushMesh4Util.h,v 1.3 2006/06/01 15:39:28 southa Exp $
 * $Log: MushMesh4Util.h,v $
 * Revision 1.3  2006/06/01 15:39:28  southa
 * DrawArray verification and fixes
 *
 * Revision 1.2  2005/08/01 17:58:25  southa
 * Object explosion
 *
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
