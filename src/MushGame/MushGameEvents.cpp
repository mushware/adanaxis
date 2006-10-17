//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameEvents.cpp
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
//%Header } D13ZnwKD9ZTm4dMvEpIY4g
/*
 * $Id$
 * $Log$
 */

#include "MushGameEvents.h"

#include "MushGameIntern.h"

MUSHCORE_SINGLETON_INSTANCE(MushGameEvents);

using namespace Mushware;
using namespace std;

MushRubyValue
MushGameEvents::EventExpiryMake(void)
{
    MushRubyValue retVal( MushRubyUtil::ClassNewInstance(MushGameIntern::Sgl().MushEventExpiry()) );
    
    return retVal;
}
//%outOfLineFunctions {

const char *MushGameEvents::AutoName(void) const
{
    return "MushGameEvents";
}

MushcoreVirtualObject *MushGameEvents::AutoClone(void) const
{
    return new MushGameEvents(*this);
}

MushcoreVirtualObject *MushGameEvents::AutoCreate(void) const
{
    return new MushGameEvents;
}

MushcoreVirtualObject *MushGameEvents::AutoVirtualFactory(void)
{
    return new MushGameEvents;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGameEvents", MushGameEvents::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGameEvents::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "]";
}
bool
MushGameEvents::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
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
MushGameEvents::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
}
//%outOfLineFunctions } cdnbnKCheY/ZFXSPd87odg
