#ifndef COREBUILTINHANDLER_H
#define COREBUILTINHANDLER_H
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
 * $Id: CoreBuiltinHandler.h,v 1.5 2002/10/22 20:41:57 southa Exp $
 * $Log: CoreBuiltinHandler.h,v $
 * Revision 1.5  2002/10/22 20:41:57  southa
 * Source conditioning
 *
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
