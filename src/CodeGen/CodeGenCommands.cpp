//%Header {
/*****************************************************************************
 *
 * File: src/CodeGen/CodeGenCommands.cpp
 *
 * Copyright: Andy Southgate 2002-2006
 *
 * All rights reserved.  Distribution prohibited.  For information, please
 * contact the author via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } i3AyXZU3zbdohH/3DsabcQ


#include "CodeGenCommands.h"

#include "GameSTL.h"

#include "mushMushcore.h"
#include "mushGame.h"

using namespace Mushware;

MushcoreInstaller CodeGenCommandsInstaller(CodeGenCommands::Install);

MushcoreScalar
CodeGenCommands::CodeGenGenerate(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    U32 numParams=ioCommand.NumParams();
    if (numParams != 2)
    {
        throw(MushcoreCommandFail("Usage: CodeGenGenerate(start, number)"));
    }
    U32 startPoint;
    U32 numToGenerate;
    ioCommand.PopParam(startPoint);
    ioCommand.PopParam(numToGenerate);

    std::cout << "Generating codes for '" << MushcoreInfo::Sgl().PackageNameGet()<< "'" << std::endl;
    
    for (U32 i=0; i<numToGenerate; ++i)
    {
        std::ostringstream codeStrm;
        codeStrm << std::setw(6) << std::setfill('0') << i + startPoint;
        codeStrm << std::setw(6) << std::setfill('0') << GameUtils::HashGenerate(i + startPoint) % 1000000;
        if (GameUtils::CodeVerify(codeStrm.str()))
        {
            std::cout << codeStrm.str() << std::endl;
        }
        else
        {
            throw MushcoreCommandFail("New code "+codeStrm.str()+" failed to verify");
        }
    }
    
    return MushcoreScalar(0);
}

void
CodeGenCommands::Install(void)
{
    MushcoreInterpreter::Sgl().HandlerAdd("CodeGenGenerate", CodeGenGenerate);
}
