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
 * $Id: MediaAudioCommandHandler.cpp,v 1.1 2002/07/02 15:48:30 southa Exp $
 * $Log: MediaAudioCommandHandler.cpp,v $
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
