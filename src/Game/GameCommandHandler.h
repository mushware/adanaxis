#ifndef GAMECOMMANDHANDLER_H
#define GAMECOMMANDHANDLER_H
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
 * $Id: GameCommandHandler.h,v 1.12 2003/01/11 13:03:12 southa Exp $
 * $Log: GameCommandHandler.h,v $
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
    static MushcoreScalar Game(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static MushcoreScalar SetSavePath(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static MushcoreScalar UpdateCheck(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static MushcoreScalar ReadDirectoryToMenu(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
};
#endif
