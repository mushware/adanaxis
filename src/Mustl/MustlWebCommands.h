#ifndef MUSTLWEBCOMMANDS_H
#define MUSTLWEBCOMMANDS_H
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
 * $Id: MustlWebCommands.h,v 1.2 2003/01/15 13:27:32 southa Exp $
 * $Log: MustlWebCommands.h,v $
 * Revision 1.2  2003/01/15 13:27:32  southa
 * Static library linking fixes
 *
 * Revision 1.1  2003/01/14 17:38:22  southa
 * Mustl web configuration
 *
 */

#include "MustlStandard.h"

class MushcoreCommand;
class MushcoreEnv;
class MushcoreScalar;

class MustlWebCommands
{
public:
    static MushcoreScalar MustlPostValues(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static MushcoreScalar MustlInputWrite(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static MushcoreScalar MustlServerStatusWrite(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static MushcoreScalar MustlLinkStatusWrite(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static void NullFunction(void);
    static void Install(void);
};
#endif
