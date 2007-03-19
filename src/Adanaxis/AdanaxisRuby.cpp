//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisRuby.cpp
 *
 * Copyright: Andy Southgate 2005-2007
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
//%Header } u23vbNfX5drZiCudCudkVw
/*
 * $Id: AdanaxisRuby.cpp,v 1.9 2007/03/12 21:06:00 southa Exp $
 * $Log: AdanaxisRuby.cpp,v $
 * Revision 1.9  2007/03/12 21:06:00  southa
 * Scanner symbols
 *
 * Revision 1.8  2007/03/09 19:50:12  southa
 * Resident textures
 *
 * Revision 1.7  2007/03/07 11:29:24  southa
 * Level permission
 *
 * Revision 1.6  2006/11/12 20:09:55  southa
 * Missile guidance
 *
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

#include "AdanaxisConfig.h"
#include "AdanaxisRecords.h"
#include "AdanaxisUtil.h"

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

Mushware::tRubyValue
AdanaxisRuby::RecordTime(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0)
{
    MushRubyValue retVal;
    MushRubyValue param0(inArg0);
    
    Mushware::tMsec recordTime = AdanaxisRecords::Sgl().RecordTime(param0.String());
    
    if (recordTime != 0)
    {
        retVal = MushRubyValue(static_cast<U32>(recordTime));
    }
    
    return retVal.Value();
}    

Mushware::tRubyValue
AdanaxisRuby::DamageIconSet(Mushware::tRubyValue inSelf, Mushware::tRubyValue inArg0,
                            Mushware::tRubyValue inArg1)
{
    MushRubyValue param0(inArg0);
    MushRubyValue param1(inArg1);
    
    VolatileData().DamageIconSet(param0.U32(), param1.Val());
    
    return kRubyQnil;
}

void
AdanaxisRuby::AdanaxisInstall(void)
{
    MushRubyUtil::SingletonMethodDefineNoParams(Klass(), "cPlayerPosition", PlayerPosition);
    MushRubyUtil::SingletonMethodDefineNoParams(Klass(), "cPlayerTargetID", PlayerTargetID);
    MushRubyUtil::SingletonMethodDefineOneParam(Klass(), "cRecordTime", RecordTime);
    MushRubyUtil::SingletonMethodDefineTwoParams(Klass(), "cDamageIconSet", DamageIconSet);
}
