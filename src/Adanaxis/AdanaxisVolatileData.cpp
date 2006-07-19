//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisVolatileData.cpp
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
//%Header } WOK6bg7pMfVL2uBwMmEFBQ
/*
 * $Id: AdanaxisVolatileData.cpp,v 1.6 2006/07/04 16:55:26 southa Exp $
 * $Log: AdanaxisVolatileData.cpp,v $
 * Revision 1.6  2006/07/04 16:55:26  southa
 * Ruby key handling
 *
 * Revision 1.5  2006/07/02 21:08:54  southa
 * Ruby menu work
 *
 */

#include "AdanaxisVolatileData.h"

AdanaxisVolatileData::AdanaxisVolatileData() :
    m_modeKeypressMsec(0),
    m_newMode(0),
    m_rubySpace(Mushware::kRubyQnil)
{
}

//%outOfLineFunctions {

const char *AdanaxisVolatileData::AutoName(void) const
{
    return "AdanaxisVolatileData";
}

MushcoreVirtualObject *AdanaxisVolatileData::AutoClone(void) const
{
    throw MushcoreRequestFail("Cannot clone 'AdanaxisVolatileData'");;
}

MushcoreVirtualObject *AdanaxisVolatileData::AutoCreate(void) const
{
    return new AdanaxisVolatileData;
}

MushcoreVirtualObject *AdanaxisVolatileData::AutoVirtualFactory(void)
{
    return new AdanaxisVolatileData;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("AdanaxisVolatileData", AdanaxisVolatileData::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
AdanaxisVolatileData::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushGameVolatileData::AutoPrint(ioOut);
    ioOut << "decoList=" << m_decoList << ", ";
    ioOut << "worldList=" << m_worldList << ", ";
    ioOut << "modeKeypressMsec=" << m_modeKeypressMsec << ", ";
    ioOut << "newMode=" << m_newMode << ", ";
    ioOut << "aRenderMesh=" << m_aRenderMesh << ", ";
    ioOut << "rubySpace=" << m_rubySpace;
    ioOut << "]";
}
bool
AdanaxisVolatileData::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "decoList")
    {
        ioIn >> m_decoList;
    }
    else if (inTagStr == "worldList")
    {
        ioIn >> m_worldList;
    }
    else if (inTagStr == "modeKeypressMsec")
    {
        ioIn >> m_modeKeypressMsec;
    }
    else if (inTagStr == "newMode")
    {
        ioIn >> m_newMode;
    }
    else if (inTagStr == "aRenderMesh")
    {
        ioIn >> m_aRenderMesh;
    }
    else if (inTagStr == "rubySpace")
    {
        ioIn >> m_rubySpace;
    }
    else if (MushGameVolatileData::AutoXMLDataProcess(ioIn, inTagStr))
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
AdanaxisVolatileData::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushGameVolatileData::AutoXMLPrint(ioOut);
    ioOut.TagSet("decoList");
    ioOut << m_decoList;
    ioOut.TagSet("worldList");
    ioOut << m_worldList;
    ioOut.TagSet("modeKeypressMsec");
    ioOut << m_modeKeypressMsec;
    ioOut.TagSet("newMode");
    ioOut << m_newMode;
    ioOut.TagSet("aRenderMesh");
    ioOut << m_aRenderMesh;
    ioOut.TagSet("rubySpace");
    ioOut << m_rubySpace;
}
//%outOfLineFunctions } Wujqs/kdpX0HgH56mAHUkQ
