/*****************************************************************************
 *
 * (Mushware file header version 1.3)
 *
 * Copyrighted work by Andy Southgate 2003
 *
 * This file may be redistributed and/or modified under the terms of the
 * Mushware licence which you should have received with this file.  For
 * information, please contact the author via http://www.mushware.com/.
 *
 ****************************************************************************/

/*
 * $Id: GameGraphic.cpp,v 1.11 2003/01/13 14:31:58 southa Exp $
 * $Log: GameGraphic.cpp,v $
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
