//%includeGuardStart {
#ifndef MUSHMESH_H
#define MUSHMESH_H
//%includeGuardStart } ThUO79ZBnDYvVIfZtUlf4Q
//%Header {
/*****************************************************************************
 *
 * File: src/MushMesh/MushMesh.h
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
//%Header } cwZJKyFY1QFkq3q40herNg
/*
 * $Id: MushMesh.h,v 1.27 2005/07/19 13:44:26 southa Exp $
 * $Log: MushMesh.h,v $
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

#include "MushMesh4Chunk.h"
#include "MushMesh4Face.h"
#include "MushMesh4FaceGenerator.h"
#include "MushMesh4LinkFaceFace.h"
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
#include "MushMeshMaterialRef.h"
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
