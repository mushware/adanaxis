//%includeGuardStart {
#ifndef MUSHMESH_H
#define MUSHMESH_H
//%includeGuardStart } ThUO79ZBnDYvVIfZtUlf4Q
//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMesh.h
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
//%Header } FL6R59LsvAqRdS83O7ypEQ
/*
 * $Id: MushMesh.h,v 1.32 2006/06/19 15:57:17 southa Exp $
 * $Log: MushMesh.h,v $
 * Revision 1.32  2006/06/19 15:57:17  southa
 * Materials
 *
 * Revision 1.31  2006/06/16 01:02:31  southa
 * Ruby mesh generation
 *
 * Revision 1.30  2006/06/14 18:45:47  southa
 * Ruby mesh generation
 *
 * Revision 1.29  2006/06/14 11:20:06  southa
 * Ruby mesh generation
 *
 * Revision 1.28  2006/05/01 17:39:00  southa
 * Texture generation
 *
 * Revision 1.27  2005/07/19 13:44:26  southa
 * MushMesh4Chunk work
 *
 * Revision 1.26  2005/07/18 13:13:36  southa
 * Extrude to point and projectile mesh
 *
 * Revision 1.25  2005/07/12 20:39:04  southa
 * Mesh library work
 *
 * Revision 1.24  2005/07/02 00:42:38  southa
 * Conditioning tweaks
 *
 * Revision 1.23  2005/06/30 12:04:55  southa
 * Mesh work
 *
 * Revision 1.22  2005/06/24 10:30:13  southa
 * MushGame camera work
 *
 * Revision 1.21  2005/05/19 13:02:09  southa
 * Mac release work
 *
 * Revision 1.20  2005/02/03 21:02:59  southa
 * Build fixes
 *
 * Revision 1.19  2005/02/03 15:46:51  southa
 * Quaternion work
 *
 * Revision 1.18  2005/01/27 21:00:39  southa
 * Division and rendering
 *
 * Revision 1.17  2005/01/26 00:48:46  southa
 * MushMeshGroup and rendering
 *
 * Revision 1.16  2004/12/06 20:44:17  southa
 * Quaternion and matrix operations
 *
 * Revision 1.15  2004/11/17 23:43:47  southa
 * Added outer product
 *
 * Revision 1.14  2004/10/31 23:34:06  southa
 * Hypercube rendering test
 *
 * Revision 1.13  2004/10/31 09:22:51  southa
 * Added MushMeshPreMatrix
 *
 * Revision 1.12  2004/01/04 17:02:30  southa
 * MushPie extras and MushcoreIO fixes
 *
 * Revision 1.11  2004/01/02 21:13:10  southa
 * Source conditioning
 *
 * Revision 1.10  2003/10/26 10:05:30  southa
 * End patch testing
 *
 * Revision 1.9  2003/10/25 11:08:17  southa
 * Triangular mesh work
 *
 * Revision 1.8  2003/10/23 20:03:57  southa
 * End mesh work
 *
 * Revision 1.7  2003/10/20 13:02:53  southa
 * Patch fixes and testing
 *
 * Revision 1.6  2003/10/18 20:28:38  southa
 * Subdivision speed tests
 *
 * Revision 1.5  2003/10/17 12:27:18  southa
 * Line end fixes and more mesh work
 *
 * Revision 1.4  2003/10/15 12:26:58  southa
 * MushMeshArray neighbour testing and subdivision work
 *
 * Revision 1.3  2003/10/15 11:54:53  southa
 * MushMeshArray neighbour testing and subdivision
 *
 * Revision 1.2  2003/10/15 07:08:28  southa
 * MushMeshArray creation
 *
 * Revision 1.1  2003/10/14 13:07:25  southa
 * MushMesh vector creation
 *
 */

#include "MushMesh4Base.h"
#include "MushMesh4Chunk.h"
#include "MushMesh4Extruder.h"
#include "MushMesh4Face.h"
#include "MushMesh4FaceGenerator.h"
#include "MushMesh4LinkFaceFace.h"
#include "MushMesh4Maker.h"
#include "MushMesh4Material.h"
#include "MushMesh4Mesh.h"
#include "MushMesh4TextureTile.h"
#include "MushMesh4VertexGenerator.h"
#include "MushMesh4Util.h"
#include "MushMeshArray.h"
#include "MushMeshBox.h"
#include "MushMeshConnector.h"
#include "MushMeshDisplacement.h"
#include "MushMeshDivide.h"
#include "MushMeshFace.h"
#include "MushMeshGroup.h"
#include "MushMeshMattress.h"
#include "MushMeshMesh.h"
#include "MushMeshOps.h"
#include "MushMeshPatch.h"
#include "MushMeshPatchEnd.h"
#include "MushMeshPatchPipe.h"
#include "MushMeshPostMatrix.h"
#include "MushMeshPosticity.h"
#include "MushMeshPreMatrix.h"
#include "MushMeshQuaternion.h"
#include "MushMeshQuaternionPair.h"
// MushMeshSubdivide.h excluded
#include "MushMeshTools.h"
#include "MushMeshTriangularArray.h"
#include "MushMeshVector.h"
#include "MushMeshUtils.h"
#include "MushMeshWorkspace.h"
#include "MushMeshWorkspaceBased.h"

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
