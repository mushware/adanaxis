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
 * $Id$
 * $Log$
 */

#include "AdanaxisRender.h"

#include "AdanaxisSaveData.h"

#include "API/mushGL.h"
#include "API/mushMushGame.h"
#include "API/mushMushGL.h"
#include "API/mushPlatform.h"

using namespace Mushware;
using namespace std;

void
AdanaxisRender::FrameRender(MushGameLogic& ioLogic, const MushGameCamera& inCamera)
{
    AdanaxisSaveData *pData = dynamic_cast<AdanaxisSaveData *>(&ioLogic.SaveData());
    
    if (pData == NULL)
    {
        throw MushcoreDataFail("Uninitialised AdanaxisSaveData");
    }
    
    GLUtils::DisplayPrologue();
    GLUtils::ClearScreen();
    
    MushGameDialogueUtils::MoveAndRender(pData->DialoguesWRef(), GameUtils::AppHandler());
    
    GLUtils::OrthoPrologue();
    
    if (pData->ModeKeypressMsec() != 0)
    {
        PlatformVideoUtils::Sgl().RenderModeInfo(pData->NewMode());
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
