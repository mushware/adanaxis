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
 * $Id$
 * $Log$
 */

#include "AdanaxisSaveData.h"

MUSHCORE_DATA_INSTANCE(AdanaxisSaveData);

//%outOfLineFunctions {

const char *AdanaxisSaveData::AutoNameGet(void) const
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
    else
    {
        return false;
    }
    return true;
}
void
AdanaxisSaveData::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("dialogues");
    ioOut << m_dialogues;
}
//%outOfLineFunctions } PXj7AAQKh8esD4sM5eYKeA
