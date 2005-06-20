//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisSaveData.cpp
 *
 * Copyright: Andy Southgate 2005
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
//%Header } 2C9hzhWi276zZkbFt6K5Ng
/*
 * $Id: AdanaxisSaveData.cpp,v 1.2 2005/06/16 17:25:37 southa Exp $
 * $Log: AdanaxisSaveData.cpp,v $
 * Revision 1.2  2005/06/16 17:25:37  southa
 * Client/server work
 *
 * Revision 1.1  2005/06/14 20:39:40  southa
 * Adanaxis work
 *
 */

#include "AdanaxisSaveData.h"

//%outOfLineFunctions {

const char *AdanaxisSaveData::AutoName(void) const
{
    return "AdanaxisSaveData";
}

MushcoreVirtualObject *AdanaxisSaveData::AutoClone(void) const
{
    return new AdanaxisSaveData(*this);
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
    ioOut.TagSet("dialogues");
    ioOut << m_dialogues;
}
//%outOfLineFunctions } GQPJU0/4jPhR45JXDZ/ovA
