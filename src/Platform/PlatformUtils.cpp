//%Header {
/*****************************************************************************
 *
 * File: src/Platform/PlatformUtils.cpp
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
//%Header } 6F4kDw3WcsUhxk99oUiYkw
/*
 * $Id: PlatformUtils.cpp,v 1.21 2007/06/25 17:58:49 southa Exp $
 * $Log: PlatformUtils.cpp,v $
 * Revision 1.21  2007/06/25 17:58:49  southa
 * X11 fixes
 *
 * Revision 1.20  2007/04/18 09:23:23  southa
 * Header and level fixes
 *
 * Revision 1.19  2006/06/01 15:39:57  southa
 * DrawArray verification and fixes
 *
 * Revision 1.18  2005/05/19 13:02:21  southa
 * Mac release work
 *
 * Revision 1.17  2004/01/02 21:13:16  southa
 * Source conditioning
 *
 * Revision 1.16  2003/09/17 19:40:39  southa
 * Source conditioning upgrades
 *
 * Revision 1.15  2003/08/21 23:09:34  southa
 * Fixed file headers
 *
 * Revision 1.14  2003/02/05 18:49:52  southa
 * Build fixes
 *
 * Revision 1.13  2002/12/29 21:00:00  southa
 * More build fixes
 *
 * Revision 1.12  2002/12/20 13:17:47  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.11  2002/12/12 18:38:58  southa
 * Mustl separation
 *
 * Revision 1.10  2002/11/01 17:24:49  southa
 * Network links on win32
 *
 * Revision 1.9  2002/11/01 16:56:49  southa
 * Fixed platform inclusion
 *
 * Revision 1.8  2002/10/22 20:42:07  southa
 * Source conditioning
 *
 * Revision 1.7  2002/10/14 18:13:18  southa
 * GLModeDef work
 *
 * Revision 1.6  2002/08/27 08:56:29  southa
 * Source conditioning
 *
 * Revision 1.5  2002/08/07 13:36:51  southa
 * Conditioned source
 *
 * Revision 1.4  2002/07/06 18:04:20  southa
 * More designer work
 *
 * Revision 1.3  2002/06/27 12:36:08  southa
 * Build process fixes
 *
 * Revision 1.2  2002/06/11 16:23:57  southa
 * New paths to data files
 *
 * Revision 1.1  2002/06/06 14:59:57  southa
 * Mouse fixes
 *
 * Revision 1.1  2002/06/06 10:40:09  southa
 * Created
 *
 */


/******************************************************************************
 *
 * This file is deliberately #including .cpp files, and is used only on
 * X11 builds so that automake chooses the X11 files based on the search path
 *
 *****************************************************************************/

#include "PlatformInputUtils.cpp"
#include "PlatformMiscUtils.cpp"
#include "PlatformVideoUtils.cpp"

