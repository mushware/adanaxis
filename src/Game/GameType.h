#ifndef GAMETYPE_H
#define GAMETYPE_H
/*****************************************************************************
 *
 * (Mushware file header version 1.2)
 *
 * This file contains original work by Andy Southgate.
 * Copyright Andy Southgate 2002.  All rights reserved.
 * Contact details can be found at http://www.mushware.com/
 *
 ****************************************************************************/

/*
 * $Id: GameType.h,v 1.9 2002/12/20 13:17:44 southa Exp $
 * $Log: GameType.h,v $
 * Revision 1.9  2002/12/20 13:17:44  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.8  2002/11/24 23:18:26  southa
 * Added type name accessor to MushcorePickle
 *
 * Revision 1.7  2002/10/22 20:42:07  southa
 * Source conditioning
 *
 * Revision 1.6  2002/08/27 08:56:28  southa
 * Source conditioning
 *
 * Revision 1.5  2002/08/24 15:42:24  southa
 * Race state change
 *
 * Revision 1.4  2002/08/22 10:11:11  southa
 * Save records, spacebar dialogues
 *
 * Revision 1.3  2002/08/21 16:09:04  southa
 * GameTypeRace state tweaks
 *
 * Revision 1.2  2002/08/19 11:09:56  southa
 * GameTypeRace rendering
 *
 * Revision 1.1  2002/08/18 20:44:35  southa
 * Initial chequepoint work
 *
 */

#include "mushCore.h"

class GameEvent;

class GameType : public MushcorePickle, protected MushcoreXMLHandler
{
public:
    virtual ~GameType() {}

    virtual void Move(void) = 0;
    virtual void EventHandler(const GameEvent& inEvent) = 0;
    virtual void Render(void) const = 0;
    virtual void Initialise(void) = 0;
    virtual bool IsGameOver(void) const = 0;
    
protected:
    void UnpicklePrologue(void) {}
    void UnpickleEpilogue(void) {}

private:
};

inline std::ostream& operator<<(std::ostream &inOut, const GameType& inObj)
{
    inObj.Pickle(inOut);
    return inOut;
}
#endif
