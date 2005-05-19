//%Header {
/*****************************************************************************
 *
 * File: src/Infernal/InfernalTileSpec.cpp
 *
 * Author: Andy Southgate 2002-2005
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
//%Header } nQcoWLHKDpnGiO716+G0RQ
/*
 * $Id: InfernalTileSpec.cpp,v 1.3 2004/01/02 21:13:09 southa Exp $
 * $Log: InfernalTileSpec.cpp,v $
 * Revision 1.3  2004/01/02 21:13:09  southa
 * Source conditioning
 *
 * Revision 1.2  2003/10/04 15:32:11  southa
 * Module split
 *
 * Revision 1.1  2003/10/04 12:23:07  southa
 * File renaming
 *
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

#include "InfernalSTL.h"
#include "InfernalTileTraits.h"

using namespace Mushware;
using namespace std;

ostream& operator<<(ostream &inOut, const InfernalTileSpec& inSpec)
{
    inOut << inSpec.TileTraitsGet() << ", rotation=" << inSpec.RotationGet();
    return inOut;
}
