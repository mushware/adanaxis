//%includeGuardStart {
#ifndef GAMETYPE_H
#define GAMETYPE_H
//%includeGuardStart } fiFGzXz++NMp6yAajC0kdA
//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameType.h
 *
 * Author: Andy Southgate 2002-2007
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
//%Header } VAqFmeVoUYHHkMCCBveGeA
/*
 * $Id: GameType.h,v 1.19 2006/06/01 15:39:00 southa Exp $
 * $Log: GameType.h,v $
 * Revision 1.19  2006/06/01 15:39:00  southa
 * DrawArray verification and fixes
 *
 * Revision 1.18  2005/05/19 13:02:03  southa
 * Mac release work
 *
 * Revision 1.17  2004/01/06 20:46:50  southa
 * Build fixes
 *
 * Revision 1.16  2004/01/02 21:13:08  southa
 * Source conditioning
 *
 * Revision 1.15  2003/10/07 22:40:05  southa
 * Created MeshMover
 *
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

#include "mushMushcore.h"

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
