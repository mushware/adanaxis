//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisRuby.cpp
 *
 * Copyright: Andy Southgate 2005-2006
 *
 * This file may be used and distributed under the terms of the Mushware
 * software licence version 1.1, under the terms for 'Proprietary original
 * source files'.  If not supplied with this software, a copy of the licence
 * can be obtained from Mushware Limited via http://www.mushware.com/.
 * One of your options under that licence is to use and distribute this file
 * under the terms of the GNU General Public Licence version 2.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } nD/Irg6+j8tkN0uh3Wk1EQ
/*
 * $Id: AdanaxisRuby.cpp,v 1.5 2006/10/17 15:28:02 southa Exp $
 * $Log: AdanaxisRuby.cpp,v $
 * Revision 1.5  2006/10/17 15:28:02  southa
 * Player collisions
 *
 * Revision 1.4  2006/10/02 17:25:04  southa
 * Object lookup and target selection
 *
 * Revision 1.3  2006/08/20 14:19:20  southa
 * Seek operation
 *
 * Revision 1.2  2006/08/01 17:21:27  southa
 * River demo
 *
 * Revision 1.1  2006/06/21 12:17:56  southa
 * Ruby object generation
 *
 */

#include "AdanaxisRuby.h"

#include "API/mushMushMeshRuby.h"

MUSHRUBYEMPTYOBJ_INSTANCE(2000);

MUSHRUBY_INSTALL(AdanaxisRuby);

using namespace Mushware;
using namespace std;

MushcoreDataRef<MushGameLogic> AdanaxisRuby::s_logicRef;

Mushware::tRubyValue
AdanaxisRuby::PlayerPosition(Mushware::tRubyValue inSelf)
{
    tRubyValue retVal = MushMeshRubyVector::NewInstance();
    
    typedef MushcoreMaptor<MushGamePiecePlayer>::iterator tIterator;
    MushcoreMaptor<MushGamePiecePlayer>& playerData = SaveData().PlayersListWRef();
    for (tIterator p = playerData.begin(); p != playerData.end(); ++p)
    {
        MushMeshRubyVector::WRef(retVal) = p->Post().Pos();
    }
    return retVal;
}    

Mushware::tRubyValue
AdanaxisRuby::PlayerTargetID(Mushware::tRubyValue inSelf)
{
    return MushRubyValue(VolatileData().PlayerTargetID()).Value();
}    

void
AdanaxisRuby::AdanaxisInstall(void)
{
    MushRubyUtil::SingletonMethodDefineNoParams(Klass(), "cPlayerPosition", PlayerPosition);
    MushRubyUtil::SingletonMethodDefineNoParams(Klass(), "cPlayerTargetID", PlayerTargetID);
}
