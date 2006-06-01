//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameGlobalConfig.cpp
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
//%Header } ItmwlIn34L7Bs3zf/bOgCA
/*
 * $Id: GameGlobalConfig.cpp,v 1.12 2005/05/19 13:02:02 southa Exp $
 * $Log: GameGlobalConfig.cpp,v $
 * Revision 1.12  2005/05/19 13:02:02  southa
 * Mac release work
 *
 * Revision 1.11  2004/01/02 21:13:07  southa
 * Source conditioning
 *
 * Revision 1.10  2003/09/17 19:40:32  southa
 * Source conditioning upgrades
 *
 * Revision 1.9  2003/08/21 23:08:45  southa
 * Fixed file headers
 *
 * Revision 1.8  2002/12/29 20:59:56  southa
 * More build fixes
 *
 * Revision 1.7  2002/12/20 13:17:40  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.6  2002/10/22 20:42:04  southa
 * Source conditioning
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
 * Revision 1.1  2002/05/28 13:05:55  southa
 * Command parser extensions and TIFF loader
 *
 */

#include "GameGlobalConfig.h"

using namespace Mushware;
using namespace std;

GameGlobalConfig *GameGlobalConfig::m_instance=NULL;
