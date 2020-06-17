//%includeGuardStart {
#ifndef GAMECOMMANDHANDLER_H
#define GAMECOMMANDHANDLER_H
//%includeGuardStart } FYoHIO/CPCG1pDzYXwbKbg
//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameCommandHandler.h
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
//%Header } O4WI9gBmcsvvJMPEF1T4Tg
/*
 * $Id: GameCommandHandler.h,v 1.20 2006/06/01 20:12:58 southa Exp $
 * $Log: GameCommandHandler.h,v $
 * Revision 1.20  2006/06/01 20:12:58  southa
 * Initial texture caching
 *
 * Revision 1.19  2006/06/01 15:38:56  southa
 * DrawArray verification and fixes
 *
 * Revision 1.18  2005/05/19 13:02:01  southa
 * Mac release work
 *
 * Revision 1.17  2004/01/06 20:46:49  southa
 * Build fixes
 *
 * Revision 1.16  2004/01/02 21:13:06  southa
 * Source conditioning
 *
 * Revision 1.15  2003/10/04 15:32:08  southa
 * Module split
 *
 * Revision 1.14  2003/09/17 19:40:31  southa
 * Source conditioning upgrades
 *
 * Revision 1.13  2003/08/21 23:08:35  southa
 * Fixed file headers
 *
 * Revision 1.12  2003/01/11 13:03:12  southa
 * Use Mushcore header
 *
 * Revision 1.11  2003/01/09 14:57:00  southa
 * Created Mushcore
 *
 * Revision 1.10  2002/12/20 13:17:37  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.9  2002/11/17 13:38:30  southa
 * Game selection
 *
 * Revision 1.8  2002/10/22 20:42:02  southa
 * Source conditioning
 *
 * Revision 1.7  2002/10/17 12:35:30  southa
 * Save path and update check
 *
 * Revision 1.6  2002/08/27 08:56:22  southa
 * Source conditioning
 *
 * Revision 1.5  2002/08/07 13:36:48  southa
 * Conditioned source
 *
 * Revision 1.4  2002/07/06 18:04:18  southa
 * More designer work
 *
 * Revision 1.3  2002/06/27 12:36:06  southa
 * Build process fixes
 *
 * Revision 1.2  2002/05/10 16:39:34  southa
 * Changed .hp files to .h
 *
 * Revision 1.1  2002/05/10 15:35:27  southa
 * Added Game group
 *
 */

#include "mushMushcore.h"

class GameCommandHandler
{
public:
    static void Install(void);
    static MushcoreScalar SetSavePath(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static MushcoreScalar SetCachePath(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static MushcoreScalar UpdateCheck(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
    static MushcoreScalar ReadDirectoryToMenu(MushcoreCommand& ioCommand, MushcoreEnv& ioEnv);
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
