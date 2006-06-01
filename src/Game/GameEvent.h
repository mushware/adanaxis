//%includeGuardStart {
#ifndef GAMEEVENT_H
#define GAMEEVENT_H
//%includeGuardStart } UEcZVIFbR3skg9cYgm/VwQ
//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameEvent.h
 *
 * Author: Andy Southgate 2002-2006
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
//%Header } b9oTKsoqj0Lv259N0V8BKw
/*
 * $Id: GameEvent.h,v 1.15 2005/05/19 13:02:02 southa Exp $
 * $Log: GameEvent.h,v $
 * Revision 1.15  2005/05/19 13:02:02  southa
 * Mac release work
 *
 * Revision 1.14  2004/01/06 20:46:50  southa
 * Build fixes
 *
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
