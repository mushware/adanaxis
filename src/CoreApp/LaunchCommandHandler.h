#ifndef LAUNCHCOMMANDHANDLER_H
#define LAUNCHCOMMANDHANDLER_H
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
 * $Id: LaunchCommandHandler.h,v 1.6 2002/10/22 20:41:59 southa Exp $
 * $Log: LaunchCommandHandler.h,v $
 * Revision 1.6  2002/10/22 20:41:59  southa
 * Source conditioning
 *
 * Revision 1.5  2002/08/27 08:56:18  southa
 * Source conditioning
 *
 * Revision 1.4  2002/08/07 13:36:46  southa
 * Conditioned source
 *
 * Revision 1.3  2002/07/06 18:04:17  southa
 * More designer work
 *
 * Revision 1.2  2002/06/27 12:36:05  southa
 * Build process fixes
 *
 * Revision 1.1  2002/05/10 16:39:38  southa
 * Changed .hp files to .h
 *
 * Revision 1.3  2002/03/07 22:24:34  southa
 * Command interpreter working
 *
 * Revision 1.2  2002/03/05 22:44:46  southa
 * Changes to command handling
 *
 * Revision 1.1.1.1  2002/02/11 22:30:08  southa
 * Created
 *
 */
 
#include "CoreCommandHandler.h"
 
class LaunchCommandHandler
{
public:
    static CoreScalar Launch(CoreCommand& ioCommand, CoreEnv &ioEnv);    
    static void Install(void);    
};
#endif
