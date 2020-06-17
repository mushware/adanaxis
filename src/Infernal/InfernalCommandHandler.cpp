//%Header {
/*****************************************************************************
 *
 * File: src/Infernal/InfernalCommandHandler.cpp
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
//%Header } RlyphVULavpZLTbd8q1n1g
/*
 * $Id: InfernalCommandHandler.cpp,v 1.6 2006/06/01 15:39:01 southa Exp $
 * $Log: InfernalCommandHandler.cpp,v $
 * Revision 1.6  2006/06/01 15:39:01  southa
 * DrawArray verification and fixes
 *
 * Revision 1.5  2005/05/19 13:02:04  southa
 * Mac release work
 *
 * Revision 1.4  2004/01/06 20:46:50  southa
 * Build fixes
 *
 * Revision 1.3  2004/01/01 23:04:02  southa
 * XCode fixes
 *
 * Revision 1.2  2004/01/01 21:15:45  southa
 * Created XCode project
 *
 * Revision 1.1  2003/10/04 15:32:10  southa
 * Module split
 *
 */

#include "InfernalCommandHandler.h"

#include "InfernalAppHandler.h"
#include "InfernalInfo.h"
#include "InfernalWebCommands.h"

#include "mushMushcore.h"
#include "mushPlatform.h"

using namespace Mushware;
using namespace std;

MushcoreInstaller InfernalCommandHandlerInstaller(InfernalCommandHandler::Install);

MushcoreScalar
InfernalCommandHandler::Infernal(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    MushcoreAppHandler::Sgl().Mutate(new InfernalAppHandler);
    MushcoreInfo::SingletonMutate(new InfernalInfo);
    InfernalWebCommands::Install();
    
    return MushcoreScalar(0);
}

void
InfernalCommandHandler::Install(void)
{
    MushcoreInterpreter::Sgl().HandlerAdd("infernal", Infernal);
}
