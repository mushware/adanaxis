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
 * $Id: MushcoreEnvOutput.cpp,v 1.3 2002/12/29 20:59:51 southa Exp $
 * $Log: MushcoreEnvOutput.cpp,v $
 * Revision 1.3  2002/12/29 20:59:51  southa
 * More build fixes
 *
 * Revision 1.2  2002/12/20 13:17:32  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.1  2002/11/07 11:59:02  southa
 * Web commands
 *
 */

#include "MushcoreEnvOutput.h"

#include "MushcoreEnv.h"

using namespace Mushware;
using namespace std;

MushcoreEnvOutput::MushcoreEnvOutput(MushcoreEnv& inEnv, ostream& inOut) :
    m_envRef(inEnv)
{
    m_envRef.OutSet(inOut);
}

MushcoreEnvOutput::~MushcoreEnvOutput()
{
    m_envRef.OutReset();
}
