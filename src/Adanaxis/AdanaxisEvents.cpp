//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisEvents.cpp
 *
 * Copyright: Andy Southgate 2005-2007
 *
 * This file may be used and distributed under the terms of the Mushware
 * Software Licence version 1.3, under the terms for 'Proprietary original
 * source files'.  If not supplied with this software, a copy of the licence
 * can be obtained from Mushware Limited via http://www.mushware.com/.
 * One of your options under that licence is to use and distribute this file
 * under the terms of the GNU General Public Licence version 2.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } WLaQYnV5gRWh/bO36m6jEw
/*
 * $Id: AdanaxisEvents.cpp,v 1.2 2006/11/03 18:46:32 southa Exp $
 * $Log: AdanaxisEvents.cpp,v $
 * Revision 1.2  2006/11/03 18:46:32  southa
 * Damage effectors
 *
 * Revision 1.1  2006/11/02 09:47:33  southa
 * Player weapon control
 *
 */

#include "AdanaxisEvents.h"

#include "AdanaxisIntern.h"

#include "API/mushMushMeshRuby.h"

MUSHCORE_SINGLETON_INSTANCE(AdanaxisEvents);

using namespace Mushware;
using namespace std;

MushRubyValue
AdanaxisEvents::EventFireMake(const MushMeshPosticity& inPost)
{
    MushRubyValue retVal( MushRubyUtil::ClassNewInstance(AdanaxisIntern::Sgl().AdanaxisEventFire()) );
    
    {
        tRubyValue value = MushRubyUtil::InstanceVar(retVal.Value(), MushRubyIntern::ATm_post());
        if (value == kRubyQnil)
        {
            throw MushcoreDataFail("No attribute @m_post in EventFireMake");
        }
        MushMeshRubyPost::WRef(value) = inPost;
    }
    
    return retVal;
}

MushRubyValue
AdanaxisEvents::EventKeyStateMake(void)
{
    MushRubyValue retVal( MushRubyUtil::ClassNewInstance(AdanaxisIntern::Sgl().AdanaxisEventKeyState()) );
    return retVal;
}    

void
AdanaxisEvents::EventKeyStateAddState(MushRubyValue& ioEvent, Mushware::U32 inNum, bool inState)
{
    MushRubyValue keyNum( MushRubyUtil::InstanceVar(ioEvent.Value(), AdanaxisIntern::Sgl().ATm_keyNum()) );
    MushRubyUtil::ArrayPush(keyNum, MushRubyValue(inNum));
    MushRubyValue state( MushRubyUtil::InstanceVar(ioEvent.Value(), AdanaxisIntern::Sgl().ATm_state()) );
    MushRubyUtil::ArrayPush(state, MushRubyValue(inState));
}

//%outOfLineFunctions {

const char *AdanaxisEvents::AutoName(void) const
{
    return "AdanaxisEvents";
}

MushcoreVirtualObject *AdanaxisEvents::AutoClone(void) const
{
    return new AdanaxisEvents(*this);
}

MushcoreVirtualObject *AdanaxisEvents::AutoCreate(void) const
{
    return new AdanaxisEvents;
}

MushcoreVirtualObject *AdanaxisEvents::AutoVirtualFactory(void)
{
    return new AdanaxisEvents;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("AdanaxisEvents", AdanaxisEvents::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
AdanaxisEvents::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "]";
}
bool
AdanaxisEvents::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else 
    {
        return false;
    }
    return true;
}
void
AdanaxisEvents::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
}
//%outOfLineFunctions } XtjvCuPkXj2ZvlO3AvBPFQ
