/*
 * $Id: CoreCommandHandler.h,v 1.2 2002/03/07 22:24:32 southa Exp $
 * $Log: CoreCommandHandler.h,v $
 * Revision 1.2  2002/03/07 22:24:32  southa
 * Command interpreter working
 *
 * Revision 1.1  2002/03/05 22:44:45  southa
 * Changes to command handling
 *
 * Revision 1.2  2002/03/02 12:08:23  southa
 * First stage rework of command handler
 * Added core target
 *
 * Revision 1.1.1.1  2002/02/11 22:30:08  southa
 * Created
 *
 */

#include "CoreStandard.h"

#include "CoreScalar.h"
#include "CoreCommand.h"
#include "CoreEnv.h"

typedef 
CoreScalar (*CoreCommandHandler)(CoreCommand& ioCommand, CoreEnv& ioEnv);
