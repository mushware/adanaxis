//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisData.cpp
 *
 * Copyright: Andy Southgate 2005-2007
 *
 * This file may be used and distributed under the terms of the Mushware
 * Software Licence version 1.4, under the terms for 'Proprietary original
 * source files'.  If not supplied with this software, a copy of the licence
 * can be obtained from Mushware Limited via http://www.mushware.com/.
 * One of your options under that licence is to use and distribute this file
 * under the terms of the GNU General Public Licence version 2.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } uN2YWp7tcg5Mo6s1B4sBMQ
/*
 * $Id: AdanaxisData.cpp,v 1.6 2007/04/18 09:22:00 southa Exp $
 * $Log: AdanaxisData.cpp,v $
 * Revision 1.6  2007/04/18 09:22:00  southa
 * Header and level fixes
 *
 * Revision 1.5  2007/04/16 08:41:07  southa
 * Level and header mods
 *
 * Revision 1.4  2007/03/16 19:50:44  southa
 * Damage indicators
 *
 * Revision 1.3  2006/08/01 17:21:23  southa
 * River demo
 *
 * Revision 1.2  2006/06/01 15:38:47  southa
 * DrawArray verification and fixes
 *
 * Revision 1.1  2005/08/01 13:09:57  southa
 * Collision messaging
 *
 */

#include "AdanaxisData.h"

AdanaxisData::AdanaxisData(const std::string& inName) :
    MushGameData(inName)
{
}
//%outOfLineFunctions {

const char *AdanaxisData::AutoName(void) const
{
    return "AdanaxisData";
}

MushcoreVirtualObject *AdanaxisData::AutoClone(void) const
{
    return new AdanaxisData(*this);
}

MushcoreVirtualObject *AdanaxisData::AutoCreate(void) const
{
    return new AdanaxisData;
}

MushcoreVirtualObject *AdanaxisData::AutoVirtualFactory(void)
{
    return new AdanaxisData;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("AdanaxisData", AdanaxisData::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
AdanaxisData::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushGameData::AutoPrint(ioOut);
    ioOut << "]";
}
bool
AdanaxisData::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (MushGameData::AutoXMLDataProcess(ioIn, inTagStr))
    {
        // Tag consumed by base class
    }
    else 
    {
        return false;
    }
    return true;
}
void
AdanaxisData::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushGameData::AutoXMLPrint(ioOut);
}
//%outOfLineFunctions } 03vLNy6OhwIL6GKqF4s06w
