/*
 * $Id: LaunchCommandHandler.h,v 1.3 2002/03/07 22:24:34 southa Exp $
 * $Log: LaunchCommandHandler.h,v $
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
