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
