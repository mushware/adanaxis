#ifndef BUILTINHANDLER_H
#define BUILTINHANDLER_H
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
 * $Id: BuiltinHandler.h,v 1.1 2002/05/10 16:39:37 southa Exp $
 * $Log: BuiltinHandler.h,v $
 * Revision 1.1  2002/05/10 16:39:37  southa
 * Changed .hp files to .h
 *
 * Revision 1.1  2002/03/07 22:24:32  southa
 * Command interpreter working
 *
 */

#include "CoreCommandHandler.h"

class BuiltinHandler
{
public:
    static CoreScalar Load(CoreCommand& ioCommand, CoreEnv &ioEnv);
    static void Install(void);
protected:

private:
};
#endif
