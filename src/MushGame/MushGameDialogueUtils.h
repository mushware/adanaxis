//%includeGuardStart {
#ifndef MUSHGAMEDIALOGUEUTILS_H
#define MUSHGAMEDIALOGUEUTILS_H
//%includeGuardStart } BHJFI+AsgSb1foZeqscgEA
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameDialogueUtils.h
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
//%Header } 4+g7ueZe/Wbm4lxb4pffwA
/*
 * $Id: MushGameDialogueUtils.h,v 1.5 2007/06/14 18:55:11 southa Exp $
 * $Log: MushGameDialogueUtils.h,v $
 * Revision 1.5  2007/06/14 18:55:11  southa
 * Level and display tweaks
 *
 * Revision 1.4  2007/04/18 09:22:39  southa
 * Header and level fixes
 *
 * Revision 1.3  2006/06/30 15:05:35  southa
 * Texture and buffer purge
 *
 * Revision 1.2  2006/06/01 15:39:21  southa
 * DrawArray verification and fixes
 *
 * Revision 1.1  2005/06/14 20:39:41  southa
 * Adanaxis work
 *
 */

#include "MushGameStandard.h"

#include "MushGameAppHandler.h"
#include "MushGameDialogue.h"

class MushGameDialogueUtils
{
public:
    static void NamedDialoguesAdd(MushcoreData<MushGameDialogue>& outDialogues,
                                  const std::string& inRegExp);
    static void MoveAndRender(MushcoreData<MushGameDialogue>& ioDialogues,
                              MushGameAppHandler& inAppHandler,
                              Mushware::U32 inMoves);
    static void ExpireAll(MushcoreData<MushGameDialogue>& outDialogues);
};

//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
