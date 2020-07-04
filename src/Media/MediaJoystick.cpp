//%Header {
/*****************************************************************************
 *
 * File: src/Media/MediaJoystick.cpp
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
//%Header } QTCqGGve2ziFnEL2Ljyj9A
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


