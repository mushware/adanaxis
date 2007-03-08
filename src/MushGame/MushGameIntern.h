//%includeGuardStart {
#ifndef MUSHGAMEINTERN_H
#define MUSHGAMEINTERN_H
//%includeGuardStart } bYgGLvtVPKy5PNyhngZPBw
//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameIntern.h
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
//%Header } mlN3NFYShD8lw+CPV54eBg
/*
 * $Id: MushGameIntern.h,v 1.7 2007/03/08 11:00:30 southa Exp $
 * $Log: MushGameIntern.h,v $
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
     @m_piece1
     @m_piece2
     @m_chunkNum1
     @m_chunkNum2
     @m_renderScale
     mActionTimer
     mCutSceneKeypress
     mEpilogueKeypress
     mEpilogueStartDead
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
    Mushware::tRubyID ATm_piece1(void) { return m_ATm_piece1; }
    Mushware::tRubyID ATm_piece2(void) { return m_ATm_piece2; }
    Mushware::tRubyID ATm_chunkNum1(void) { return m_ATm_chunkNum1; }
    Mushware::tRubyID ATm_chunkNum2(void) { return m_ATm_chunkNum2; }
    Mushware::tRubyID ATm_renderScale(void) { return m_ATm_renderScale; }
    Mushware::tRubyID mActionTimer(void) { return m_mActionTimer; }
    Mushware::tRubyID mCutSceneKeypress(void) { return m_mCutSceneKeypress; }
    Mushware::tRubyID mEpilogueKeypress(void) { return m_mEpilogueKeypress; }
    Mushware::tRubyID mEpilogueStartDead(void) { return m_mEpilogueStartDead; }
    Mushware::tRubyID mEpilogueStartWon(void) { return m_mEpilogueStartWon; }
    Mushware::tRubyID mEventConsume(void) { return m_mEventConsume; }
    Mushware::tRubyID mEventHandle(void) { return m_mEventHandle; }
private:
    MushRubyValue m_klassMushEventCollision;
    MushRubyValue m_klassMushEventExpiry;
    Mushware::tRubyID m_ATm_piece1;
    Mushware::tRubyID m_ATm_piece2;
    Mushware::tRubyID m_ATm_chunkNum1;
    Mushware::tRubyID m_ATm_chunkNum2;
    Mushware::tRubyID m_ATm_renderScale;
    Mushware::tRubyID m_mActionTimer;
    Mushware::tRubyID m_mCutSceneKeypress;
    Mushware::tRubyID m_mEpilogueKeypress;
    Mushware::tRubyID m_mEpilogueStartDead;
    Mushware::tRubyID m_mEpilogueStartWon;
    Mushware::tRubyID m_mEventConsume;
    Mushware::tRubyID m_mEventHandle;
//%declarations } 4785328cf9bf433a6a8d515bc2580892
//%classPrototypes {
public:
//%classPrototypes } 0ImSRh0/JBpOMwe5g8vGcA
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
