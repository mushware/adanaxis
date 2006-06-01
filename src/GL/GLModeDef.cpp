//%Header {
/*****************************************************************************
 *
 * File: src/GL/GLModeDef.cpp
 *
 * Author: Andy Southgate 2002-2006
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
//%Header } vhAMnmvsnbGEXwx1Py1zUQ
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
