#ifndef GAMEEVENT_H
#define GAMEEVENT_H
/*****************************************************************************
 *
 * (Mushware file header version 1.3)
 *
 * Copyrighted work by Andy Southgate 2003
 *
 * This file may be redistributed and/or modified under the terms of the
 * Mushware licence which you should have received with this file.  For
 * information, please contact the author via http://www.mushware.com/.
 *
 ****************************************************************************/

/*
 * $Id: GameEvent.h,v 1.7 2003/01/11 13:03:13 southa Exp $
 * $Log: GameEvent.h,v $
 * Revision 1.7  2003/01/11 13:03:13  southa
 * Use Mushcore header
 *
 * Revision 1.6  2002/12/20 13:17:39  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.5  2002/10/22 20:42:03  southa
 * Source conditioning
 *
 * Revision 1.4  2002/10/08 11:58:52  southa
 * Light cache
 *
 * Revision 1.3  2002/08/27 08:56:23  southa
 * Source conditioning
 *
 * Revision 1.2  2002/08/21 16:09:04  southa
 * GameTypeRace state tweaks
 *
 * Revision 1.1  2002/08/18 20:44:34  southa
 * Initial chequepoint work
 *
 */

#include "Mushcore.h"

#include "GameFloorMap.h"

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
    explicit GameEventStandingOn(const GameFloorMap::tMapVector& inValues) { mapValues = inValues; }
    GameFloorMap::tMapVector mapValues;
};

class GameEventSequenceAdvance : public GameEvent
{
public:
};
#endif
