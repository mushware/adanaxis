#ifndef COREENVOUTPUT_H
#define COREENVOUTPUT_H
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
 * $Id: CoreEnvOutput.h,v 1.1 2002/11/07 11:59:02 southa Exp $
 * $Log: CoreEnvOutput.h,v $
 * Revision 1.1  2002/11/07 11:59:02  southa
 * Web commands
 *
 */

#include "CoreStandard.h"

class CoreEnv;

class CoreEnvOutput
{
public:
    CoreEnvOutput(CoreEnv& inEnv, std::ostream& inOut);
    ~CoreEnvOutput();

private:
    CoreEnv& m_envRef;
};
#endif
