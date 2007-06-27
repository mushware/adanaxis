//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisScanner.cpp
 *
 * Copyright: Andy Southgate 2005-2007
 *
 * This file may be used and distributed under the terms of the Mushware
 * Software Licence version 1.3, under the terms for 'Proprietary original
 * source files'.  If not supplied with this software, a copy of the licence
 * can be obtained from Mushware Limited via http://www.mushware.com/.
 * One of your options under that licence is to use and distribute this file
 * under the terms of the GNU General Public Licence version 2.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } Wn9CtHgzeIT2Muk6Sf8H8A
/*
 * $Id: AdanaxisScanner.cpp,v 1.14 2007/04/18 09:22:04 southa Exp $
 * $Log: AdanaxisScanner.cpp,v $
 * Revision 1.14  2007/04/18 09:22:04  southa
 * Header and level fixes
 *
 * Revision 1.13  2007/04/16 08:41:09  southa
 * Level and header mods
 *
 * Revision 1.12  2007/03/13 18:21:37  southa
 * Scanner jamming
 *
 * Revision 1.11  2007/03/13 12:22:51  southa
 * Scanner symbols
 *
 * Revision 1.10  2007/03/12 21:06:00  southa
 * Scanner symbols
 *
 * Revision 1.9  2006/11/12 20:09:55  southa
 * Missile guidance
 *
 * Revision 1.8  2006/10/20 15:38:52  southa
 * Item collection
 *
 * Revision 1.7  2006/10/09 16:00:16  southa
 * Intern generation
 *
 * Revision 1.6  2006/08/01 17:21:29  southa
 * River demo
 *
 * Revision 1.5  2006/07/30 19:38:52  southa
 * Level updates
 *
 * Revision 1.4  2006/07/28 19:24:34  southa
 * Pre-release work
 *
 * Revision 1.3  2006/07/25 20:31:03  southa
 * Scanner work
 *
 * Revision 1.2  2006/07/25 15:03:08  southa
 * Scanner work
 *
 * Revision 1.1  2006/07/25 13:30:57  southa
 * Initial scanner work
 *
 */

#include "AdanaxisScanner.h"

using namespace Mushware;
using namespace std;

AdanaxisScanner::AdanaxisScanner() :
    m_symbolSize(4,4),
    m_symbolFontRef("symbol1-font"),
    m_sightAngle(0),
    m_targetState(kTargetStateIdle),
    m_targetHitPointRatio(0)
{

}

void
AdanaxisScanner::ScanSymbolRender(Mushware::t4Val& inPos, Mushware::t4Val inParam,
                                  Mushware::tVal inAlpha, Mushware::U32 inSymbol)
{
    MushGLFont& fontRef = m_symbolFontRef.WRef();

    fontRef.ColourSet(t4Val(1,1,1,inAlpha));
    fontRef.RenderSymbolAtSize(inSymbol, inPos, m_symbolSize);

    fontRef.ColourSet(t4Val(1,1,1,std::pow(1.0*inAlpha, 0.4)));

    tVal outerRadius = 0.7;
    tVal dotSize = 0.3;
    t4Val wOffset = t4Val(0, 0, 0, 0);
    // fontRef.RenderSymbolAtSize(kSymbolScanW, inPos + wOffset, m_symbolSize * dotSize);

    tVal xAngle = atan2(inParam.X(), inParam.W());
    xAngle = M_PI * pow(xAngle/M_PI, 7);
    t4Val xOffset = t4Val(m_symbolSize.X() * outerRadius * sin(xAngle), m_symbolSize.Y() * outerRadius * -cos(xAngle), 0, 0);
    fontRef.RenderSymbolAtSize(kSymbolScanX, inPos + xOffset, m_symbolSize * dotSize);

    tVal yAngle = atan2(inParam.Y(), inParam.W());
    yAngle = M_PI * pow(yAngle/M_PI, 7);
    t4Val yOffset = t4Val(m_symbolSize.X() * outerRadius * sin(yAngle), m_symbolSize.Y() * outerRadius * -cos(yAngle), 0, 0);
    fontRef.RenderSymbolAtSize(kSymbolScanY, inPos + yOffset, m_symbolSize * dotSize);

    tVal zAngle = atan2(inParam.Z(), inParam.W());
    zAngle = M_PI * pow(zAngle/M_PI, 7);
    t4Val zOffset = t4Val(m_symbolSize.X() * outerRadius * sin(zAngle), m_symbolSize.Y() * outerRadius * -cos(zAngle), 0, 0);
    fontRef.RenderSymbolAtSize(kSymbolScanZ, inPos + zOffset, m_symbolSize * dotSize);
}

void
AdanaxisScanner::ScanObjectRender(AdanaxisLogic& ioLogic, MushRenderMesh *inpMeshRender,
                                  const MushGameCamera& inCamera, const MushGamePiece& inPiece,
                                  Mushware::U32 inObjType)
{
    MUSHCOREASSERT(inpMeshRender != NULL);

    MushMeshPosticity objPost = inPiece.Post();
    MushMeshPosticity cameraPost = inCamera.Post();
    const MushMesh4Mesh& meshRef = inPiece.Mesh();

    // t4Val cameraToObj = objPost.Pos() - cameraPos.Pos();

    objPost.PosWRef() -= cameraPost.Pos();
    cameraPost.AngPosWRef().Conjugate().VectorRotate(objPost.PosWRef());
    cameraPost.PosWRef() -= cameraPost.Pos();
    cameraPost.AngPosWRef().ToRotationIdentitySet();

    MushRenderSpec renderSpec;
    MushMeshOps::PosticityToMattress(renderSpec.ModelWRef(), objPost);
    MushMeshOps::PosticityToMattress(renderSpec.ViewWRef(), cameraPost);
    renderSpec.ViewWRef().InPlaceInvert();
    renderSpec.ProjectionSet(inCamera.Projection());

    t4Val eyePos = renderSpec.ModelToEyeMattress() * t4Val(0,0,0,0);

    // Check whether the camera is on target on this object
    if (inObjType == kObjectTypeKhazi && m_targetState != kTargetStateOnTarget)
    {
        tVal boundingRadius = meshRef.BoundingRadius();
        t4Val centroidPos = renderSpec.ModelToEyeMattress() * meshRef.Centroid();
        if (centroidPos.W() < boundingRadius && centroidPos.W() != 0)
        {
            // Distance from the w axis is sqrt(x^2+y^2+z^2), so set w to 0 and take magnitude
            centroidPos.WSet(0);
            tVal distFromWAxis = centroidPos.Magnitude();
            if (distFromWAxis < boundingRadius)
            {
                // Bounding sphere intersects th w axis, so set in boundary
                m_targetState = kTargetStateInBoundary;
                m_targetHitPointRatio = inPiece.HitPointRatio();
                m_targetID = inPiece.Id();
                U32 numChunks = meshRef.NumChunks();
                for (U32 i=0; i<numChunks; ++i)
                {
                    tVal chunkRadius = meshRef.ChunkBoundingRadius(i);
                    t4Val chunkCentroidPos = renderSpec.ModelToEyeMattress() * meshRef.ChunkCentroid(i);
                    chunkCentroidPos.WSet(0);
                    if (chunkCentroidPos.Magnitude() < chunkRadius)
                    {
                        // Bounding sphere on a chunk intersects th w axis, so set on target
                        m_targetState = kTargetStateOnTarget;
                        break;
                    }
                }
            }
        }
    }

    tVal angleRunOff = M_PI/50;
    tVal xwAngleLimit = renderSpec.Projection().XHalfAngle() - angleRunOff;
    tVal ywAngleLimit = renderSpec.Projection().YHalfAngle() - angleRunOff;
    tVal xwAngle = atan2(objPost.Pos().X(), -objPost.Pos().W());

    tVal alpha = 1;

    if (std::fabs(xwAngle) > xwAngleLimit)
    {
        tVal runOffFraction = (std::fabs(xwAngle) - xwAngleLimit) / (M_PI - xwAngleLimit);
        tVal newXWAngle =  xwAngleLimit + angleRunOff * (1- pow(1-runOffFraction, 4));
        if (xwAngle < 0) newXWAngle = -newXWAngle;
        MushMeshTools::QuaternionRotateInAxis(MushMeshTools::kAxisXW, newXWAngle - xwAngle).VectorRotate(objPost.PosWRef());
    }
    else
    {
        alpha *= 0.6 + 0.4*(std::fabs(xwAngle) / xwAngleLimit);
    }

    tVal ywAngle = atan2(objPost.Pos().Y(), -objPost.Pos().W());
    if (std::fabs(ywAngle) > ywAngleLimit)
    {
        tVal runOffFraction = (std::fabs(ywAngle) - ywAngleLimit) / (M_PI - ywAngleLimit);
        tVal newYWAngle =  ywAngleLimit + angleRunOff * (1- pow(1-runOffFraction, 4));
        if (ywAngle < 0) newYWAngle = -newYWAngle;
        MushMeshTools::QuaternionRotateInAxis(MushMeshTools::kAxisYW, newYWAngle - ywAngle).VectorRotate(objPost.PosWRef());
    }
    else
    {
        alpha *= 0.6 + 0.4*(std::fabs(ywAngle) / ywAngleLimit);
    }

    U32 scanSymbol = kSymbolScanNone;
    const AdanaxisPieceKhazi *pKhazi = dynamic_cast<const AdanaxisPieceKhazi *>(&inPiece);

    if (ioLogic.VolatileData().JammerCount() > 0)
    {
        if (pKhazi != NULL && pKhazi->IsJammer())
        {
            scanSymbol = kSymbolScanYellow;
        }
        else
        {
            pKhazi = NULL;
        }
    }

    if (scanSymbol == kSymbolScanNone)
    {
        if (pKhazi != NULL)
        {
            scanSymbol = pKhazi->ScannerSymbol();
        }
        else
        {
            switch (inObjType)
            {
                case kObjectTypeItem:
                    scanSymbol = kSymbolScanGreen;
                    break;

                case kObjectTypeKhazi:
                    scanSymbol = kSymbolScanWhite;
                    break;

                default:
                    scanSymbol = kSymbolScanWhite;
                    break;
            }
        }
    }

    if (std::fabs(objPost.PosWRef().W()) > 0)
    {
        objPost.PosWRef() /= std::fabs(objPost.PosWRef().W());
        objPost.PosWRef() *= 100;
        MushMeshOps::PosticityToMattress(renderSpec.ModelWRef(), objPost);
        MushMeshOps::PosticityToMattress(renderSpec.ViewWRef(), cameraPost);
        renderSpec.ViewWRef().InPlaceInvert();
        t4Val clipPos = renderSpec.ModelToClipMattress() * t4Val(0,0,0,0);

        m_symbolSize = 4 * t2Val(1, renderSpec.Projection().AspectRatio());
        ScanSymbolRender(clipPos, eyePos, alpha, scanSymbol);
    }
}

void
AdanaxisScanner::ScanCrosshairRender(AdanaxisLogic& ioLogic, MushRenderMesh *inpMeshRender,
                                     const MushGameCamera& inCamera)
{
    U32 movesThisFrame = ioLogic.VolatileData().MovesThisFrame();

    MushMeshPosticity cameraPost = inCamera.Post();

    MushMeshPosticity crossPost(MushMeshPosticity::Identity());

    crossPost.PosSet(cameraPost.Pos() + cameraPost.AngPos().RotatedVector(t4Val(0,0,0,-10)));

    MushRenderSpec renderSpec;
    MushMeshOps::PosticityToMattress(renderSpec.ModelWRef(), crossPost);
    MushMeshOps::PosticityToMattress(renderSpec.ViewWRef(), cameraPost);
    renderSpec.ViewWRef().InPlaceInvert();
    renderSpec.ProjectionSet(inCamera.Projection());
    t4Val sightClipPos = renderSpec.ModelToClipMattress() * t4Val(0,0,0,0);
    t4Val barClipPos = sightClipPos + t4Val(0,-0.5,0,0);

    m_symbolSize = 1 * t2Val(1, renderSpec.Projection().AspectRatio());

    U32 symbol;
    const tVal rotSpeed = 0.025 * movesThisFrame;
    bool hitPointsBar = false;

    switch (m_targetState)
    {
        case kTargetStateIdle:
            symbol = kSymbolCrosshairIdle;

            if (m_sightAngle == 0 ||
                ceil(m_sightAngle / (M_PI/2)) != ceil((m_sightAngle + rotSpeed) / (M_PI/2)))
            {
                m_sightAngle = 0;
            }
            else
            {
                m_sightAngle += rotSpeed;
            }
            break;

        case kTargetStateInBoundary:
            symbol = kSymbolCrosshairInBoundary;
            if (m_sightAngle == 0 ||
                ceil(m_sightAngle / (M_PI/2)) != ceil((m_sightAngle + rotSpeed) / (M_PI/2)))
            {
                m_sightAngle = 0;
            }
            else
            {
                m_sightAngle += rotSpeed;
            }
            hitPointsBar = true;
            break;

        case kTargetStateOnTarget:
            symbol = kSymbolCrosshairOnTarget;
            m_sightAngle += rotSpeed;
            hitPointsBar = true;
            break;

        default:
            symbol = kSymbolCrosshairSpecial;
            m_sightAngle = 0;
            break;
    }

    // Render sight
    MushGLFont& fontRef = m_symbolFontRef.WRef();
    fontRef.ColourSet(t4Val(1,1,1,0.3));
    fontRef.RenderSymbolAtSizeAngle(symbol, sightClipPos, m_symbolSize,
                                    m_sightAngle);

    if (hitPointsBar)
    {
        MushcoreUtil::Constrain<tVal>(m_targetHitPointRatio, 0.0, 1.0);
        // Render hit points bar
        fontRef.RenderSymbolAtSize(kSymbolHitPointsBarBorder, barClipPos, m_symbolSize);
        fontRef.RenderSymbolAtSizeProportion(kSymbolHitPointsBarInterior, barClipPos,
                                             m_symbolSize, t2Val(m_targetHitPointRatio, 1));
    }
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
    ioOut << "symbolFontRef=" << m_symbolFontRef << ", ";
    ioOut << "sightAngle=" << m_sightAngle << ", ";
    ioOut << "targetState=" << m_targetState << ", ";
    ioOut << "targetHitPointRatio=" << m_targetHitPointRatio << ", ";
    ioOut << "targetID=" << m_targetID;
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
    else if (inTagStr == "sightAngle")
    {
        ioIn >> m_sightAngle;
    }
    else if (inTagStr == "targetState")
    {
        ioIn >> m_targetState;
    }
    else if (inTagStr == "targetHitPointRatio")
    {
        ioIn >> m_targetHitPointRatio;
    }
    else if (inTagStr == "targetID")
    {
        ioIn >> m_targetID;
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
    ioOut.TagSet("sightAngle");
    ioOut << m_sightAngle;
    ioOut.TagSet("targetState");
    ioOut << m_targetState;
    ioOut.TagSet("targetHitPointRatio");
    ioOut << m_targetHitPointRatio;
    ioOut.TagSet("targetID");
    ioOut << m_targetID;
}
//%outOfLineFunctions } nmioQwjsOEAtcVMnY6mM8A
