//%Header {
/*****************************************************************************
 *
 * File: src/Mustl/MustlTimer.cpp
 *
 * Copyright Andy Southgate 2002-2003
 *
 * This file may be redistributed and/or modified under the terms of the
 * Mushware licence which you should have received with this file.  For
 * information, please contact the author via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } WzUI3TfF4uD9YFlW+myPOg
/*
 * $Id: MustlTimer.cpp,v 1.6 2003/08/21 23:09:31 southa Exp $
 * $Log: MustlTimer.cpp,v $
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
