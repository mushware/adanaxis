/*
 * $Id$
 * $Log$
 */

#include "TestMustlStandard.h"

class MushcoreCommand;
class MushcoreEnv;
class MushcoreScalar;

class TestMustlPostHandler
{
public:
    static void Install(void);
    static MushcoreScalar PostHandler(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
};
