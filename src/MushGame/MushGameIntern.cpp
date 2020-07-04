//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameIntern.cpp
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
//%Header } dRVhsu9GieJqPTFJWDIbOQ
/*
 * $Id: MushGameIntern.cpp,v 1.9 2007/03/21 11:56:06 southa Exp $
 * $Log: MushGameIntern.cpp,v $
 * Revision 1.9  2007/03/21 11:56:06  southa
 * Rail effects and damage icons
 *
 * Revision 1.8  2007/03/08 18:38:15  southa
 * Level progression
 *
 * Revision 1.7  2007/03/08 11:00:29  southa
 * Level epilogue
 *
 * Revision 1.6  2006/12/14 15:59:24  southa
 * Fire and cutscene fixes
 *
 * Revision 1.5  2006/10/17 15:28:02  southa
 * Player collisions
 *
 * Revision 1.4  2006/10/17 11:05:55  southa
 * Expiry events
 *
 * Revision 1.3  2006/10/15 17:12:54  southa
 * Scripted explosions
 *
 * Revision 1.2  2006/10/12 22:04:48  southa
 * Collision events
 *
 * Revision 1.1  2006/10/09 16:00:17  southa
 * Intern generation
 *
 */

#include "MushGameIntern.h"

//:process ProcessIntern.rb

MUSHCORE_SINGLETON_INSTANCE(MushGameIntern);

MushGameIntern::MushGameIntern()
{
//%initialisations {
    m_klassMushEventCollision = MushRubyValue(MushRubyUtil::Class("MushEventCollision"));
    m_klassMushEventExpiry = MushRubyValue(MushRubyUtil::Class("MushEventExpiry"));
    m_ATm_alphaStutter = MushRubyIntern::SymbolID("@m_alphaStutter");
    m_ATm_piece1 = MushRubyIntern::SymbolID("@m_piece1");
    m_ATm_piece2 = MushRubyIntern::SymbolID("@m_piece2");
    m_ATm_chunkNum1 = MushRubyIntern::SymbolID("@m_chunkNum1");
    m_ATm_chunkNum2 = MushRubyIntern::SymbolID("@m_chunkNum2");
    m_ATm_collisionPoint = MushRubyIntern::SymbolID("@m_collisionPoint");
    m_ATm_renderScale = MushRubyIntern::SymbolID("@m_renderScale");
    m_mActionTimer = MushRubyIntern::SymbolID("mActionTimer");
    m_mCutSceneKeypress = MushRubyIntern::SymbolID("mCutSceneKeypress");
    m_mEpilogueKeypress = MushRubyIntern::SymbolID("mEpilogueKeypress");
    m_mEpilogueStartDead = MushRubyIntern::SymbolID("mEpilogueStartDead");
    m_mEpilogueStartLost = MushRubyIntern::SymbolID("mEpilogueStartLost");
    m_mEpilogueStartWon = MushRubyIntern::SymbolID("mEpilogueStartWon");
    m_mEventConsume = MushRubyIntern::SymbolID("mEventConsume");
    m_mEventHandle = MushRubyIntern::SymbolID("mEventHandle");
//%initialisations } c10868ae0468ef14379b985d088a8472
}
