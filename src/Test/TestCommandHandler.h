#ifndef TESTCOMMANDHANDLER_H
#define TESTCOMMANDHANDLER_H
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
 * $Id: TestCommandHandler.h,v 1.1 2002/05/10 16:39:35 southa Exp $
 * $Log: TestCommandHandler.h,v $
 * Revision 1.1  2002/05/10 16:39:35  southa
 * Changed .hp files to .h
 *
 * Revision 1.3  2002/05/09 18:01:39  southa
 * Rebuild under cygwin
 *
 * Revision 1.2  2002/03/07 22:24:34  southa
 * Command interpreter working
 *
 * Revision 1.1.1.1  2002/02/11 22:30:09  southa
 * Created
 *
 */
 
#include "mushCore.h"
 
class TestCommandHandler
{
public:
    static CoreScalar Execute(CoreCommand& ioCommand, CoreEnv& ioEnv);
    static void Install(void);
};
#endif
