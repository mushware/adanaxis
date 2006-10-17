//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameIntern.cpp
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
//%Header } 8fTAEuGpO9TKg8SBLTUQaw
/*
 * $Id: MushGameIntern.cpp,v 1.4 2006/10/17 11:05:55 southa Exp $
 * $Log: MushGameIntern.cpp,v $
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
    m_ATm_piece1 = MushRubyIntern::SymbolID("@m_piece1");
    m_ATm_piece2 = MushRubyIntern::SymbolID("@m_piece2");
    m_ATm_chunkNum1 = MushRubyIntern::SymbolID("@m_chunkNum1");
    m_ATm_chunkNum2 = MushRubyIntern::SymbolID("@m_chunkNum2");
    m_ATm_renderScale = MushRubyIntern::SymbolID("@m_renderScale");
    m_mActionTimer = MushRubyIntern::SymbolID("mActionTimer");
    m_mEventConsume = MushRubyIntern::SymbolID("mEventConsume");
    m_mEventHandle = MushRubyIntern::SymbolID("mEventHandle");
//%initialisations } 3fe70ef9b9740000270cf67524a0a741
}
