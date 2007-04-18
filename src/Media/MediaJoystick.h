//%includeGuardStart {
#ifndef MEDIAJOYSTICK_H
#define MEDIAJOYSTICK_H
//%includeGuardStart } zVXRwFJkY+4ff5QZ534fbg
//%Header {
/*****************************************************************************
 *
 * File: src/Media/MediaJoystick.h
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
//%Header } i0kk63WdoYiCW1djxS6GyA
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
