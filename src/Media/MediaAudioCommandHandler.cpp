//%Header {
/*****************************************************************************
 *
 * File: src/Media/MediaAudioCommandHandler.cpp
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
//%Header } /VxXmWdPn3bYKMbY4KlWdA
/*
 * $Id: MediaAudioCommandHandler.cpp,v 1.24 2006/06/01 15:39:13 southa Exp $
 * $Log: MediaAudioCommandHandler.cpp,v $
 * Revision 1.24  2006/06/01 15:39:13  southa
 * DrawArray verification and fixes
 *
 * Revision 1.23  2005/05/19 13:02:08  southa
 * Mac release work
 *
 * Revision 1.22  2004/01/06 20:46:51  southa
 * Build fixes
 *
 * Revision 1.21  2004/01/02 21:13:10  southa
 * Source conditioning
 *
 * Revision 1.20  2003/09/17 19:40:34  southa
 * Source conditioning upgrades
 *
 * Revision 1.19  2003/08/21 23:09:00  southa
 * Fixed file headers
 *
 * Revision 1.18  2003/01/20 12:23:22  southa
 * Code and interface tidying
 *
 * Revision 1.17  2003/01/20 10:45:28  southa
 * Singleton tidying
 *
 * Revision 1.16  2003/01/13 14:32:01  southa
 * Build frameworks for Mac OS X
 *
 * Revision 1.15  2003/01/12 17:32:57  southa
 * Mushcore work
 *
 * Revision 1.14  2003/01/11 17:07:53  southa
 * Mushcore library separation
 *
 * Revision 1.13  2003/01/11 13:03:15  southa
 * Use Mushcore header
 *
 * Revision 1.12  2003/01/09 14:57:04  southa
 * Created Mushcore
 *
 * Revision 1.11  2002/12/29 20:59:58  southa
 * More build fixes
 *
 * Revision 1.10  2002/12/20 13:17:44  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.9  2002/10/22 20:42:07  southa
 * Source conditioning
 *
 * Revision 1.8  2002/08/27 08:56:28  southa
 * Source conditioning
 *
 * Revision 1.7  2002/08/16 19:46:07  southa
 * MediaSound work
 *
 * Revision 1.6  2002/08/13 17:50:21  southa
 * Added playsound command
 *
 * Revision 1.5  2002/08/07 13:36:51  southa
 * Conditioned source
 *
 * Revision 1.4  2002/07/11 10:19:01  southa
 * Removed debug code
 *
 * Revision 1.3  2002/07/11 10:12:03  southa
 * Tweaks for BSD build
 *
 * Revision 1.2  2002/07/06 18:04:20  southa
 * More designer work
 *
 * Revision 1.1  2002/07/02 15:48:30  southa
 * Floor map designer
 *
 */

#include "MediaAudioCommandHandler.h"

#include "MediaAudio.h"
#include "MediaSTL.h"

#include "mushMushcore.h"

using namespace Mushware;
using namespace std;

MushcoreInstaller MediaAudioCommandHandlerInstaller(MediaAudioCommandHandler::Install);

MushcoreScalar
MediaAudioCommandHandler::PlayMusic(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    if (ioCommand.NumParams() != 1)
    {
        throw(MushcoreCommandFail("Usage: playmusic(filename)"));
    }
    string filename;
    ioCommand.PopParam(filename);
    try
    {
        MediaAudio::Sgl().PlayMusic(filename);
    }
    catch (MushcoreDeviceFail& e)
    {
        throw(MushcoreCommandFail(string("Command failed: ")+e.what()));
    }
    return MushcoreScalar(0);
}

void
MediaAudioCommandHandler::Install(void)
{
    MushcoreInterpreter::Sgl().HandlerAdd("playmusic", PlayMusic);
}
