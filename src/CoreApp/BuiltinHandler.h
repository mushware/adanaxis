/*
 * $Id: BuiltinHandler.h,v 1.1 2002/03/07 22:24:32 southa Exp $
 * $Log: BuiltinHandler.h,v $
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
