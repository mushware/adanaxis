//%Header {
/*****************************************************************************
 *
 * File: src/MushRender/MushRenderMesh.cpp
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
//%Header } nAlXQAIXh98l6rrr70+y5w
/*
 * $Id: MushRenderMesh.cpp,v 1.4 2006/06/01 15:39:38 southa Exp $
 * $Log: MushRenderMesh.cpp,v $
 * Revision 1.4  2006/06/01 15:39:38  southa
 * DrawArray verification and fixes
 *
 * Revision 1.3  2005/07/04 11:10:43  southa
 * Rendering pipeline
 *
 * Revision 1.2  2005/07/02 00:42:38  southa
 * Conditioning tweaks
 *
 * Revision 1.1  2005/07/01 10:36:46  southa
 * MushRender work
 *
 */

#include "MushRenderMesh.h"

using namespace Mushware;
using namespace std;

void
MushRenderMesh::MeshRender(const MushRenderSpec& inSpec, const MushMeshMesh& inMesh)
{
    // No render output
}

bool
MushRenderMesh::RenderJobCreate(MushGLJobRender& outRender,
                                const MushRenderSpec& inSpec,
                                const MushMeshMesh& inMesh)
{
    // Never creates a render job
    return false;
}

Mushware::tVal
MushRenderMesh::SortDepth(const MushRenderSpec& inSpec, const MushMesh4Mesh& inMesh)
{
    t4Val objCentre = inMesh.Centroid();
    objCentre = inSpec.ModelToEyeMattress() * objCentre;
    return objCentre.W();
}

bool
MushRenderMesh::ShouldMeshCull(const MushRenderSpec& inSpec, const MushMesh4Mesh& inMesh)
{
    // Transform mesh centroid to eye coordinates
    t4Val objCentre = inMesh.Centroid();
    objCentre = inSpec.ModelToEyeMattress() * objCentre;
    tVal boundingRadius = inMesh.BoundingRadius();
    
    const t4Val& clipMin = inSpec.Projection().ClipMin();
    const t4Val& clipMax = inSpec.Projection().ClipMax();
    const t4Val& brFactor = inSpec.Projection().BoundingRadiusFactor();
    
    /* Cull unless the centre of the object is within a bounding radius of
     * any part of the view frustum
     */
    return (//objCentre.W() + boundingRadius < clipMin.W() ||
            //objCentre.W() - boundingRadius > clipMax.W() ||
            objCentre.X() + boundingRadius * brFactor.X() < clipMin.X() * -objCentre.W() ||
            objCentre.X() - boundingRadius * brFactor.X() > clipMax.X() * -objCentre.W() ||
            objCentre.Y() + boundingRadius * brFactor.Y() < clipMin.Y() * -objCentre.W() ||
            objCentre.Y() - boundingRadius * brFactor.Y() > clipMax.Y() * -objCentre.W() ||
            objCentre.Z() + boundingRadius * brFactor.Z() < clipMin.Z() * -objCentre.W() ||
            objCentre.Z() - boundingRadius * brFactor.Z() > clipMax.Z() * -objCentre.W());
}

//%outOfLineFunctions {

const char *MushRenderMesh::AutoName(void) const
{
    return "MushRenderMesh";
}

MushcoreVirtualObject *MushRenderMesh::AutoClone(void) const
{
    return new MushRenderMesh(*this);
}

MushcoreVirtualObject *MushRenderMesh::AutoCreate(void) const
{
    return new MushRenderMesh;
}

MushcoreVirtualObject *MushRenderMesh::AutoVirtualFactory(void)
{
    return new MushRenderMesh;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushRenderMesh", MushRenderMesh::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushRenderMesh::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "]";
}
bool
MushRenderMesh::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else 
    {
        return false;
    }
    return true;
}
void
MushRenderMesh::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
}
//%outOfLineFunctions } qaoiRfg+HPe2DQ7C+MKFKw
