//%Header {
/*****************************************************************************
 *
 * File: src/Adanaxis/AdanaxisConfig.cpp
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
//%Header } Vjkzrv0A3x9QC18VN1bMwA
/*
 * $Id: AdanaxisConfig.cpp,v 1.25 2007/06/11 20:06:14 southa Exp $
 * $Log: AdanaxisConfig.cpp,v $
 * Revision 1.25  2007/06/11 20:06:14  southa
 * Compatibility fixes and level 27
 *
 * Revision 1.24  2007/04/18 09:22:00  southa
 * Header and level fixes
 *
 * Revision 1.23  2007/04/16 08:41:07  southa
 * Level and header mods
 *
 * Revision 1.22  2007/03/20 17:31:23  southa
 * Difficulty and GL options
 *
 * Revision 1.21  2007/03/12 21:05:59  southa
 * Scanner symbols
 *
 * Revision 1.20  2007/03/09 19:50:11  southa
 * Resident textures
 *
 * Revision 1.19  2007/03/07 11:29:24  southa
 * Level permission
 *
 * Revision 1.18  2006/11/25 21:26:31  southa
 * Display mode definitions
 *
 * Revision 1.17  2006/08/01 17:21:22  southa
 * River demo
 *
 * Revision 1.16  2006/07/28 11:14:26  southa
 * Records for multiple spaces
 *
 * Revision 1.15  2006/07/26 16:37:20  southa
 * Options menu
 *
 * Revision 1.14  2006/07/11 12:37:51  southa
 * Control configuration
 *
 * Revision 1.13  2006/06/01 15:38:46  southa
 * DrawArray verification and fixes
 *
 * Revision 1.12  2005/08/02 17:11:28  southa
 * win32 build fixes
 *
 * Revision 1.11  2005/08/02 14:37:44  southa
 * Adanaxis control demo work
 *
 * Revision 1.10  2005/08/02 11:11:47  southa
 * Adanaxis control demo work
 *
 * Revision 1.9  2005/07/30 19:06:14  southa
 * Collision checking
 *
 * Revision 1.8  2005/07/11 16:37:45  southa
 * Uplink control work
 *
 * Revision 1.7  2005/07/07 16:54:17  southa
 * Control tweaks
 *
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

#include "API/mushPlatform.h"

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
    m_modeDef = GLModeDef(kDisplayXSize, kDisplayYSize, true);
    AxesToDefaultSet();
    KeysToDefaultSet();
    m_configDifficulty = 1;
    m_useGLCompression = 1;
    m_useGLShader = 1;
}

void
AdanaxisConfig::AxesToDefaultSet(void)
{
    m_axisDefs.resize(0);
    
    try
    {
        std::string axisFilename = MushcoreEnv::Sgl().VariableGet("ADANAXIS_AXISCONFIG_DEFAULT_FILENAME").StringGet();
        
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
    
    if (m_axisDefs.size() < kNumAxes)
    {
        m_axisDefs.resize(kNumAxes);
    }
}

void
AdanaxisConfig::KeysToDefaultSet(void)
{
    m_keyDefs.resize(0);
    
    try
    {
        std::string keysFilename = MushcoreEnv::Sgl().VariableGet("ADANAXIS_KEYCONFIG_DEFAULT_FILENAME").StringGet();
        
        std::ifstream fileStream(MushcoreUtil::TranslateFilename(keysFilename).c_str());
        if (!fileStream)
        {
            throw MushcoreFileFail(keysFilename, "Could not open file");
        }
        
        MushcoreXMLIStream xmlIn(fileStream);
        xmlIn >> m_keyDefs;
    }
    catch (MushcoreNonFatalFail& e)
    {
        MushcoreLog::Sgl().ErrorLog() << "Failed to load default control key configuration: " << e.what() << endl;
    }
    
    if (m_keyDefs.size() < kNumKeys)
    {
        m_keyDefs.resize(kNumKeys);
    }
}


void
AdanaxisConfig::AutoInputPrologue(MushcoreXMLIStream& ioIn)
{
    MushGameConfigBase::AutoInputPrologue(ioIn);
    VersionSet(kVersion);
    m_modeDef = GLModeDef(kDisplayXSize, kDisplayYSize, true);
    m_axisDefs.resize(0);
    m_keyDefs.resize(0);
}

void
AdanaxisConfig::AutoInputEpilogue(MushcoreXMLIStream& ioIn)
{
    if (m_axisDefs.size() < kNumAxes)
    {
        AxesToDefaultSet();
    }
    if (m_keyDefs.size() < kNumKeys)
    {
        KeysToDefaultSet();
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
    ioOut << "keyDefs=" << m_keyDefs << ", ";
    ioOut << "modeDef=" << m_modeDef << ", ";
    ioOut << "configDifficulty=" << m_configDifficulty << ", ";
    ioOut << "useGLCompression=" << m_useGLCompression << ", ";
    ioOut << "useGLShader=" << m_useGLShader;
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
    else if (inTagStr == "keyDefs")
    {
        ioIn >> m_keyDefs;
    }
    else if (inTagStr == "modeDef")
    {
        ioIn >> m_modeDef;
    }
    else if (inTagStr == "configDifficulty")
    {
        ioIn >> m_configDifficulty;
    }
    else if (inTagStr == "useGLCompression")
    {
        ioIn >> m_useGLCompression;
    }
    else if (inTagStr == "useGLShader")
    {
        ioIn >> m_useGLShader;
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
    ioOut.TagSet("keyDefs");
    ioOut << m_keyDefs;
    ioOut.TagSet("modeDef");
    ioOut << m_modeDef;
    ioOut.TagSet("configDifficulty");
    ioOut << m_configDifficulty;
    ioOut.TagSet("useGLCompression");
    ioOut << m_useGLCompression;
    ioOut.TagSet("useGLShader");
    ioOut << m_useGLShader;
}
//%outOfLineFunctions } ZjUgfZDxs1gUaSH6BJy7ew
