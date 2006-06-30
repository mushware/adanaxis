//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisPieceDeco.cpp
 *
 * Copyright: Andy Southgate 2005-2006
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
//%Header } Kb73MSBnaByz2lwXVLGZkA
/*
 * $Id: AdanaxisPieceDeco.cpp,v 1.16 2006/06/27 11:58:08 southa Exp $
 * $Log: AdanaxisPieceDeco.cpp,v $
 * Revision 1.16  2006/06/27 11:58:08  southa
 * Warning fixes
 *
 * Revision 1.15  2006/06/21 16:52:28  southa
 * Deco objects
 *
 * Revision 1.14  2006/06/01 15:38:47  southa
 * DrawArray verification and fixes
 *
 * Revision 1.13  2005/08/02 11:11:47  southa
 * Adanaxis control demo work
 *
 * Revision 1.12  2005/08/01 20:24:15  southa
 * Backdrop and build fixes
 *
 * Revision 1.11  2005/07/19 10:08:06  southa
 * Adanaxis work
 *
 * Revision 1.10  2005/07/18 13:13:35  southa
 * Extrude to point and projectile mesh
 *
 * Revision 1.9  2005/07/06 19:08:26  southa
 * Adanaxis control work
 *
 * Revision 1.8  2005/07/05 16:35:53  southa
 * Adanaxis work
 *
 * Revision 1.7  2005/07/05 13:52:22  southa
 * Adanaxis work
 *
 * Revision 1.6  2005/07/04 15:59:00  southa
 * Adanaxis work
 *
 * Revision 1.5  2005/07/04 11:10:43  southa
 * Rendering pipeline
 *
 * Revision 1.4  2005/07/02 00:42:36  southa
 * Conditioning tweaks
 *
 * Revision 1.3  2005/07/01 10:36:46  southa
 * MushRender work
 *
 * Revision 1.2  2005/06/30 16:29:24  southa
 * Adanaxis work
 *
 * Revision 1.1  2005/06/30 14:26:35  southa
 * Adanaxis work
 *
 */

#include "AdanaxisPieceDeco.h"

using namespace Mushware;
using namespace std;

AdanaxisPieceDeco::AdanaxisPieceDeco(const std::string& inID) :
    MushGamePiece(inID)
{
}

void
AdanaxisPieceDeco::Render(MushGameLogic& ioLogic, MushRenderMesh& inRender, const MushGameCamera& inCamera)
{
    bool visible = true;
    t4Val objNormal = Post().Pos();
	
    objNormal.InPlaceNormalise();
    t4Val viewNormal = t4Val(0,0,0,-1);
    
    inCamera.Post().AngPos().VectorRotate(viewNormal);
    
    visible = (objNormal * viewNormal > 0.9);
    
    if (visible, 1)
    {
        PostWRef().InPlaceVelocityAdd();

        MushGameCamera newCamera(inCamera);
        newCamera.PostWRef().PosWRef().ToAdditiveIdentitySet();

        MushRenderSpec renderSpec;
        renderSpec.BuffersRefSet(BuffersRef());
		renderSpec.TexCoordBuffersRefSet(TexCoordBuffersRef());

        MushMeshOps::PosticityToMattress(renderSpec.ModelWRef(), Post());
        MushMeshOps::PosticityToMattress(renderSpec.ViewWRef(), newCamera.Post());
        renderSpec.ViewWRef().InPlaceInvert();
        
        renderSpec.ProjectionSet(inCamera.Projection());
        
        inRender.MeshRender(renderSpec, Mesh());
    }
}

//%outOfLineFunctions {

const char *AdanaxisPieceDeco::AutoName(void) const
{
    return "AdanaxisPieceDeco";
}

MushcoreVirtualObject *AdanaxisPieceDeco::AutoClone(void) const
{
    return new AdanaxisPieceDeco(*this);
}

MushcoreVirtualObject *AdanaxisPieceDeco::AutoCreate(void) const
{
    return new AdanaxisPieceDeco;
}

MushcoreVirtualObject *AdanaxisPieceDeco::AutoVirtualFactory(void)
{
    return new AdanaxisPieceDeco;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("AdanaxisPieceDeco", AdanaxisPieceDeco::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
AdanaxisPieceDeco::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushGamePiece::AutoPrint(ioOut);
    ioOut << "]";
}
bool
AdanaxisPieceDeco::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (MushGamePiece::AutoXMLDataProcess(ioIn, inTagStr))
    {
        // Tag consumed by base class
    }
    else 
    {
        return false;
    }
    return true;
}
void
AdanaxisPieceDeco::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushGamePiece::AutoXMLPrint(ioOut);
}
//%outOfLineFunctions } C4QJXOg4sML405P71FzJlQ
