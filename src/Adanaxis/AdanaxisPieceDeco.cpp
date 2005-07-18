//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisPieceDeco.cpp
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
//%Header } sexYl99zeFqxCTpAO8DLNQ
/*
 * $Id: AdanaxisPieceDeco.cpp,v 1.9 2005/07/06 19:08:26 southa Exp $
 * $Log: AdanaxisPieceDeco.cpp,v $
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
    m_id(inID)
{
    PostWRef().ToIdentitySet();
    m_buffersRef.NameSet(MushGLBuffers::NextBufferNumAdvance());
    MushGLBuffers::tData::Sgl().GetOrCreate(m_buffersRef.Name());    
}

void
AdanaxisPieceDeco::Render(MushGameLogic& ioLogic, MushRenderMesh& inRender, const MushGameCamera& inCamera)
{
    PostWRef().InPlaceVelocityAdd();
    MushRenderSpec renderSpec;
    renderSpec.BuffersRefSet(m_buffersRef);
        
    MushMeshPosticity viewOffset;
    MushMeshPosticity viewAng;
    
    viewOffset.ToIdentitySet();
    viewOffset.PosSet(t4Val(0,0,0,0)-inCamera.Post().Pos());
    
    viewAng.ToIdentitySet();
    viewAng.AngPosSet(inCamera.Post().AngPos().Conjugate());
    
    MushMeshOps::PosticityToMattress(renderSpec.ModelWRef(), Post());
    MushMeshOps::PosticityToMattress(renderSpec.SpecialWRef(), viewOffset);
    MushMeshOps::PosticityToMattress(renderSpec.ViewWRef(), viewAng);

    renderSpec.ProjectionSet(inCamera.Projection());
    
    static U32 ctr=0;
    
    if (ctr++ < 0)
    {
        MushcoreXMLOStream xmlOut(std::cout);
        std::cout << "Camera " << inCamera << endl;
        xmlOut << inCamera;
        std::cout << "RenderSpec " << renderSpec << endl;
        xmlOut << renderSpec;
    }
    
    inRender.MeshRender(renderSpec, m_mesh);
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
    ioOut << "id=" << m_id << ", ";
    ioOut << "mesh=" << m_mesh << ", ";
    ioOut << "buffersRef=" << m_buffersRef;
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
    else if (inTagStr == "id")
    {
        ioIn >> m_id;
    }
    else if (inTagStr == "mesh")
    {
        ioIn >> m_mesh;
    }
    else if (inTagStr == "buffersRef")
    {
        ioIn >> m_buffersRef;
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
    ioOut.TagSet("id");
    ioOut << m_id;
    ioOut.TagSet("mesh");
    ioOut << m_mesh;
    ioOut.TagSet("buffersRef");
    ioOut << m_buffersRef;
}
//%outOfLineFunctions } 8IECvxeHlwRBQh1H5NuTiQ
