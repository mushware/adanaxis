//%includeGuardStart {
#ifndef GAMETYPE_H
#define GAMETYPE_H
//%includeGuardStart } fiFGzXz++NMp6yAajC0kdA
//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameType.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2003.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } fusdHcJJ9bUvpylMoCVBZg
/*
 * $Id: GameType.h,v 1.14 2003/10/04 15:32:09 southa Exp $
 * $Log: GameType.h,v $
 * Revision 1.14  2003/10/04 15:32:09  southa
 * Module split
 *
 * Revision 1.13  2003/09/17 19:40:34  southa
 * Source conditioning upgrades
 *
 * Revision 1.12  2003/08/21 23:08:58  southa
 * Fixed file headers
 *
 * Revision 1.11  2003/01/11 13:03:15  southa
 * Use Mushcore header
 *
 * Revision 1.10  2003/01/09 14:57:04  southa
 * Created Mushcore
 *
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
 * InfernalTypeRace state tweaks
 *
 * Revision 1.2  2002/08/19 11:09:56  southa
 * InfernalTypeRace rendering
 *
 * Revision 1.1  2002/08/18 20:44:35  southa
 * Initial chequepoint work
 *
 */

#include "Mushcore.h"

class GameEvent;

class GameType : public MushcoreAbstractSingleton<GameType>, public MushcorePickle, protected MushcoreXMLHandler
{
public:
    virtual ~GameType() {}

    virtual void Move(void) = 0;
    virtual void EventHandler(const GameEvent& inEvent) = 0;
    virtual void Render(void) const = 0;
    virtual void Initialise(void) = 0;
    virtual bool IsGameOver(void) const = 0;

    static GameType *SingletonFactory(void);

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
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
