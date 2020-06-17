//%Header {
/*****************************************************************************
 *
 * File: src/GL/GLTest.cpp
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
//%Header } U6i5FN2W/Jfue+zLRDGCMA
/*
 * $Id: GLTest.cpp,v 1.16 2006/06/01 15:38:53 southa Exp $
 * $Log: GLTest.cpp,v $
 * Revision 1.16  2006/06/01 15:38:53  southa
 * DrawArray verification and fixes
 *
 * Revision 1.15  2005/05/19 13:02:00  southa
 * Mac release work
 *
 * Revision 1.14  2004/01/02 21:13:05  southa
 * Source conditioning
 *
 * Revision 1.13  2003/09/17 19:40:30  southa
 * Source conditioning upgrades
 *
 * Revision 1.12  2003/08/21 23:08:29  southa
 * Fixed file headers
 *
 * Revision 1.11  2002/12/29 20:59:53  southa
 * More build fixes
 *
 * Revision 1.10  2002/12/20 13:17:35  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.9  2002/10/22 20:42:01  southa
 * Source conditioning
 *
 * Revision 1.8  2002/08/27 08:56:20  southa
 * Source conditioning
 *
 * Revision 1.7  2002/08/07 13:36:47  southa
 * Conditioned source
 *
 * Revision 1.6  2002/07/06 18:04:17  southa
 * More designer work
 *
 * Revision 1.5  2002/06/27 12:36:05  southa
 * Build process fixes
 *
 * Revision 1.4  2002/05/10 16:41:43  southa
 * Changed .hp files to .h
 *
 * Revision 1.3  2002/05/08 16:31:21  southa
 * Created API directory
 *
 * Revision 1.2  2002/03/07 22:24:34  southa
 * Command interpreter working
 *
 * Revision 1.1  2002/02/23 17:54:45  southa
 * Added GIF loader and GL tests
 *
 */

#include "GLTest.h"

#include "GLStandard.h"
#include "GLTest1AppHandler.h"

using namespace Mushware;
using namespace std;

