/*
 * $Id: Mustl.cpp,v 1.1 2002/10/31 15:52:14 southa Exp $
 * $Log: Mustl.cpp,v $
 * Revision 1.1  2002/10/31 15:52:14  southa
 * First network code
 *
 */

#include "Mustl.h"

#include "MediaSDL.h"


auto_ptr<Mustl> Mustl::m_instance;


Mustl::Mustl()
{
    MediaSDL::Instance().Init(0);
    if (SDLNet_Init() == -1)
    {
        ostringstream message;
        message << "Failed to init SDL_Net: " << SDLNet_GetError();
        throw(DeviceFail(message.str()));
    }
}

Mustl::~Mustl()
{
    SDLNet_Quit();
}
