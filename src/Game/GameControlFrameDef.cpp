//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameControlFrameDef.cpp
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
//%Header } ckVhGtKHkk2TzceUHs7vxQ
/*
 * $Id: GameControlFrameDef.cpp,v 1.10 2006/06/01 15:38:56 southa Exp $
 * $Log: GameControlFrameDef.cpp,v $
 * Revision 1.10  2006/06/01 15:38:56  southa
 * DrawArray verification and fixes
 *
 * Revision 1.9  2005/05/19 13:02:02  southa
 * Mac release work
 *
 * Revision 1.8  2004/01/02 21:13:06  southa
 * Source conditioning
 *
 * Revision 1.7  2003/09/17 19:40:31  southa
 * Source conditioning upgrades
 *
 * Revision 1.6  2003/08/21 23:08:37  southa
 * Fixed file headers
 *
 * Revision 1.5  2003/01/13 14:31:57  southa
 * Build frameworks for Mac OS X
 *
 * Revision 1.4  2002/12/29 20:59:54  southa
 * More build fixes
 *
 * Revision 1.3  2002/12/20 13:17:38  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.2  2002/12/04 15:39:58  southa
 * Multiplayer work
 *
 * Revision 1.1  2002/12/04 00:37:11  southa
 * ControlFrameDef work
 *
 */

#include "GameControlFrameDef.h"

#include "GameSTL.h"

using namespace Mushware;
using namespace std;

void
GameControlFrameDef::Print(ostream& ioOut) const
{
    ioOut << "mouseDeltaX=" << static_cast<S32>(mouseDeltaX);
    ioOut << ", mouseDeltaY=" << static_cast<S32>(mouseDeltaY);
    ioOut << ", keyState=" << hex << static_cast<U32>(keyState) << dec;
}
