//%Header {
/*****************************************************************************
 *
 * File: src/TesseractTrainer/TesseractTrainerCommandHandler.cpp
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
//%Header } Dz+Nm7fXZEvu5c+B5QpOZw
/*
 * $Id: TesseractTrainerCommandHandler.cpp,v 1.4 2006/06/01 15:39:59 southa Exp $
 * $Log: TesseractTrainerCommandHandler.cpp,v $
 * Revision 1.4  2006/06/01 15:39:59  southa
 * DrawArray verification and fixes
 *
 * Revision 1.3  2005/06/03 13:36:44  southa
 * win32 build fixes
 *
 * Revision 1.2  2005/05/19 13:02:21  southa
 * Mac release work
 *
 * Revision 1.1  2005/02/03 15:46:56  southa
 * Quaternion work
 *
 */

#include "TesseractTrainerCommandHandler.h"

#include "TesseractTrainerAppHandler.h"
#include "TesseractTrainerInfo.h"

#include "mushMushcore.h"
#include "mushPlatform.h"

using namespace Mushware;
using namespace std;

MushcoreInstaller TesseractTrainerCommandHandlerInstaller(TesseractTrainerCommandHandler::Install);

MushcoreScalar
TesseractTrainerCommandHandler::TesseractTrainer(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    MushcoreInfo::SingletonMutate(new TesseractTrainerInfo);

    TesseractTrainerAppHandler *pAppHandler = new TesseractTrainerAppHandler;
    MushcoreAppHandler::Sgl().Mutate(pAppHandler);
    
    return MushcoreScalar(0);
}

void
TesseractTrainerCommandHandler::Install(void)
{
    MushcoreInterpreter::Sgl().HandlerAdd("tesseracttrainer", TesseractTrainer);
}
