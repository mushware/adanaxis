#ifndef MUSHCOREENVOUTPUT_H
#define MUSHCOREENVOUTPUT_H
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
 * $Id: MushcoreEnvOutput.h,v 1.1 2003/01/09 14:57:06 southa Exp $
 * $Log: MushcoreEnvOutput.h,v $
 * Revision 1.1  2003/01/09 14:57:06  southa
 * Created Mushcore
 *
 * Revision 1.2  2002/12/20 13:17:32  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.1  2002/11/07 11:59:02  southa
 * Web commands
 *
 */

#include "MushcoreStandard.h"

class MushcoreEnv;

class MushcoreEnvOutput
{
public:
    MushcoreEnvOutput(MushcoreEnv& inEnv, std::ostream& inOut);
    ~MushcoreEnvOutput();

private:
    MushcoreEnv& m_envRef;
};
#endif
