//%Header {
/*****************************************************************************
 *
 * File: src/Infernal/InfernalTileSpec.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } JB0oSO4tyd6g+dgqPjwUpQ
/*
 * $Id: InfernalTileSpec.cpp,v 1.7 2003/09/17 19:40:33 southa Exp $
 * $Log: InfernalTileSpec.cpp,v $
 * Revision 1.7  2003/09/17 19:40:33  southa
 * Source conditioning upgrades
 *
 * Revision 1.6  2003/08/21 23:08:56  southa
 * Fixed file headers
 *
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

#include "InfernalTileSpec.h"

#include "GameSTL.h"
#include "InfernalTileTraits.h"

using namespace Mushware;
using namespace std;

ostream& operator<<(ostream &inOut, const InfernalTileSpec& inSpec)
{
    inOut << inSpec.TileTraitsGet() << ", rotation=" << inSpec.RotationGet();
    return inOut;
}
