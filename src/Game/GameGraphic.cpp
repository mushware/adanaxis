//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameGraphic.cpp
 *
 * Author: Andy Southgate 2002-2007
 *
 * This file contains original work by Andy Southgate.  The author and his
 * employer (Mushware Limited) irrevocably waive all of their copyright rights
 * vested in this particular version of this file to the furthest extent
 * permitted.  The author and Mushware Limited also irrevocably waive any and
 * all of their intellectual property rights arising from said file and its
 * creation that would otherwise restrict the rights of any party to use and/or
 * distribute the use of, the techniques and methods used herein.  A written
 * waiver can be obtained via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } hQxHdLVD8NKoShbCkfwRoA
/*
 * $Id: GameGraphic.cpp,v 1.16 2006/06/01 15:38:57 southa Exp $
 * $Log: GameGraphic.cpp,v $
 * Revision 1.16  2006/06/01 15:38:57  southa
 * DrawArray verification and fixes
 *
 * Revision 1.15  2005/05/19 13:02:02  southa
 * Mac release work
 *
 * Revision 1.14  2004/01/02 21:13:07  southa
 * Source conditioning
 *
 * Revision 1.13  2003/09/17 19:40:32  southa
 * Source conditioning upgrades
 *
 * Revision 1.12  2003/08/21 23:08:45  southa
 * Fixed file headers
 *
 * Revision 1.11  2003/01/13 14:31:58  southa
 * Build frameworks for Mac OS X
 *
 * Revision 1.10  2003/01/12 17:32:55  southa
 * Mushcore work
 *
 * Revision 1.9  2002/12/29 20:59:56  southa
 * More build fixes
 *
 * Revision 1.8  2002/12/20 13:17:40  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.7  2002/10/22 20:42:04  southa
 * Source conditioning
 *
 * Revision 1.6  2002/10/12 11:22:21  southa
 * GraphicModel work
 *
 * Revision 1.5  2002/08/27 08:56:24  southa
 * Source conditioning
 *
 * Revision 1.4  2002/08/07 13:36:50  southa
 * Conditioned source
 *
 * Revision 1.3  2002/07/06 18:04:19  southa
 * More designer work
 *
 * Revision 1.2  2002/06/27 12:36:07  southa
 * Build process fixes
 *
 * Revision 1.1  2002/06/04 17:02:11  southa
 * More work
 *
 */

#include "GameGraphic.h"

#include "GameGraphicModel.h"
#include "GameGraphicSprite.h"
#include "GameSTL.h"

using namespace Mushware;
using namespace std;

GameGraphic&
GameGraphic::NewFromType(const string& inName)
{
    if (inName == "sprite")
    {
        return *new GameGraphicSprite;
    }
    else if (inName == "model")
    {
        return *new GameGraphicModel;
    }
    else
    {
        ostringstream message;
        message << "Unknown type for graphic '" << inName << "'";
        throw (MushcoreDataFail(message.str()));
    }
}
