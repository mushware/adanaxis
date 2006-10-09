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
 * $Id$
 * $Log$
 */

#include "MushGameStandard.h"

//:process ProcessIntern.rb
/*
:data1begin
 ids = %w{
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
    Mushware::tRubyValue MushEventCollision(void) { return m_klassMushEventCollision; }
private:
    Mushware::tRubyValue m_klassMushEventCollision;
//%declarations } 89014877e9776b890acea928a1035564
//%classPrototypes {
public:
//%classPrototypes } 0ImSRh0/JBpOMwe5g8vGcA
};
//%includeGuardEnd {
#endif
//%includeGuardEnd } hNb4yLSsimk5RFvFdUzHEw
