/*****************************************************************************
 *
 * (Mushware file header version 1.3)
 *
 * Copyrighted work by Andy Southgate 2003
 *
 * This file may be redistributed and/or modified under the terms of the
 * Mushware licence which you should have received with this file.  For
 * information, please contact the author via http://www.mushware.com/.
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

#include "GLSTL.h"

using namespace Mushware;
using namespace std;

GLModeDef::GLModeDef()
{
    *this = Default();
}

GLModeDef
GLModeDef::Default(void)
{
    return GLModeDef("Default 640x480",640,480,32,0,GLModeDef::kScreenWindow,GLModeDef::kCursorShow,GLModeDef::kSyncSoft);
}
