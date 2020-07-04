//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisPieceWorld.cpp
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
//%Header } QIL+woYy2hzA4Tfon2oT6w
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
