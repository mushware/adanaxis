//%includeGuardStart {
#ifndef GAMEEVENT_H
#define GAMEEVENT_H
//%includeGuardStart } UEcZVIFbR3skg9cYgm/VwQ
//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameEvent.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } yDMnpO6dBYVbvQbZBWfOWw
/*
 * $Id: GameEvent.h,v 1.13 2004/01/02 21:13:07 southa Exp $
 * $Log: GameEvent.h,v $
 * Revision 1.13  2004/01/02 21:13:07  southa
 * Source conditioning
 *
 * Revision 1.12  2003/10/07 22:40:05  southa
 * Created MeshMover
 *
 * Revision 1.11  2003/10/04 15:32:09  southa
 * Module split
 *
 * Revision 1.10  2003/10/04 12:22:59  southa
 * File renaming
 *
 * Revision 1.9  2003/09/17 19:40:31  southa
 * Source conditioning upgrades
 *
 * Revision 1.8  2003/08/21 23:08:43  southa
 * Fixed file headers
 *
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
 * InfernalTypeRace state tweaks
 *
 * Revision 1.1  2002/08/18 20:44:34  southa
 * Initial chequepoint work
 *
 */

#include "mushMushcore.h"

class GameEvent
{
public:
    virtual ~GameEvent() {}
protected:
    GameEvent() {}
};

class GameEventReward : public GameEvent
{
public:
    explicit GameEventReward(const std::string& inName) { m_name = inName; }
    const std::string& NameGet(void) const { return m_name; }
private:
    std::string m_name;
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
