#ifndef GLTEST_H
#define GLTEST_H
/*****************************************************************************
 *
 * (Mushware file header version 1.2)
 *
 * This file contains original work by Andy Southgate.
 * Copyright Andy Southgate 2002.  All rights reserved.
 * Contact details can be found at http://www.mushware.com/
 *
 ****************************************************************************/

/*
 * $Id: GLTest.h,v 1.6 2002/10/22 20:42:01 southa Exp $
 * $Log: GLTest.h,v $
 * Revision 1.6  2002/10/22 20:42:01  southa
 * Source conditioning
 *
 * Revision 1.5  2002/08/27 08:56:20  southa
 * Source conditioning
 *
 * Revision 1.4  2002/08/07 13:36:47  southa
 * Conditioned source
 *
 * Revision 1.3  2002/07/06 18:04:17  southa
 * More designer work
 *
 * Revision 1.2  2002/06/27 12:36:05  southa
 * Build process fixes
 *
 * Revision 1.1  2002/05/10 16:41:43  southa
 * Changed .hp files to .h
 *
 * Revision 1.1  2002/02/23 17:54:45  southa
 * Added GIF loader and GL tests
 *
 */

#include "GLStandard.h"

class GLTest
{
public:
    static void Test1(const string& inStr);
};
#endif
