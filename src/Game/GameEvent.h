/*
 * $Id$
 * $Log$
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
