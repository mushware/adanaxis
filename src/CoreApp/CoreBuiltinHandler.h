#ifndef COREBUILTINHANDLER_H
#define COREBUILTINHANDLER_H
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
 * $Id: CoreBuiltinHandler.h,v 1.4 2002/08/27 08:56:16 southa Exp $
 * $Log: CoreBuiltinHandler.h,v $
 * Revision 1.4  2002/08/27 08:56:16  southa
 * Source conditioning
 *
 * Revision 1.3  2002/08/07 13:36:44  southa
 * Conditioned source
 *
 * Revision 1.2  2002/07/06 18:04:15  southa
 * More designer work
 *
 * Revision 1.1  2002/07/02 09:10:06  southa
 * Name changed to CoreBuiltinHandler
 *
 * Revision 1.2  2002/06/27 12:36:02  southa
 * Build process fixes
 *
 * Revision 1.1  2002/05/10 16:39:37  southa
 * Changed .hp files to .h
 *
 * Revision 1.1  2002/03/07 22:24:32  southa
 * Command interpreter working
 *
 */

#include "CoreCommandHandler.h"

class CoreBuiltinHandler
{
public:
    static CoreScalar Load(CoreCommand& ioCommand, CoreEnv &ioEnv);
    static CoreScalar ConfigSet(CoreCommand& ioCommand, CoreEnv &ioEnv);
    static void Install(void);
protected:

private:
};
#endif
