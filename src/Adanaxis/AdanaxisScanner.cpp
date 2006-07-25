//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisScanner.cpp
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
//%Header } G8Z0FhC/G4lBOZEeeMzYgA
/*
 * $Id$
 * $Log$
 */

#include "AdanaxisScanner.h"

using namespace Mushware;
using namespace std;

AdanaxisScanner::AdanaxisScanner() :
    m_symbolSize(4,4),
    m_symbolFontRef("symbol1-font")
{
    
}

void
AdanaxisScanner::ScanSymbolRender(Mushware::t4Val& inPos, Mushware::t4Val inParam)
{
    MushGLFont& fontRef = m_symbolFontRef.WRef();
    
    fontRef.ColourSet(t4Val(1,1,1,1));
    fontRef.RenderSymbolAtSize(kSymbolScanWhite, inPos, m_symbolSize);
    
    tVal radius = 2.5;
    tVal xAngle = atan2(inParam.X(), inParam.W());
    t4Val xOffset = t4Val(radius * sin(xAngle), radius * -cos(xAngle), 0, 0);
    fontRef.RenderSymbolAtSize(kSymbolScanX, inPos + xOffset, m_symbolSize * 0.2);
    tVal yAngle = atan2(inParam.Y(), inParam.W());
    t4Val yOffset = t4Val(radius * sin(yAngle), radius * -cos(yAngle), 0, 0);
    fontRef.RenderSymbolAtSize(kSymbolScanY, inPos + yOffset, m_symbolSize * 0.2);
    tVal zAngle = atan2(inParam.Z(), inParam.W());
    t4Val zOffset = t4Val(radius * sin(zAngle), radius * -cos(zAngle), 0, 0);
    fontRef.RenderSymbolAtSize(kSymbolScanZ, inPos + zOffset, m_symbolSize * 0.2);
    t4Val wOffset = t4Val(0, (inPos.W() > 0) ? 3.5 : -3.5, 0, 0);
    fontRef.RenderSymbolAtSize(kSymbolScanW, inPos + wOffset, m_symbolSize * 0.2);
}

void
AdanaxisScanner::ScanObjectRender(AdanaxisLogic& ioLogic, MushRenderMesh *inpMeshRender,
                                  const MushGameCamera& inCamera, const MushMeshPosticity& inPost,
                                  const MushMesh4Mesh& inMesh, Mushware::U32 inObjType)
{
    MUSHCOREASSERT(inpMeshRender != NULL);
    
    MushMeshPosticity scanPost = inPost;
    MushMeshPosticity cameraPost = inCamera.Post();
    
    // scanPost.PosWRef().Normalise();

    MushRenderSpec renderSpec;
    MushMeshOps::PosticityToMattress(renderSpec.ModelWRef(), scanPost);
    MushMeshOps::PosticityToMattress(renderSpec.ViewWRef(), cameraPost);
    renderSpec.ViewWRef().InPlaceInvert();    
    renderSpec.ProjectionSet(inCamera.Projection());
    
    t4Val clipPos = renderSpec.ModelToClipMattress() * t4Val(0,0,0,0); // inMesh.Centroid();
    t4Val eyePos = renderSpec.ModelToEyeMattress() * t4Val(0,0,0,0); // inMesh.Centroid();
    ScanSymbolRender(clipPos, eyePos);
}

//%outOfLineFunctions {

const char *AdanaxisScanner::AutoName(void) const
{
    return "AdanaxisScanner";
}

MushcoreVirtualObject *AdanaxisScanner::AutoClone(void) const
{
    return new AdanaxisScanner(*this);
}

MushcoreVirtualObject *AdanaxisScanner::AutoCreate(void) const
{
    return new AdanaxisScanner;
}

MushcoreVirtualObject *AdanaxisScanner::AutoVirtualFactory(void)
{
    return new AdanaxisScanner;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("AdanaxisScanner", AdanaxisScanner::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
AdanaxisScanner::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "symbolSize=" << m_symbolSize << ", ";
    ioOut << "symbolFontRef=" << m_symbolFontRef;
    ioOut << "]";
}
bool
AdanaxisScanner::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "symbolSize")
    {
        ioIn >> m_symbolSize;
    }
    else if (inTagStr == "symbolFontRef")
    {
        ioIn >> m_symbolFontRef;
    }
    else 
    {
        return false;
    }
    return true;
}
void
AdanaxisScanner::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("symbolSize");
    ioOut << m_symbolSize;
    ioOut.TagSet("symbolFontRef");
    ioOut << m_symbolFontRef;
}
//%outOfLineFunctions } 2/cipfgQzQbubvmpeqKf8A
