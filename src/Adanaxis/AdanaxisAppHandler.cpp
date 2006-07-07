//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisAppHandler.cpp
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
//%Header } oSmLZ+XD56LtO8LoKCgFfg
/*
 * $Id: AdanaxisAppHandler.cpp,v 1.6 2006/06/30 15:05:30 southa Exp $
 * $Log: AdanaxisAppHandler.cpp,v $
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
    MushGameAppHandler(inName)
{
}

void
AdanaxisAppHandler::NewGameCreate(const std::string& inName)
{
    MushcoreData<MushGameBase>::Sgl().Give(inName, new AdanaxisGame(inName));
    m_gameRef.NameSet(inName);
}

