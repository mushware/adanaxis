//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameType.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } CE4p9Obptgcq47PZM1Kswg
/*
 * $Id: GameType.cpp,v 1.8 2003/10/07 22:40:05 southa Exp $
 * $Log: GameType.cpp,v $
 * Revision 1.8  2003/10/07 22:40:05  southa
 * Created MeshMover
 *
 * Revision 1.7  2003/09/17 19:40:34  southa
 * Source conditioning upgrades
 *
 * Revision 1.6  2003/08/21 23:08:58  southa
 * Fixed file headers
 *
 * Revision 1.5  2002/12/29 20:59:57  southa
 * More build fixes
 *
 * Revision 1.4  2002/12/20 13:17:44  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.3  2002/10/22 20:42:07  southa
 * Source conditioning
 *
 * Revision 1.2  2002/08/27 08:56:28  southa
 * Source conditioning
 *
 * Revision 1.1  2002/08/18 20:44:35  southa
 * Initial chequepoint work
 *
 */

#include "GameType.h"

using namespace Mushware;
using namespace std;

MUSHCORE_SINGLETON_INSTANCE(GameType);

GameType *
GameType::SingletonFactory(void)
{
    throw(MushcoreReferenceFail("GameType accessed before creation"));
}
