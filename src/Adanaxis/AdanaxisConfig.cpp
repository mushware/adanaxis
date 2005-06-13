//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisConfig.cpp
 *
 * Author: Andy Southgate 2002-2005
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
//%Header } n2nSue7N6TZsnR51N1Ujlw
/*
 * $Id: AdanaxisConfig.cpp,v 1.5 2005/05/26 00:46:41 southa Exp $
 * $Log: AdanaxisConfig.cpp,v $
 */

#include "AdanaxisConfig.h"

#include "AdanaxisSTL.h"

AdanaxisConfig::AdanaxisConfig() :
    m_version(1)
{
}

//%outOfLineFunctions {

const char *AdanaxisConfig::AutoNameGet(void) const
{
    return "AdanaxisConfig";
}

MushcoreVirtualObject *AdanaxisConfig::AutoClone(void) const
{
    return new AdanaxisConfig(*this);
}

MushcoreVirtualObject *AdanaxisConfig::AutoCreate(void) const
{
    return new AdanaxisConfig;
}

MushcoreVirtualObject *AdanaxisConfig::AutoVirtualFactory(void)
{
    return new AdanaxisConfig;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("AdanaxisConfig", AdanaxisConfig::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
AdanaxisConfig::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "version=" << m_version << ", ";
    ioOut << "displayMode=" << m_displayMode;
    ioOut << "]";
}
bool
AdanaxisConfig::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        ioIn >> *this;
    }
    else if (inTagStr == "version")
    {
        ioIn >> m_version;
    }
    else if (inTagStr == "displayMode")
    {
        ioIn >> m_displayMode;
    }
    else
    {
        return false;
    }
    return true;
}
void
AdanaxisConfig::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("version");
    ioOut << m_version;
    ioOut.TagSet("displayMode");
    ioOut << m_displayMode;
}
//%outOfLineFunctions } XuVb+LiWR8yD7TZLA/pxVQ
