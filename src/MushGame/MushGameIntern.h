//%includeGuardStart {
#ifndef MUSHGAMEINTERN_H
#define MUSHGAMEINTERN_H
//%includeGuardStart } bYgGLvtVPKy5PNyhngZPBw
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameIntern.h
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
//%Header } 0ByZ6R005+SK87V/vEjy5w
/*
 * $Id: MushGameIntern.h,v 1.9 2007/03/21 11:56:06 southa Exp $
 * $Log: MushGameIntern.h,v $
 * Revision 1.9  2007/03/21 11:56:06  southa
 * Rail effects and damage icons
 *
 * Revision 1.8  2007/03/08 18:38:15  southa
 * Level progression
 *
 * Revision 1.7  2007/03/08 11:00:30  southa
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

#include "MushGameStandard.h"

//:process ProcessIntern.rb
/*
:data1begin
 ids = %w{
     @m_alphaStutter
     @m_piece1
     @m_piece2
     @m_chunkNum1
     @m_chunkNum2
     @m_collisionPoint
     @m_renderScale
     mActionTimer
     mCutSceneKeypress
     mEpilogueKeypress
     mEpilogueStartDead
     mEpilogueStartLost
     mEpilogueStartWon
     mEventConsume
     mEventHandle
 }
 classes = %w{
     MushEventCollision
     MushEventExpiry
 }
:data1end
*/
class MushGameIntern : public MushcoreSingleton<MushGameIntern>
{
public:
    MushGameIntern();
//%declarations {
public:
    MushRubyValue& MushEventCollision(void) { return m_klassMushEventCollision; }
    MushRubyValue& MushEventExpiry(void) { return m_klassMushEventExpiry; }
    Mushware::tRubyID ATm_alphaStutter(void) { return m_ATm_alphaStutter; }
    Mushware::tRubyID ATm_piece1(void) { return m_ATm_piece1; }
    Mushware::tRubyID ATm_piece2(void) { return m_ATm_piece2; }
    Mushware::tRubyID ATm_chunkNum1(void) { return m_ATm_chunkNum1; }
    Mushware::tRubyID ATm_chunkNum2(void) { return m_ATm_chunkNum2; }
    Mushware::tRubyID ATm_collisionPoint(void) { return m_ATm_collisionPoint; }
    Mushware::tRubyID ATm_renderScale(void) { return m_ATm_renderScale; }
    Mushware::tRubyID mActionTimer(void) { return m_mActionTimer; }
    Mushware::tRubyID mCutSceneKeypress(void) { return m_mCutSceneKeypress; }
    Mushware::tRubyID mEpilogueKeypress(void) { return m_mEpilogueKeypress; }
    Mushware::tRubyID mEpilogueStartDead(void) { return m_mEpilogueStartDead; }
    Mushware::tRubyID mEpilogueStartLost(void) { return m_mEpilogueStartLost; }
    Mushware::tRubyID mEpilogueStartWon(void) { return m_mEpilogueStartWon; }
    Mushware::tRubyID mEventConsume(void) { return m_mEventConsume; }
    Mushware::tRubyID mEventHandle(void) { return m_mEventHandle; }
private:
    MushRubyValue m_klassMushEventCollision;
    MushRubyValue m_klassMushEventExpiry;
    Mushware::tRubyID m_ATm_alphaStutter;
    Mushware::tRubyID m_ATm_piece1;
    Mushware::tRubyID m_ATm_piece2;
    Mushware::tRubyID m_ATm_chunkNum1;
    Mushware::tRubyID m_ATm_chunkNum2;
    Mushware::tRubyID m_ATm_collisionPoint;
    Mushware::tRubyID m_ATm_renderScale;
    Mushware::tRubyID m_mActionTimer;
    Mushware::tRubyID m_mCutSceneKeypress;
    Mushware::tRubyID m_mEpilogueKeypress;
    Mushware::tRubyID m_mEpilogueStartDead;
    Mushware::tRubyID m_mEpilogueStartLost;
    Mushware::tRubyID m_mEpilogueStartWon;
    Mushware::tRubyID m_mEventConsume;
    Mushware::tRubyID m_mEventHandle;
//%declarations } 001f11739b95ec0bd280144f65d24b6d
//%classPrototypes {
public:
//%classPrototypes } 0ImSRh0/JBpOMwe5g8vGcA
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
