/*
 * $Id$
 * $Log$
 */

#include "CoreStandard.h"

class CoreEnv;

class CoreEnvOutput
{
public:
    CoreEnvOutput(CoreEnv& inEnv, ostream& inOut);
    ~CoreEnvOutput();

private:
    CoreEnv& m_envRef;
};
