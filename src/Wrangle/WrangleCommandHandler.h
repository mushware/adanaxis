#ifndef WRANGLECOMMANDHANDLER_H
#define WRANGLECOMMANDHANDLER_H
/*****************************************************************************
 *
 * (Mushware file header version 1.1)
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/

/*
 * $Id: WrangleCommandHandler.h,v 1.5 2002/08/27 08:56:30 southa Exp $
 * $Log: WrangleCommandHandler.h,v $
 * Revision 1.5  2002/08/27 08:56:30  southa
 * Source conditioning
 *
 * Revision 1.4  2002/08/07 13:36:52  southa
 * Conditioned source
 *
 * Revision 1.3  2002/07/06 18:04:21  southa
 * More designer work
 *
 * Revision 1.2  2002/06/27 12:36:09  southa
 * Build process fixes
 *
 * Revision 1.1  2002/05/10 16:40:39  southa
 * Changed .hp files to .h
 *
 * Revision 1.1  2002/05/09 17:08:08  southa
 * Fixed for gcc 3.0
 *
 * Revision 1.2  2002/05/08 16:31:21  southa
 * Created API directory
 *
 * Revision 1.1  2002/03/18 22:21:12  southa
 * Initial wrangle command
 *
 */

#include "mushCore.h"

class WrangleCommandHandler
{
public:
    static void Install(void);
    static CoreScalar Wrangle(CoreCommand& ioCommand, CoreEnv& ioEnv);
};
#endif
