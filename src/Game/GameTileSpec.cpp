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
 * $Id: GameTileSpec.cpp,v 1.2 2002/10/22 20:42:06 southa Exp $
 * $Log: GameTileSpec.cpp,v $
 * Revision 1.2  2002/10/22 20:42:06  southa
 * Source conditioning
 *
 * Revision 1.1  2002/10/13 12:26:48  southa
 * Facetised map rendering
 *
 */

#include "GameTileSpec.h"
#include "GameTileTraits.h"

using namespace Mushware;

ostream& operator<<(ostream &inOut, const GameTileSpec& inSpec)
{
    inOut << inSpec.TileTraitsGet() << ", rotation=" << inSpec.RotationGet();
    return inOut;
}
