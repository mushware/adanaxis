//%Header {
/*****************************************************************************
 *
 * File: src/MushGame/MushGameMessageControlInfo.cpp
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
//%Header } kjtpGq3pCUzxXKu2JQ/iFw
/*
 * $Id: MushGameMessageControlInfo.cpp,v 1.1 2005/07/06 19:08:27 southa Exp $
 * $Log: MushGameMessageControlInfo.cpp,v $
 * Revision 1.1  2005/07/06 19:08:27  southa
 * Adanaxis control work
 *
 */

#include "MushGameMessageControlInfo.h"
//%outOfLineFunctions {

const char *MushGameMessageControlInfo::AutoName(void) const
{
    return "MushGameMessageControlInfo";
}

MushcoreVirtualObject *MushGameMessageControlInfo::AutoClone(void) const
{
    return new MushGameMessageControlInfo(*this);
}

MushcoreVirtualObject *MushGameMessageControlInfo::AutoCreate(void) const
{
    return new MushGameMessageControlInfo;
}

MushcoreVirtualObject *MushGameMessageControlInfo::AutoVirtualFactory(void)
{
    return new MushGameMessageControlInfo;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("MushGameMessageControlInfo", MushGameMessageControlInfo::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
MushGameMessageControlInfo::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    MushGameMessage::AutoPrint(ioOut);
    ioOut << "timestamp=" << m_timestamp << ", ";
    ioOut << "axisEvents=" << m_axisEvents << ", ";
    ioOut << "keyEvents=" << m_keyEvents;
    ioOut << "]";
}
bool
MushGameMessageControlInfo::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "timestamp")
    {
        ioIn >> m_timestamp;
    }
    else if (inTagStr == "axisEvents")
    {
        ioIn >> m_axisEvents;
    }
    else if (inTagStr == "keyEvents")
    {
        ioIn >> m_keyEvents;
    }
    else if (MushGameMessage::AutoXMLDataProcess(ioIn, inTagStr))
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
MushGameMessageControlInfo::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushGameMessage::AutoXMLPrint(ioOut);
    ioOut.TagSet("timestamp");
    ioOut << m_timestamp;
    ioOut.TagSet("axisEvents");
    ioOut << m_axisEvents;
    ioOut.TagSet("keyEvents");
    ioOut << m_keyEvents;
}
//%outOfLineFunctions } 2pzNQJVGzbzqSBE8BGC1KA
