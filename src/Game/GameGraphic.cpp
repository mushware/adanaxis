/*****************************************************************************
 *
 * (Mushware file header version 1.2)
 *
 * This file contains original work by Andy Southgate.
 * Copyright Andy Southgate 2002.  All rights reserved.
 * Contact details can be found at http://www.mushware.com/
 *
 ****************************************************************************/

/*
 * $Id: GameGraphic.cpp,v 1.8 2002/12/20 13:17:40 southa Exp $
 * $Log: GameGraphic.cpp,v $
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
        throw (SpecifierFail(message.str()));
    }
}
