//%includeGuardStart {
#ifndef GAMECOMMANDHANDLER_H
#define GAMECOMMANDHANDLER_H
//%includeGuardStart } FYoHIO/CPCG1pDzYXwbKbg
//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameCommandHandler.h
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } PlnS42gkKu6Jk7XBx4Wu3w
/*
 * $Id: GameCommandHandler.h,v 1.15 2003/10/04 15:32:08 southa Exp $
 * $Log: GameCommandHandler.h,v $
 * Revision 1.15  2003/10/04 15:32:08  southa
 * Module split
 *
 * Revision 1.14  2003/09/17 19:40:31  southa
 * Source conditioning upgrades
 *
 * Revision 1.13  2003/08/21 23:08:35  southa
 * Fixed file headers
 *
 * Revision 1.12  2003/01/11 13:03:12  southa
 * Use Mushcore header
 *
 * Revision 1.11  2003/01/09 14:57:00  southa
 * Created Mushcore
 *
 * Revision 1.10  2002/12/20 13:17:37  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.9  2002/11/17 13:38:30  southa
 * Game selection
 *
 * Revision 1.8  2002/10/22 20:42:02  southa
 * Source conditioning
 *
 * Revision 1.7  2002/10/17 12:35:30  southa
 * Save path and update check
 *
 * Revision 1.6  2002/08/27 08:56:22  southa
 * Source conditioning
 *
 * Revision 1.5  2002/08/07 13:36:48  southa
 * Conditioned source
 *
 * Revision 1.4  2002/07/06 18:04:18  southa
 * More designer work
 *
 * Revision 1.3  2002/06/27 12:36:06  southa
 * Build process fixes
 *
 * Revision 1.2  2002/05/10 16:39:34  southa
 * Changed .hp files to .h
 *
 * Revision 1.1  2002/05/10 15:35:27  southa
 * Added Game group
 *
 */

#include "Mushcore.h"

class GameCommandHandler
{
public:
    static void Install(void);
    static MushcoreScalar SetSavePath(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static MushcoreScalar UpdateCheck(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static MushcoreScalar ReadDirectoryToMenu(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
