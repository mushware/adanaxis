/*
 * $Id: MustlWebCommands.h,v 1.1 2003/01/14 17:38:22 southa Exp $
 * $Log: MustlWebCommands.h,v $
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
