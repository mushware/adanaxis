//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisConfig.cpp
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
//%Header } G3+dIgQrIeaNRuZ7DQOVuQ
/*
 * $Id: AdanaxisConfig.cpp,v 1.6 2005/07/06 19:08:26 southa Exp $
 * $Log: AdanaxisConfig.cpp,v $
 * Revision 1.6  2005/07/06 19:08:26  southa
 * Adanaxis control work
 *
 * Revision 1.5  2005/07/02 00:42:36  southa
 * Conditioning tweaks
 *
 * Revision 1.4  2005/06/20 14:30:33  southa
 * Adanaxis work
 *
 * Revision 1.3  2005/06/14 20:39:40  southa
 * Adanaxis work
 *
 * Revision 1.2  2005/06/14 13:25:33  southa
 * Adanaxis work
 *
 * Revision 1.1  2005/06/13 17:34:54  southa
 * Adanaxis creation
 *
 */

#include "AdanaxisConfig.h"

#include "AdanaxisSTL.h"

using namespace Mushware;
using namespace std;

AdanaxisConfig::AdanaxisConfig()
{
    ToDefaultSet();
}

void
AdanaxisConfig::ToDefaultSet(void)
{
    MushGameConfigBase::ToDefaultSet();
    VersionSet(kVersion);
    m_displayMode = 0;
    AxesToDefaultSet();
}

void
AdanaxisConfig::AxesToDefaultSet(void)
{
    m_axisDefs.resize(0);
    
    try
    {
        std::string axisFilename = MushcoreEnv::Sgl().VariableGet("AXISCONFIG_DEFAULT_FILENAME").StringGet();
        
        std::ifstream fileStream(MushcoreUtil::TranslateFilename(axisFilename).c_str());
        if (!fileStream)
        {
            throw MushcoreFileFail(axisFilename, "Could not open file");
        }
        
        MushcoreXMLIStream xmlIn(fileStream);
        xmlIn >> m_axisDefs;
    }
    catch (MushcoreNonFatalFail& e)
    {
        MushcoreLog::Sgl().ErrorLog() << "Failed to load default control axis configuration: " << e.what() << endl;
    }
    
    m_axisDefs.resize(kNumAxes);
}


void
AdanaxisConfig::AutoInputPrologue(MushcoreXMLIStream& ioIn)
{
    MushGameConfigBase::AutoInputPrologue(ioIn);
    VersionSet(kVersion);
    m_displayMode = 0;
    m_axisDefs.resize(0);
}

void
AdanaxisConfig::AutoInputEpilogue(MushcoreXMLIStream& ioIn)
{
    if (m_axisDefs.size() != kNumAxes)
    {
        AxesToDefaultSet();
    }
}

void
AdanaxisConfig::AutoOutputPrologue(MushcoreXMLOStream& ioOut) const
{
    MushGameConfigBase::AutoOutputPrologue(ioOut);
}

//%outOfLineFunctions {

const char *AdanaxisConfig::AutoName(void) const
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
    MushGameConfigBase::AutoPrint(ioOut);
    ioOut << "axisDefs=" << m_axisDefs << ", ";
    ioOut << "displayMode=" << m_displayMode;
    ioOut << "]";
}
bool
AdanaxisConfig::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
    }
    else if (inTagStr == "axisDefs")
    {
        ioIn >> m_axisDefs;
    }
    else if (inTagStr == "displayMode")
    {
        ioIn >> m_displayMode;
    }
    else if (MushGameConfigBase::AutoXMLDataProcess(ioIn, inTagStr))
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
AdanaxisConfig::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    MushGameConfigBase::AutoXMLPrint(ioOut);
    ioOut.TagSet("axisDefs");
    ioOut << m_axisDefs;
    ioOut.TagSet("displayMode");
    ioOut << m_displayMode;
}
//%outOfLineFunctions } iyqNB0Jlf69bXMLIi+y2XA
