//%Header {
/*****************************************************************************
 *
 * File: src/Maurheen/MaurheenCommandHandler.cpp
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
//%Header } mUmXDkL5fDURiHhwydPkvg
/*
 * $Id: MaurheenCommandHandler.cpp,v 1.3 2006/06/01 15:39:11 southa Exp $
 * $Log: MaurheenCommandHandler.cpp,v $
 * Revision 1.3  2006/06/01 15:39:11  southa
 * DrawArray verification and fixes
 *
 * Revision 1.2  2005/05/19 13:02:07  southa
 * Mac release work
 *
 * Revision 1.1  2004/03/06 14:01:42  southa
 * Maurheen created
 *
 */

#include "MaurheenCommandHandler.h"

#include "MaurheenAppHandler.h"
#include "MaurheenInfo.h"

#include "mushMushcore.h"
#include "mushPlatform.h"

using namespace Mushware;
using namespace std;

MushcoreInstaller MaurheenCommandHandlerInstaller(MaurheenCommandHandler::Install);

MushcoreScalar
MaurheenCommandHandler::Maurheen(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    MushcoreInfo::SingletonMutate(new MaurheenInfo);

    MaurheenAppHandler *pAppHandler = new MaurheenAppHandler;
    MushcoreAppHandler::Sgl().Mutate(pAppHandler);
    pAppHandler->GameModeEnter(false);
    
    return MushcoreScalar(0);
}

void
MaurheenCommandHandler::Install(void)
{
    MushcoreInterpreter::Sgl().HandlerAdd("maurheen", Maurheen);
}
