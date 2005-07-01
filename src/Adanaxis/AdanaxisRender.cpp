//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisRender.cpp
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
//%Header } eomVoawiv9P4VcOw5CYHSg
/*
 * $Id: AdanaxisRender.cpp,v 1.2 2005/06/30 14:26:35 southa Exp $
 * $Log: AdanaxisRender.cpp,v $
 * Revision 1.2  2005/06/30 14:26:35  southa
 * Adanaxis work
 *
 * Revision 1.1  2005/06/29 11:11:15  southa
 * Camera and rendering work
 *
 */

#include "AdanaxisRender.h"

#include "AdanaxisSaveData.h"
#include "AdanaxisVolatileData.h"

#include "API/mushGL.h"
#include "API/mushMushGame.h"
#include "API/mushMushGL.h"
#include "API/mushPlatform.h"

using namespace Mushware;
using namespace std;

AdanaxisRender::AdanaxisRender()
{
    m_projection.FromFAspectNearFarMake(m_projection.FValueFromViewHalfRadians(M_PI/8), 16.0/10, 0.1, 100.0);
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
    
    GLUtils::DisplayPrologue();
    GLUtils::ClearScreen();
    
    // Projection prologue
    
    typedef AdanaxisVolatileData::tDecoList tDecoList;
    
    tDecoList::iterator endIter = pVolData->DecoListWRef().end();
    for (tDecoList::iterator p = pVolData->DecoListWRef().begin(); p != endIter; ++p)
    {
        p->Render(ioLogic, inCamera);
    }
        
    // Projection epilogue
    
    MushGameDialogueUtils::MoveAndRender(pSaveData->DialoguesWRef(), GameUtils::AppHandler());
    
    
    GLUtils::OrthoPrologue();
    
    if (pVolData->ModeKeypressMsec() != 0)
    {
        PlatformVideoUtils::Sgl().RenderModeInfo(pVolData->NewMode());
    }
    
    static U32 ctr=0;

    if (ctr++ < 5)
    {
        MushcoreXMLOStream xmlOut(std::cout);
        std::cout << "Camera " << inCamera << endl;
        xmlOut << m_projection;
    }
    GLUtils::OrthoEpilogue();
    
    GLUtils::DisplayEpilogue();
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
    ioOut << "projection=" << m_projection;
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
}
//%outOfLineFunctions } Y86cz1VUtb/D0tLtfKLsQA
