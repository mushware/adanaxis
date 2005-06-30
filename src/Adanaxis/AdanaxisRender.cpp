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
 * $Id: AdanaxisRender.cpp,v 1.1 2005/06/29 11:11:15 southa Exp $
 * $Log: AdanaxisRender.cpp,v $
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

    if (ctr++ < 5) std::cout << "Camera " << inCamera << endl;
    
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
    else
    {
        return false;
    }
    return true;
}
void
AdanaxisRender::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
}
//%outOfLineFunctions } fijB+kNsAePk1dtY8iyeDg
