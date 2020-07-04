//%includeGuardStart {
#ifndef MEDIAJOYSTICK_H
#define MEDIAJOYSTICK_H
//%includeGuardStart } zVXRwFJkY+4ff5QZ534fbg
//%Header {
/*****************************************************************************
 *
 * File: src/Media/MediaJoystick.h
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
//%Header } CscPpq4EZMSK8Bxyq0BesQ
/*
 * $Id: MediaJoystick.h,v 1.1 2006/07/11 19:49:04 southa Exp $
 * $Log: MediaJoystick.h,v $
 * Revision 1.1  2006/07/11 19:49:04  southa
 * Control menu
 *
 */

#include "MediaStandard.h"

typedef struct _SDL_Joystick SDL_Joystick;

class MediaJoystick : public MushcoreSingleton<MediaJoystick>
{
public:
    MediaJoystick();
    ~MediaJoystick();
    Mushware::U32 NumJoysticks(void);
    
private:
    std::vector<SDL_Joystick *> m_sticks;
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
