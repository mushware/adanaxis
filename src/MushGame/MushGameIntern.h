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
 * $Id: MushGameIntern.h,v 1.1 2006/10/09 16:00:17 southa Exp $
 * $Log: MushGameIntern.h,v $
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
 }
 classes = %w{
     MushEventCollision
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
    Mushware::tRubyID ATm_piece1(void) { return m_ATm_piece1; }
    Mushware::tRubyID ATm_piece2(void) { return m_ATm_piece2; }
    Mushware::tRubyID ATm_chunkNum1(void) { return m_ATm_chunkNum1; }
    Mushware::tRubyID ATm_chunkNum2(void) { return m_ATm_chunkNum2; }
private:
    MushRubyValue m_klassMushEventCollision;
    Mushware::tRubyID m_ATm_piece1;
    Mushware::tRubyID m_ATm_piece2;
    Mushware::tRubyID m_ATm_chunkNum1;
    Mushware::tRubyID m_ATm_chunkNum2;
//%declarations } 11e60ae1a822cef6ce5199b23d7032cd
//%classPrototypes {
public:
//%classPrototypes } 0ImSRh0/JBpOMwe5g8vGcA
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
