//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameBase.cpp
 *
 * Author: Andy Southgate 2002-2006
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
//%Header } qNtiP8KZ6QfdreN3B5rs4g
/*
 * $Id: GameBase.cpp,v 1.8 2005/05/19 13:02:01 southa Exp $
 * $Log: GameBase.cpp,v $
 * Revision 1.8  2005/05/19 13:02:01  southa
 * Mac release work
 *
 * Revision 1.7  2004/03/06 13:13:42  southa
 * Maurheen created
 *
 * Revision 1.6  2004/01/02 21:13:06  southa
 * Source conditioning
 *
 * Revision 1.5  2003/09/17 19:40:31  southa
 * Source conditioning upgrades
 *
 * Revision 1.4  2003/08/21 23:08:34  southa
 * Fixed file headers
 *
 * Revision 1.3  2002/12/29 20:59:53  southa
 * More build fixes
 *
 * Revision 1.2  2002/12/20 13:17:37  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.1  2002/12/05 13:20:11  southa
 * Client link handling
 *
 */

#include "GameBase.h"

using namespace Mushware;
using namespace std;

MUSHCORE_DATA_INSTANCE(GameBase);
