/*
 * $Id: WrangleCommandHandler.h,v 1.1 2002/05/09 17:08:08 southa Exp $
 * $Log: WrangleCommandHandler.h,v $
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
