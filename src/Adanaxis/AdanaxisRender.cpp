//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisRender.cpp
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
//%Header } Hr8bvS7fc+x0pR9DrFcIZw
/*
 * $Id: AdanaxisRender.cpp,v 1.36 2006/07/21 10:52:05 southa Exp $
 * $Log: AdanaxisRender.cpp,v $
 * Revision 1.36  2006/07/21 10:52:05  southa
 * win32 build fixes
 *
 * Revision 1.35  2006/07/20 12:22:21  southa
 * Precache display
 *
 * Revision 1.34  2006/07/19 14:34:51  southa
 * Flare effects
 *
 * Revision 1.33  2006/07/19 10:22:15  southa
 * World objects
 *
 * Revision 1.32  2006/07/17 14:43:39  southa
 * Billboarded deco objects
 *
 * Revision 1.31  2006/07/08 16:05:54  southa
 * Ruby menus and key handling
 *
 * Revision 1.30  2006/07/07 18:13:57  southa
 * Menu start and stop
 *
 * Revision 1.29  2006/07/02 21:08:54  southa
 * Ruby menu work
 *
 * Revision 1.28  2006/07/02 09:43:26  southa
 * MushGLFont work
 *
 * Revision 1.27  2006/06/30 17:26:10  southa
 * Render prelude
 *
 * Revision 1.26  2006/06/30 15:05:32  southa
 * Texture and buffer purge
 *
 * Revision 1.25  2006/06/21 16:52:28  southa
 * Deco objects
 *
 * Revision 1.24  2006/06/01 15:38:48  southa
 * DrawArray verification and fixes
 *
 * Revision 1.23  2005/09/06 12:15:35  southa
 * Texture and rendering work
 *
 * Revision 1.22  2005/09/05 17:14:22  southa
 * Solid rendering
 *
 * Revision 1.21  2005/08/31 23:57:26  southa
 * Texture coordinate work
 *
 * Revision 1.20  2005/08/02 14:37:44  southa
 * Adanaxis control demo work
 *
 * Revision 1.19  2005/08/02 11:11:47  southa
 * Adanaxis control demo work
 *
 * Revision 1.18  2005/08/01 20:24:15  southa
 * Backdrop and build fixes
 *
 * Revision 1.17  2005/07/30 19:06:14  southa
 * Collision checking
 *
 * Revision 1.16  2005/07/29 14:59:49  southa
 * Maptor access
 *
 * Revision 1.15  2005/07/29 08:27:47  southa
 * Collision work
 *
 * Revision 1.14  2005/07/18 13:13:36  southa
 * Extrude to point and projectile mesh
 *
 * Revision 1.13  2005/07/16 14:22:59  southa
 * Added diagnostic renderer
 *
 * Revision 1.12  2005/07/13 16:45:04  southa
 * Extrusion work
 *
 * Revision 1.11  2005/07/12 12:18:17  southa
 * Projectile work
 *
 * Revision 1.10  2005/07/06 19:08:26  southa
 * Adanaxis control work
 *
 * Revision 1.9  2005/07/05 16:35:53  southa
 * Adanaxis work
 *
 * Revision 1.8  2005/07/05 13:52:22  southa
 * Adanaxis work
 *
 * Revision 1.7  2005/07/04 15:59:00  southa
 * Adanaxis work
 *
 * Revision 1.6  2005/07/04 11:10:43  southa
 * Rendering pipeline
 *
 * Revision 1.5  2005/07/02 00:42:36  southa
 * Conditioning tweaks
 *
 * Revision 1.4  2005/07/01 10:36:46  southa
 * MushRender work
 *
 * Revision 1.3  2005/07/01 10:03:30  southa
 * Projection work
 *
 * Revision 1.2  2005/06/30 14:26:35  southa
 * Adanaxis work
 *
 * Revision 1.1  2005/06/29 11:11:15  southa
 * Camera and rendering work
 *
 */

#include "AdanaxisRender.h"

#include "AdanaxisAppHandler.h"
#include "AdanaxisSaveData.h"
#include "AdanaxisLogic.h"
#include "AdanaxisVolatileData.h"
#include "AdanaxisUtil.h"

#include "API/mushGL.h"
#include "API/mushMushGame.h"
#include "API/mushMushGL.h"
#include "API/mushPlatform.h"

using namespace Mushware;
using namespace std;

AdanaxisRender::AdanaxisRender() :
    m_halfAngle(M_PI/12),
    m_halfAngleAttractor(M_PI/12),
    m_scannerOn(false),
    m_renderPrelude(0)
{
}

void
AdanaxisRender::PreCacheRender(MushGameLogic& ioLogic, const MushGameCamera& inCamera)
{
    AdanaxisVolatileData *pVolData = dynamic_cast<AdanaxisVolatileData *>(&ioLogic.VolatileData());
    
    if (pVolData == NULL)
    {
        throw MushcoreDataFail("Uninitialised AdanaxisVolatileData");
    }
    
    AdanaxisLogic *pLogic = dynamic_cast<AdanaxisLogic *>(&ioLogic);
    
    if (pLogic == NULL)
    {
        throw MushcoreDataFail("Uninitialised AdanaxisLogic");
    }
    
    MushGLUtil::DisplayPrologue();
    MushGLUtil::ClearScreen();
    MushGLUtil::IdentityPrologue();
    MushGLUtil::OrthoPrologue();

    MushGLState::Sgl().RenderStateSet(MushGLState::kRenderState2D);

    MushRubyExec::Sgl().Call(pVolData->RubyGame(),
                             MushRubyIntern::mPreCacheRender(),
                             MushRubyValue(pLogic->PreCachePercentage()));

    MushGLUtil::OrthoEpilogue();
    MushGLUtil::IdentityEpilogue();
    MushGLUtil::DisplayEpilogue();    
}

void
AdanaxisRender::SortAndDespatch(MushGameLogic& ioLogic, std::vector<MushGLJobRender *> inJobs)
{
    U32 numJobs = inJobs.size();
    
    std::vector< std::pair<tVal, U32> > sortList(numJobs);
    
    for (U32 i=0; i<numJobs; ++i)
    {
        MUSHCOREASSERT(inJobs[i] != NULL);
        sortList[i].first = inJobs[i]->SortValue(); 
        sortList[i].second = i; 
    }
    
    std::sort(sortList.begin(), sortList.end());
    
    for (U32 i=0; i<numJobs; ++i)
    {
        MushGLJobRender *pJob = inJobs[sortList[i].second];
        MUSHCOREASSERT(pJob != NULL);
        pJob->Execute();
    }
}


void
AdanaxisRender::FrameRender(MushGameLogic& ioLogic, const MushGameCamera& inCamera)
{
    AdanaxisSaveData *pSaveData = dynamic_cast<AdanaxisSaveData *>(&ioLogic.SaveData());
    
    if (pSaveData == NULL)
    {
        throw MushcoreDataFail("Uninitialised AdanaxisSaveData");
    }
    
    AdanaxisVolatileData *pVolData = dynamic_cast<AdanaxisVolatileData *>(&ioLogic.VolatileData());
    
    if (pVolData == NULL)
    {
        throw MushcoreDataFail("Uninitialised AdanaxisVolatileData");
    }
    
    tVal aspectRatio = MushGLUtil::ScreenAspectRatio();
    
    m_projection.ViewHalfRadiansSet(m_halfAngle);
    m_projection.FromAspectNearFarMake(aspectRatio, 1.0, 10000.0);

    m_halfAngle = m_halfAngle * 0.90 + m_halfAngleAttractor * 0.1;
    
    if (MushGLUtil::AppHandler().LatchedKeyStateTake(9))
    {
        m_scannerOn = !m_scannerOn;
    }
    
    if (m_scannerOn)
    {
        m_halfAngleAttractor = 0.4*M_PI;
    }
    else
    {
        m_halfAngleAttractor = M_PI/12;
    }
    
    MushGLUtil::DisplayPrologue();
    MushGLUtil::ClearScreen();
    
    GLColour(0.8,0.8,0.8,0.5).Apply();
    
    if (m_renderPrelude == 0)
    {
        m_renderList.resize(0);
        m_renderList.push_back(new MushGLJobRender);

        MushGLUtil::IdentityPrologue();
        
        MushGLState::Sgl().RenderStateSet(MushGLState::kRenderState4D);
        
        //MushRenderMeshDiagnostic renderMesh;
        //MushRenderMeshWireframe renderMesh;
        MushRenderMeshSolid renderMesh;
        
        MushGameCamera camera(inCamera);
        
        renderMesh.ColourZMiddleSet(t4Val(1.0,1.0,1.0,1.0));
        renderMesh.ColourZLeftSet(t4Val(1.0,0.3,0.3,0.0));
        renderMesh.ColourZRightSet(t4Val(0.3,1.0,0.3,0.0));

        camera.ProjectionSet(m_projection);
        {
            typedef AdanaxisVolatileData::tWorldList tWorldList;
            tWorldList::iterator worldEndIter = pVolData->WorldListWRef().end();
            for (tWorldList::iterator p = pVolData->WorldListWRef().begin(); p != worldEndIter; ++p)
            {
                p->Render(ioLogic, renderMesh, camera);
            }
        }
        
        renderMesh.ColourZMiddleSet(t4Val(1.0,1.0,1.0,0.3));
        renderMesh.ColourZLeftSet(t4Val(1.0,0.3,0.3,0.0));
        renderMesh.ColourZRightSet(t4Val(0.3,1.0,0.3,0.0));

        typedef AdanaxisSaveData::tProjectileList tProjectileList;
        
        tProjectileList::iterator projectileEndIter = pSaveData->ProjectileListWRef().end();
        for (tProjectileList::iterator p = pSaveData->ProjectileListWRef().begin(); p != projectileEndIter; ++p)
        {
            MUSHCOREASSERT(m_renderList.back() != NULL);
            
            if (p->Render(*m_renderList.back(), ioLogic, renderMesh, camera))
            {
                m_renderList.push_back(new MushGLJobRender);
            }
        }    
        
        renderMesh.ColourZMiddleSet(t4Val(1.0,1.0,1.0,1.0));
        renderMesh.ColourZLeftSet(t4Val(1.0,0.3,0.3,0.0));
        renderMesh.ColourZRightSet(t4Val(0.3,1.0,0.3,0.0));
        
        if (!m_scannerOn)
        {
            typedef AdanaxisVolatileData::tDecoList tDecoList;
            
            tDecoList::iterator decoEndIter = pVolData->DecoListWRef().end();
            for (tDecoList::iterator p = pVolData->DecoListWRef().begin(); p != decoEndIter; ++p)
            {
                MUSHCOREASSERT(m_renderList.back() != NULL);
                
                if (p->Render(*m_renderList.back(), ioLogic, renderMesh, camera))
                {
                    m_renderList.push_back(new MushGLJobRender);
                }
            }
        }
        
        renderMesh.ColourZMiddleSet(t4Val(1.0,1.0,1.0,0.3));
        renderMesh.ColourZLeftSet(t4Val(1.0,0.3,0.3,0.0));
        renderMesh.ColourZRightSet(t4Val(0.3,1.0,0.3,0.0));
        
        typedef AdanaxisSaveData::tKhaziList tKhaziList;
        
        tKhaziList::iterator khaziEndIter = pSaveData->KhaziListWRef().end();
        for (tKhaziList::iterator p = pSaveData->KhaziListWRef().begin(); p != khaziEndIter; ++p)
        {
            MUSHCOREASSERT(m_renderList.back() != NULL);
            
            if (p->Render(*m_renderList.back(), ioLogic, renderMesh, camera))
            {
                m_renderList.push_back(new MushGLJobRender);
            }
        }    
        
        SortAndDespatch(ioLogic, m_renderList);
        
        U32 renderListSize = m_renderList.size();
        for (U32 i=0; i + 1 < renderListSize; ++i)
        {
            MUSHCOREASSERT(m_renderList[i] != NULL);            
            delete m_renderList[i];
            m_renderList[i] = NULL;
        }
        m_renderList.resize(0);
        
        MushGLUtil::IdentityEpilogue();
    }
    
    MushGLState::Sgl().ResetWriteAll();
    GLState::ContextReset();

    MushGLState::Sgl().RenderStateSet(MushGLState::kRenderState2D);

    MushGLUtil::IdentityPrologue();

    MushGameDialogueUtils::MoveAndRender(pSaveData->DialoguesWRef(), AdanaxisUtil::AppHandler());
    
    MushGLUtil::OrthoPrologue();

    Overplot(ioLogic, inCamera);
    
    if (pVolData->ModeKeypressMsec() != 0)
    {
        PlatformVideoUtils::Sgl().RenderModeInfo(pVolData->NewMode());
    }

    MushGLUtil::OrthoEpilogue();
    
    MushGLUtil::IdentityEpilogue();
    
    if (ioLogic.IsMenuMode())
    {
        MushGLUtil::IdentityPrologue();
        MushGLUtil::OrthoPrologue();
        GLState::ColourSet(1.0,1.0,1.0,1.0);
        
        U32 timeNow = AdanaxisUtil::AppHandler().MillisecondsGet();
        
        MushRubyExec::Sgl().Call(pVolData->RubyGame(),
                                 MushRubyIntern::mRender(),
                                 MushRubyValue(timeNow));
        MushGLUtil::OrthoEpilogue();
        MushGLUtil::IdentityEpilogue();
    }
    
    MushGLUtil::DisplayEpilogue();
    
    if (m_renderPrelude > 0)
    {
        --m_renderPrelude;   
    }
    

}

void
AdanaxisRender::Overplot(MushGameLogic& ioLogic, const MushGameCamera& inCamera)
{
    GLState::ColourSet(1.0,1.0,1.0,0.3);
    GLUtils orthoGL;
    
    AdanaxisLogic &logicRef = dynamic_cast<AdanaxisLogic &>(ioLogic);
    
    if (m_renderPrelude != 0)
    {
        orthoGL.MoveToEdge(1,-1);
        orthoGL.MoveRelative(-0.08, 0.08);
        GLString glStr1(MushcoreInfo::Sgl().PackageID(), GLFontRef("font-mono1", 0.015), 1);
        glStr1.Render();
        orthoGL.MoveToEdge(0,0);
        GLString glStr2("Generating texture cache", GLFontRef("font-mono1", 0.03), 0);
        glStr2.Render();
        
        if (MushcoreGlobalConfig::Sgl().Exists("FIRST_RUN"))
        {
            orthoGL.MoveRelative(0, -0.08);
            GLString glStr3("(This may take a minute or two)", GLFontRef("font-mono1", 0.02), 0);
            glStr3.Render();
        }
    }
    else
    {
        if (m_scannerOn)
        {
            orthoGL.MoveToEdge(0,1);
            orthoGL.MoveRelative(0, -0.08);
            GLString glStr("Fish-eye scanner", GLFontRef("font-mono1", 0.02), 0);
            glStr.Render();
        }
        
        {
            orthoGL.MoveToEdge(-1,1);
            orthoGL.MoveRelative(0.01, -0.04);
            ostringstream message;
            message << logicRef.KhaziCount() << " left";
            GLString glStr(message.str(), GLFontRef("font-mono1", 0.02), -1);
            glStr.Render();
        }
        {
            orthoGL.MoveToEdge(1,1);
            orthoGL.MoveRelative(-0.01, -0.04);
            ostringstream message;
            message << GameTimer::MsecToLongString(logicRef.EndTime() - logicRef.StartTime());
            GLString glStr(message.str(), GLFontRef("font-mono1", 0.02), 1);
            glStr.Render();
        }
        {
            orthoGL.MoveToEdge(0,-1);
            orthoGL.MoveRelative(0, 0.04);
            GLString glStr(AdanaxisUtil::AppHandler().AxisNames(), GLFontRef("font-mono1", 0.02), 0);
            glStr.Render();
        }
        
        if (logicRef.KhaziCount() == 0)
        {
            {
                orthoGL.MoveTo(0, 0.04);
                ostringstream message;
                message << "Time:   " << GameTimer::MsecToLongString(logicRef.EndTime() - logicRef.StartTime());
                GLString glStr(message.str(), GLFontRef("font-mono1", 0.03), 0);
                glStr.Render();        
            }
            if (logicRef.RecordTime() != 0)
            {
                orthoGL.MoveTo(0, -0.04);
                ostringstream message;
                message << "Record: " << GameTimer::MsecToLongString(logicRef.RecordTime());
                GLString glStr(message.str(), GLFontRef("font-mono1", 0.03), 0);
                glStr.Render();        
            }
            {
                orthoGL.MoveTo(0, -0.2);
                ostringstream message;
                message << "(Esc to exit)";
                GLString glStr(message.str(), GLFontRef("font-mono1", 0.02), 0);
                glStr.Render();        
            }
        }
    }
    orthoGL.MoveTo(0, 0);
}

//%outOfLineFunctions {

const char *AdanaxisRender::AutoName(void) const
{
    return "AdanaxisRender";
}

MushcoreVirtualObject *AdanaxisRender::AutoClone(void) const
{
    return new AdanaxisRender(*this);
}

MushcoreVirtualObject *AdanaxisRender::AutoCreate(void) const
{
    return new AdanaxisRender;
}

MushcoreVirtualObject *AdanaxisRender::AutoVirtualFactory(void)
{
    return new AdanaxisRender;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("AdanaxisRender", AdanaxisRender::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
AdanaxisRender::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "projection=" << m_projection << ", ";
    ioOut << "halfAngle=" << m_halfAngle << ", ";
    ioOut << "halfAngleAttractor=" << m_halfAngleAttractor << ", ";
    ioOut << "scannerOn=" << m_scannerOn << ", ";
    ioOut << "renderPrelude=" << m_renderPrelude << ", ";
    ioOut << "renderList=" << m_renderList;
    ioOut << "]";
}
bool
AdanaxisRender::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "projection")
    {
        ioIn >> m_projection;
    }
    else if (inTagStr == "halfAngle")
    {
        ioIn >> m_halfAngle;
    }
    else if (inTagStr == "halfAngleAttractor")
    {
        ioIn >> m_halfAngleAttractor;
    }
    else if (inTagStr == "scannerOn")
    {
        ioIn >> m_scannerOn;
    }
    else if (inTagStr == "renderPrelude")
    {
        ioIn >> m_renderPrelude;
    }
    else if (inTagStr == "renderList")
    {
        ioIn >> m_renderList;
    }
    else 
    {
        return false;
    }
    return true;
}
void
AdanaxisRender::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("projection");
    ioOut << m_projection;
    ioOut.TagSet("halfAngle");
    ioOut << m_halfAngle;
    ioOut.TagSet("halfAngleAttractor");
    ioOut << m_halfAngleAttractor;
    ioOut.TagSet("scannerOn");
    ioOut << m_scannerOn;
    ioOut.TagSet("renderPrelude");
    ioOut << m_renderPrelude;
    ioOut.TagSet("renderList");
    ioOut << m_renderList;
}
//%outOfLineFunctions } c/2s2DO2L2KEFp5Qw59H4Q
