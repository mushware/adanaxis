//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisSaveData.cpp
 *
 * Copyright: Andy Southgate 2005-2006
 *
 * This file may be used and distributed under the terms of the Mushware
 * software licence version 1.0, under the terms for 'Proprietary original
 * source files'.  If not supplied with this software, a copy of the licence
 * can be obtained from Mushware Limited via http://www.mushware.com/.
 * One of your options under that licence is to use and distribute this file
 * under the terms of the GNU General Public Licence version 2.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } 157b9FcuQDovkVcDTGUZJw
/*
 * $Id: AdanaxisSaveData.cpp,v 1.9 2005/07/29 14:59:49 southa Exp $
 * $Log: AdanaxisSaveData.cpp,v $
 * Revision 1.9  2005/07/29 14:59:49  southa
 * Maptor access
 *
 * Revision 1.8  2005/07/29 08:27:47  southa
 * Collision work
 *
 * Revision 1.7  2005/07/12 12:18:17  southa
 * Projectile work
 *
 * Revision 1.6  2005/07/02 00:42:36  southa
 * Conditioning tweaks
 *
 * Revision 1.5  2005/06/30 14:26:35  southa
 * Adanaxis work
 *
 * Revision 1.4  2005/06/29 11:11:15  southa
 * Camera and rendering work
 *
 * Revision 1.3  2005/06/20 14:30:33  southa
 * Adanaxis work
 *
 * Revision 1.2  2005/06/16 17:25:37  southa
 * Client/server work
 *
 * Revision 1.1  2005/06/14 20:39:40  southa
 * Adanaxis work
 *
 */

#include "AdanaxisSaveData.h"

AdanaxisSaveData::AdanaxisSaveData()
{
}

//%outOfLineFunctions {

const char *AdanaxisSaveData::AutoName(void) const
{
    return "AdanaxisSaveData";
}

MushcoreVirtualObject *AdanaxisSaveData::AutoClone(void) const
{
    throw MushcoreRequestFail("Cannot clone 'AdanaxisSaveData'");;
}

MushcoreVirtualObject *AdanaxisSaveData::AutoCreate(void) const
{
    return new AdanaxisSaveData;
}

MushcoreVirtualObject *AdanaxisSaveData::AutoVirtualFactory(void)
{
    return new AdanaxisSaveData;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("AdanaxisSaveData", AdanaxisSaveData::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
AdanaxisSaveData::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushGameSaveData::AutoPrint(ioOut);
    ioOut << "projectileList=" << m_projectileList << ", ";
    ioOut << "khaziList=" << m_khaziList << ", ";
    ioOut << "dialogues=" << m_dialogues;
    ioOut << "]";
}
bool
AdanaxisSaveData::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "projectileList")
    {
        ioIn >> m_projectileList;
    }
    else if (inTagStr == "khaziList")
    {
        ioIn >> m_khaziList;
    }
    else if (inTagStr == "dialogues")
    {
        ioIn >> m_dialogues;
    }
    else if (MushGameSaveData::AutoXMLDataProcess(ioIn, inTagStr))
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
AdanaxisSaveData::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushGameSaveData::AutoXMLPrint(ioOut);
    ioOut.TagSet("projectileList");
    ioOut << m_projectileList;
    ioOut.TagSet("khaziList");
    ioOut << m_khaziList;
    ioOut.TagSet("dialogues");
    ioOut << m_dialogues;
}
//%outOfLineFunctions } I1umnKaoHF4d6RhVXZcmtQ
