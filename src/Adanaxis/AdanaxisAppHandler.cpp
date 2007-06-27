//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisAppHandler.cpp
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
//%Header } KoqKCIMG0M53D1ct0e/kAA
/*
 * $Id: AdanaxisAppHandler.cpp,v 1.10 2007/04/18 09:21:59 southa Exp $
 * $Log: AdanaxisAppHandler.cpp,v $
 * Revision 1.10  2007/04/18 09:21:59  southa
 * Header and level fixes
 *
 * Revision 1.9  2006/08/01 17:21:21  southa
 * River demo
 *
 * Revision 1.8  2006/07/31 11:01:35  southa
 * Music and dialogues
 *
 * Revision 1.7  2006/07/07 18:13:56  southa
 * Menu start and stop
 *
 * Revision 1.6  2006/06/30 15:05:30  southa
 * Texture and buffer purge
 *
 * Revision 1.5  2006/06/01 15:38:46  southa
 * DrawArray verification and fixes
 *
 * Revision 1.4  2005/07/06 19:08:26  southa
 * Adanaxis control work
 *
 * Revision 1.3  2005/06/14 20:39:40  southa
 * Adanaxis work
 *
 * Revision 1.2  2005/06/14 13:25:32  southa
 * Adanaxis work
 *
 * Revision 1.1  2005/06/13 17:34:54  southa
 * Adanaxis creation
 *
 */

#include "AdanaxisAppHandler.h"

#include "AdanaxisSTL.h"

#include "mushMushcore.h"
#include "mushGL.h"
#include "mushMedia.h"
#include "mushPlatform.h"

#include "AdanaxisGame.h"

using namespace Mushware;
using namespace std;

AdanaxisAppHandler::AdanaxisAppHandler(const std::string& inName) :
    MushGameAppHandler(inName),
    m_firstGame(true)
{
}

void
AdanaxisAppHandler::NewGameCreate(const std::string& inName)
{
    MushcoreData<MushGameBase>::Sgl().Give(inName, new AdanaxisGame(inName));
    m_gameRef.NameSet(inName);
}

//%outOfLineFunctions {

const char *AdanaxisAppHandler::AutoName(void) const
{
    return "AdanaxisAppHandler";
}

MushcoreVirtualObject *AdanaxisAppHandler::AutoClone(void) const
{
    return new AdanaxisAppHandler(*this);
}

MushcoreVirtualObject *AdanaxisAppHandler::AutoCreate(void) const
{
    return new AdanaxisAppHandler;
}

MushcoreVirtualObject *AdanaxisAppHandler::AutoVirtualFactory(void)
{
    return new AdanaxisAppHandler;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("AdanaxisAppHandler", AdanaxisAppHandler::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
bool
AdanaxisAppHandler::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "gameRef")
    {
        ioIn >> m_gameRef;
    }
    else if (inTagStr == "firstGame")
    {
        ioIn >> m_firstGame;
    }
    else if (MushGameAppHandler::AutoXMLDataProcess(ioIn, inTagStr))
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
AdanaxisAppHandler::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushGameAppHandler::AutoXMLPrint(ioOut);
    ioOut.TagSet("gameRef");
    ioOut << m_gameRef;
    ioOut.TagSet("firstGame");
    ioOut << m_firstGame;
}
//%outOfLineFunctions } sjpvgUWxyJpvMdK+HI4NEQ
