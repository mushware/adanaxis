#ifndef GAMECOMMANDHANDLER_H
#define GAMECOMMANDHANDLER_H
/*****************************************************************************
 *
 * (Mushware file header version 1.0)
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.co.uk.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/


/*
 * $Id: GameCommandHandler.h,v 1.3 2002/06/27 12:36:06 southa Exp $
 * $Log: GameCommandHandler.h,v $
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

#include "mushCore.h"

class GameCommandHandler
{
public:
    static void Install(void);
    static CoreScalar Game(CoreCommand& ioCommand, CoreEnv& ioEnv);
};
#endif
