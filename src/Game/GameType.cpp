//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameType.cpp
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
//%Header } iaAszbh5fOROcDI8/bRsYg
/*
 * $Id: GameType.cpp,v 1.11 2006/06/01 15:39:00 southa Exp $
 * $Log: GameType.cpp,v $
 * Revision 1.11  2006/06/01 15:39:00  southa
 * DrawArray verification and fixes
 *
 * Revision 1.10  2005/05/19 13:02:03  southa
 * Mac release work
 *
 * Revision 1.9  2004/01/02 21:13:08  southa
 * Source conditioning
 *
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
