/*
 * $Id$
 * $Log$
 */

#include "GameTileSpec.h"
#include "GameTileTraits.h"

ostream& operator<<(ostream &inOut, const GameTileSpec& inSpec)
{
    inOut << inSpec.TileTraitsGet() << ", rotation=" << inSpec.RotationGet();
    return inOut;
}
