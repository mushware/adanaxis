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
 * $Id: CoreEnvOutput.cpp,v 1.2 2002/12/20 13:17:32 southa Exp $
 * $Log: CoreEnvOutput.cpp,v $
 * Revision 1.2  2002/12/20 13:17:32  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.1  2002/11/07 11:59:02  southa
 * Web commands
 *
 */

#include "CoreEnvOutput.h"

#include "CoreEnv.h"

using namespace Mushware;
using namespace std;

CoreEnvOutput::CoreEnvOutput(CoreEnv& inEnv, ostream& inOut) :
    m_envRef(inEnv)
{
    m_envRef.OutSet(inOut);
}

CoreEnvOutput::~CoreEnvOutput()
{
    m_envRef.OutReset();
}
