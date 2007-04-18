//%includeGuardStart {
#ifndef INFERNALEVENT_H
#define INFERNALEVENT_H
//%includeGuardStart } 4TKgDlgKORxN63q9kxQnHw
//%Header {
/*****************************************************************************
 *
 * File: src/Infernal/InfernalEvent.h
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
//%Header } EvyQ7q0eAK57itF6izsMlw
/*
 * $Id: InfernalEvent.h,v 1.5 2006/06/01 15:39:02 southa Exp $
 * $Log: InfernalEvent.h,v $
 * Revision 1.5  2006/06/01 15:39:02  southa
 * DrawArray verification and fixes
 *
 * Revision 1.4  2005/05/19 13:02:04  southa
 * Mac release work
 *
 * Revision 1.3  2004/01/06 20:46:50  southa
 * Build fixes
 *
 * Revision 1.2  2004/01/02 21:13:08  southa
 * Source conditioning
 *
 * Revision 1.1  2003/10/04 15:32:10  southa
 * Module split
 *
 */

#include "mushMushcore.h"
#include "mushGame.h"

#include "InfernalFloorMap.h"

class InfernalEventStandingOn : public GameEvent
{
public:
    explicit InfernalEventStandingOn(const InfernalFloorMap::tMapVector& inValues) { mapValues = inValues; }
    InfernalFloorMap::tMapVector mapValues;
};

class InfernalEventSequenceAdvance : public GameEvent
{
public:
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
