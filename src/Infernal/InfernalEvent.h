//%includeGuardStart {
#ifndef INFERNALEVENT_H
#define INFERNALEVENT_H
//%includeGuardStart } 4TKgDlgKORxN63q9kxQnHw
//%Header {
/*****************************************************************************
 *
 * File: src/Infernal/InfernalEvent.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } zdXi0pa6S/CF3BOLwACrHA
/*
 * $Id: InfernalEvent.h,v 1.2 2004/01/02 21:13:08 southa Exp $
 * $Log: InfernalEvent.h,v $
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
