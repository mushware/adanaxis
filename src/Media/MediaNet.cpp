/*
 * $Id$
 * $Log$
 */

#include "MediaNet.h"

#include "MediaSDL.h"


auto_ptr<MediaNet> MediaNet::m_instance;


MediaNet::MediaNet()
{
    MediaSDL::Instance().Init(0);
    if (SDLNet_Init() == -1)
    {
        ostringstream message;
        message << "Failed to init SDL_Net: " << SDLNet_GetError();
        throw(DeviceFail(message.str()));
    }
}

MediaNet::~MediaNet()
{
    SDLNet_Quit();
}
