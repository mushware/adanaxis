#ifndef COREENV_HP
#define COREENV_HP
/*
 * $Id: CoreEnv.h,v 1.2 2002/03/07 22:24:33 southa Exp $
 * $Log: CoreEnv.h,v $
 * Revision 1.2  2002/03/07 22:24:33  southa
 * Command interpreter working
 *
 * Revision 1.1  2002/03/02 12:08:23  southa
 * First stage rework of command handler
 * Added core target
 *
 */

#include "CoreStandard.h"

#include "CoreScript.h"

class CoreEnv
{
public:
    void Enter(const CoreScript& inScript);
private:
    int temp;
};
#endif
