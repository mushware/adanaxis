/*
 * $Id$
 * $Log$
 */

#include "CoreEnvOutput.h"

#include "CoreEnv.h"

CoreEnvOutput::CoreEnvOutput(CoreEnv& inEnv, ostream& inOut) :
    m_envRef(inEnv)
{
    m_envRef.OutSet(inOut);
}

CoreEnvOutput::~CoreEnvOutput()
{
    m_envRef.OutReset();
}
