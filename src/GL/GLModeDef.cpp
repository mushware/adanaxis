/*****************************************************************************
 *
 * (Mushware file header version 1.1)
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/

/*
 *  GLModeDef.cpp
 *  core-app
 *
 *  Created by Andy Southgate on Mon Oct 14 2002.
 *  Copyright (c) 2002 __MyCompanyName__. All rights reserved.
 *
 */

#include "GLModeDef.h"

GLModeDef::GLModeDef()
{
    *this = Default();
}

GLModeDef
GLModeDef::Default(void)
{
    return GLModeDef("Default 640x480",640,480,32,0,GLModeDef::kScreenWindow,GLModeDef::kCursorShow,GLModeDef::kSyncSoft);
}
