/*****************************************************************************
 *
 * (Mushware file header version 1.2)
 *
 * This file contains original work by Andy Southgate.
 * Copyright Andy Southgate 2002.  All rights reserved.
 * Contact details can be found at http://www.mushware.com/
 *
 ****************************************************************************/

/*
 * $Id: MediaAudioCommandHandler.cpp,v 1.13 2003/01/11 13:03:15 southa Exp $
 * $Log: MediaAudioCommandHandler.cpp,v $
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
#include "Mushcore.h"

using namespace Mushware;
using namespace std;

MushcoreInstaller MediaAudioCommandHandlerInstaller(MediaAudioCommandHandler::Install);

MushcoreScalar
MediaAudioCommandHandler::PlayMusic(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv)
{
    if (ioCommand.NumParams() != 1)
    {
        throw(CommandFail("Usage: playmusic(filename)"));
    }
    string filename;
    ioCommand.PopParam(filename);
    try
    {
        MediaAudio::Instance().PlayMusic(filename);
    }
    catch (DeviceFail& e)
    {
        throw(CommandFail(string("Command failed: ")+e.what()));
    }
    return MushcoreScalar(0);
}

void
MediaAudioCommandHandler::Install(void)
{
    MushcoreInterpreter::Instance().AddHandler("playmusic", PlayMusic);
}
