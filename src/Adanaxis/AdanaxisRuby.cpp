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
 * $Id: AdanaxisRuby.cpp,v 1.2 2006/08/01 17:21:27 southa Exp $
 * $Log: AdanaxisRuby.cpp,v $
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
    
    typedef MushcoreData<MushGamePlayer>::tIterator tIterator;
    MushcoreData<MushGamePlayer>& playerData = SaveData().PlayersWRef();
    for (tIterator p = playerData.Begin(); p != playerData.End(); ++p)
    {
        MushMeshRubyVector::WRef(retVal) = p->second->Post().Pos();
    }
    return retVal;
}    

void
AdanaxisRuby::AdanaxisInstall(void)
{
    MushRubyUtil::SingletonMethodDefineNoParams(Klass(), "cPlayerPosition", PlayerPosition);
}
