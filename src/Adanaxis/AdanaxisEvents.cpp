//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisEvents.cpp
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
//%Header } ADSLqDTcV2OoWVkzmxyavQ
/*
 * $Id$
 * $Log$
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
