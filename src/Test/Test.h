#ifndef TEST_H
#define TEST_H
/*****************************************************************************
 *
 * (Mushware file header version 1.0)
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.co.uk.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/


/*
 * $Id: Test.h,v 1.3 2002/06/27 12:36:08 southa Exp $
 * $Log: Test.h,v $
 * Revision 1.3  2002/06/27 12:36:08  southa
 * Build process fixes
 *
 * Revision 1.2  2002/05/24 18:09:39  southa
 * CoreXML and game map
 *
 * Revision 1.1  2002/05/10 16:39:35  southa
 * Changed .hp files to .h
 *
 * Revision 1.4  2002/05/09 18:01:39  southa
 * Rebuild under cygwin
 *
 * Revision 1.3  2002/02/23 17:54:45  southa
 * Added GIF loader and GL tests
 *
 * Revision 1.2  2002/02/23 11:43:36  southa
 * Added AutoMonkey
 *
 * Revision 1.1.1.1  2002/02/11 22:30:09  southa
 * Created
 *
 */

#include "mushCore.h"

class Test
{
public:
    static void Test1(void);
    static void Test2(void);
    static void Test3(void);
    static void Test4(void);
    static void Test5(void);

private:
};
#endif
