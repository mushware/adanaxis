/*
 * $Id: GameEvent.h,v 1.1 2002/08/18 20:44:34 southa Exp $
 * $Log: GameEvent.h,v $
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
