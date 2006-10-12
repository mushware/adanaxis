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
 * $Id: MushGameIntern.cpp,v 1.1 2006/10/09 16:00:17 southa Exp $
 * $Log: MushGameIntern.cpp,v $
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
    m_ATm_piece1 = MushRubyIntern::SymbolID("@m_piece1");
    m_ATm_piece2 = MushRubyIntern::SymbolID("@m_piece2");
    m_ATm_chunkNum1 = MushRubyIntern::SymbolID("@m_chunkNum1");
    m_ATm_chunkNum2 = MushRubyIntern::SymbolID("@m_chunkNum2");
//%initialisations } 0635fbe9216a0e71ab725f8c642e7bce
}
