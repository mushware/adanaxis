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
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } k0Sn6hVC9uFmWVARlBuCew
/*
 * $Id$
 * $Log$
 */

#include "Mushcore.h"
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
