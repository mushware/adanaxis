//%Header {
/*****************************************************************************
 *
 * File: src/CodeGen/CodeGenCommands.cpp
 *
 * Copyright: Andy Southgate 2002-2007, 2020
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 ****************************************************************************/
//%Header } iTZJsSgBQg/cPExmBZVnrQ


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
