//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisPieceWorld.cpp
 *
 * Copyright: Andy Southgate 2005-2007
 *
 * This file may be used and distributed under the terms of the Mushware
 * Software Licence version 1.4, under the terms for 'Proprietary original
 * source files'.  If not supplied with this software, a copy of the licence
 * can be obtained from Mushware Limited via http://www.mushware.com/.
 * One of your options under that licence is to use and distribute this file
 * under the terms of the GNU General Public Licence version 2.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 3AMlL/j+D1DwbIjtGT5T0A
/*
 * $Id: AdanaxisPieceWorld.cpp,v 1.5 2007/04/18 09:22:02 southa Exp $
 * $Log: AdanaxisPieceWorld.cpp,v $
 * Revision 1.5  2007/04/18 09:22:02  southa
 * Header and level fixes
 *
 * Revision 1.4  2006/09/09 11:16:39  southa
 * One-time vertex buffer generation
 *
 * Revision 1.3  2006/08/01 17:21:26  southa
 * River demo
 *
 * Revision 1.2  2006/07/24 18:46:47  southa
 * Depth sorting
 *
 * Revision 1.1  2006/07/19 10:22:15  southa
 * World objects
 *
 */

#include "AdanaxisPieceWorld.h"

using namespace Mushware;
using namespace std;

AdanaxisPieceWorld::AdanaxisPieceWorld(const std::string& inID) :
MushGamePiece(inID)
{
}

void
AdanaxisPieceWorld::Render(MushGameLogic& ioLogic, MushRenderMesh& inRender, const MushGameCamera& inCamera)
{

    PostWRef().InPlaceVelocityAdd();
    
    MushGameCamera newCamera(inCamera);
    newCamera.PostWRef().PosWRef().ToAdditiveIdentitySet();
    
    MushRenderSpec renderSpec;
    renderSpec.BuffersRefSet(BuffersRef());
    renderSpec.SharedBuffersRefSet(SharedBuffersRef());
    
    MushMeshOps::PosticityToMattress(renderSpec.ModelWRef(), Post());
    MushMeshOps::PosticityToMattress(renderSpec.ViewWRef(), newCamera.Post());
    renderSpec.ViewWRef().InPlaceInvert();
    
    renderSpec.ProjectionSet(inCamera.Projection());
    
    inRender.MeshRender(renderSpec, Mesh());
}

//%outOfLineFunctions {

const char *AdanaxisPieceWorld::AutoName(void) const
{
    return "AdanaxisPieceWorld";
}

MushcoreVirtualObject *AdanaxisPieceWorld::AutoClone(void) const
{
    return new AdanaxisPieceWorld(*this);
}

MushcoreVirtualObject *AdanaxisPieceWorld::AutoCreate(void) const
{
    return new AdanaxisPieceWorld;
}

MushcoreVirtualObject *AdanaxisPieceWorld::AutoVirtualFactory(void)
{
    return new AdanaxisPieceWorld;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("AdanaxisPieceWorld", AdanaxisPieceWorld::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
AdanaxisPieceWorld::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushGamePiece::AutoPrint(ioOut);
    ioOut << "]";
}
bool
AdanaxisPieceWorld::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
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
AdanaxisPieceWorld::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushGamePiece::AutoXMLPrint(ioOut);
}
//%outOfLineFunctions } nWxX8rEvhCDQjM6MrQ5/xQ
