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
 * $Id: GameTileSpec.cpp,v 1.5 2003/01/13 14:32:00 southa Exp $
 * $Log: GameTileSpec.cpp,v $
 * Revision 1.5  2003/01/13 14:32:00  southa
 * Build frameworks for Mac OS X
 *
 * Revision 1.4  2002/12/29 20:59:57  southa
 * More build fixes
 *
 * Revision 1.3  2002/12/20 13:17:43  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.2  2002/10/22 20:42:06  southa
 * Source conditioning
 *
 * Revision 1.1  2002/10/13 12:26:48  southa
 * Facetised map rendering
 *
 */

#include "GameTileSpec.h"

#include "GameSTL.h"
#include "GameTileTraits.h"

using namespace Mushware;
using namespace std;

ostream& operator<<(ostream &inOut, const GameTileSpec& inSpec)
{
    inOut << inSpec.TileTraitsGet() << ", rotation=" << inSpec.RotationGet();
    return inOut;
}
