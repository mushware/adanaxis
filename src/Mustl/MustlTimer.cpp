//%Header {
/*****************************************************************************
 *
 * File: src/Mustl/MustlTimer.cpp
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
//%Header } 9/Cnp1nIV1yaroRrPR603w
/*
 * $Id: MustlTimer.cpp,v 1.9 2005/05/19 13:02:20 southa Exp $
 * $Log: MustlTimer.cpp,v $
 * Revision 1.9  2005/05/19 13:02:20  southa
 * Mac release work
 *
 * Revision 1.8  2004/01/02 21:13:15  southa
 * Source conditioning
 *
 * Revision 1.7  2003/09/17 19:40:38  southa
 * Source conditioning upgrades
 *
 * Revision 1.6  2003/08/21 23:09:31  southa
 * Fixed file headers
 *
 * Revision 1.5  2003/01/20 10:45:31  southa
 * Singleton tidying
 *
 * Revision 1.4  2002/12/29 21:00:00  southa
 * More build fixes
 *
 * Revision 1.3  2002/12/20 13:17:46  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.2  2002/12/13 01:06:54  southa
 * Mustl work
 *
 * Revision 1.1  2002/12/12 18:38:25  southa
 * Mustl separation
 *
 */

#include "MustlTimer.h"

#include "Mustl.h"
#include "MustlPlatform.h"
#include "MustlSTL.h"

using namespace Mustl;
using namespace std;

MUSHCORE_SINGLETON_INSTANCE(MustlTimer);

MustlTimer::MustlTimer() :
    m_timerFunction(MustlPlatform::DefaultTimer),
    m_currentMsec(0),
    m_lastU32Msec(0)
{}
