/*
 * $Id: MustlTimer.cpp,v 1.1 2002/12/12 18:38:25 southa Exp $
 * $Log: MustlTimer.cpp,v $
 * Revision 1.1  2002/12/12 18:38:25  southa
 * Mustl separation
 *
 */

#include "MustlTimer.h"

#include "Mustl.h"
#include "MustlPlatform.h"
#include "MustlSTL.h"

#include "MustlNamespace.h"

auto_ptr<MustlTimer> MustlTimer::m_instance;

MustlTimer::MustlTimer() :
    m_timerFunction(MustlPlatform::DefaultTimer),
    m_currentMsec(0),
    m_lastU32Msec(0)
{}