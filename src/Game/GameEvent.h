#ifndef GAMEEVENT_H
#define GAMEEVENT_H
/*****************************************************************************
 *
 * (Mushware file header version 1.0)
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.co.uk.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/

/*
 * $Id: GameEvent.h,v 1.2 2002/08/21 16:09:04 southa Exp $
 * $Log: GameEvent.h,v $
 * Revision 1.2  2002/08/21 16:09:04  southa
 * GameTypeRace state tweaks
 *
 * Revision 1.1  2002/08/18 20:44:34  southa
 * Initial chequepoint work
 *
 */

#include "mushCore.h"

class GameEvent
{
public:
    virtual ~GameEvent() {}
protected:
    GameEvent() {}
};

class GameEventStandingOn : public GameEvent
{
public:
    explicit GameEventStandingOn(U32 inValue) { mapValue = inValue; }
    U32 mapValue;
};

class GameEventSequenceAdvance : public GameEvent
{
public:
};
#endif
