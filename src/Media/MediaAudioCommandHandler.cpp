/*****************************************************************************
 *
 * (Mushware file header version 1.0)
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.co.uk.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/


/*
 * $Id: MediaAudioCommandHandler.cpp,v 1.6 2002/08/13 17:50:21 southa Exp $
 * $Log: MediaAudioCommandHandler.cpp,v $
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

#include "mushCore.h"
#include "MediaAudio.h"

CoreInstaller MediaAudioCommandHandlerInstaller(MediaAudioCommandHandler::Install);

CoreScalar
MediaAudioCommandHandler::PlayMusic(CoreCommand& ioCommand, CoreEnv& ioEnv)
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
    return CoreScalar(0);
}

void
MediaAudioCommandHandler::Install(void)
{
    CoreApp::Instance().AddHandler("playmusic", PlayMusic);
}
