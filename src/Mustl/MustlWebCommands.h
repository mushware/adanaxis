/*
 * $Id$
 * $Log$
 */

#include "MustlStandard.h"

class MushcoreCommand;
class MushcoreEnv;
class MushcoreScalar;

class MustlWebCommands
{
public:
    static void Install(void);
    static MushcoreScalar MustlPostValues(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static MushcoreScalar MustlInputWrite(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static MushcoreScalar MustlServerStatusWrite(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static MushcoreScalar MustlLinkStatusWrite(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
};
