//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisCommandHandler.cpp
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
//%Header } U4dfcZ2+ck6QYPknYbgsXw
/*
 * $Id: AdanaxisCommandHandler.cpp,v 1.7 2007/04/18 09:21:59 southa Exp $
 * $Log: AdanaxisCommandHandler.cpp,v $
 * Revision 1.7  2007/04/18 09:21:59  southa
 * Header and level fixes
 *
 * Revision 1.6  2006/08/01 17:21:22  southa
 * River demo
 *
 * Revision 1.5  2006/06/30 15:05:30  southa
 * Texture and buffer purge
 *
 * Revision 1.4  2006/06/01 15:38:46  southa
 * DrawArray verification and fixes
 *
 * Revision 1.3  2005/07/06 19:08:26  southa
 * Adanaxis control work
 *
 * Revision 1.2  2005/06/14 13:25:32  southa
 * Adanaxis work
 *
 * Revision 1.1  2005/06/13 17:34:54  southa
 * Adanaxis creation
 *
 */

#include "AdanaxisCommandHandler.h"

#include "AdanaxisAppHandler.h"
#include "AdanaxisInfo.h"

#include "mushMushcore.h"
#include "mushPlatform.h"

using namespace Mushware;
using namespace std;

MushcoreInstaller AdanaxisCommandHandlerInstaller(AdanaxisCommandHandler::Install);

MushcoreScalar
AdanaxisCommandHandler::Adanaxis(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    MushcoreInfo::SingletonMutate(new AdanaxisInfo);

    AdanaxisAppHandler *pAppHandler = new AdanaxisAppHandler("adanaxis");
    
    MushcoreAppHandler::Sgl().Mutate(pAppHandler);

    MushcoreLog::Sgl().PackageHasChanged();
    
    return MushcoreScalar(0);
}

void
AdanaxisCommandHandler::Install(void)
{
    MushcoreInterpreter::Sgl().HandlerAdd("adanaxis", Adanaxis);
}
