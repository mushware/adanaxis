//%Header {
/*****************************************************************************
 *
 * File: src/Media/MediaJoystick.cpp
 *
 * Author: Andy Southgate 2002-2007
 *
 * This file contains original work by Andy Southgate.  The author and his
 * employer (Mushware Limited) irrevocably waive all of their copyright rights
 * vested in this particular version of this file to the furthest extent
 * permitted.  The author and Mushware Limited also irrevocably waive any and
 * all of their intellectual property rights arising from said file and its
 * creation that would otherwise restrict the rights of any party to use and/or
 * distribute the use of, the techniques and methods used herein.  A written
 * waiver can be obtained via http://www.mushware.com/.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } Po5lbIePjsONtVWMiD5o/g
/*
 * $Id: MediaJoystick.cpp,v 1.2 2006/07/21 10:52:06 southa Exp $
 * $Log: MediaJoystick.cpp,v $
 * Revision 1.2  2006/07/21 10:52:06  southa
 * win32 build fixes
 *
 * Revision 1.1  2006/07/11 19:49:04  southa
 * Control menu
 *
 */

#include "MediaJoystick.h"

#include "MediaSDL.h"

MUSHCORE_SINGLETON_INSTANCE(MediaJoystick);

using namespace Mushware;
using namespace std;

MediaJoystick::MediaJoystick()
{
    MediaSDL::Sgl().InitJoystick();
    SDL_JoystickEventState(SDL_ENABLE);
    
    U32 numSticks = SDL_NumJoysticks();
    
    m_sticks.resize(numSticks);
    for (U32 i=0; i<numSticks; ++i)
    {
        m_sticks[i] = SDL_JoystickOpen(i);
        SDL_JoystickID stickId = SDL_JoystickInstanceID(m_sticks[i]);

        if (m_sticks[i] != NULL)
        {
            MushcoreLog::Sgl().InfoLog() << "Opening joystick " << i << endl;
            MushcoreLog::Sgl().InfoLog() << "- Name     : " << SDL_JoystickName(m_sticks[i]) << endl;
            MushcoreLog::Sgl().InfoLog() << "- Axes     : " << SDL_JoystickNumAxes(m_sticks[i]) << endl;
            MushcoreLog::Sgl().InfoLog() << "- Buttons  : " << SDL_JoystickNumButtons(m_sticks[i]) << endl;
            MushcoreLog::Sgl().InfoLog() << "- Balls    : " << SDL_JoystickNumBalls(m_sticks[i]) << endl;
            MushcoreLog::Sgl().InfoLog() << "- Hats     : " << SDL_JoystickNumHats(m_sticks[i]) << endl;
        }
    }
}

MediaJoystick::~MediaJoystick()
{
#ifndef WIN32
    // Windows doesn't like this
    for (U32 i=0; i<m_sticks.size(); ++i)
    {
        if (SDL_JoystickOpened(i))
        {
            SDL_JoystickClose(m_sticks[i]);
        }
    }
#endif    
    MediaSDL::Sgl().QuitJoystick();
}

Mushware::U32
MediaJoystick::NumJoysticks(void)
{
    return SDL_NumJoysticks();
}


