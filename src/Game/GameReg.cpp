//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameReg.cpp
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com/.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002-2004.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/
//%Header } uWbfm7fd07cmTliM1Hqs3g
/*
 * $Id: GameReg.cpp,v 1.1 2005/04/10 00:09:22 southa Exp $
 * $Log: GameReg.cpp,v $
 * Revision 1.1  2005/04/10 00:09:22  southa
 * Registration
 *
 */

#include "GameReg.h"


#include "GameAppHandler.h"
#include "GameSTL.h"
#include "GameUtils.h"

#include "mushGL.h"
#include "mushPlatform.h"


using namespace Mushware;
using namespace std;

GameReg::GameReg() :
    m_regURL("http://www.mushware.com/"),
    m_regCodeLength(12),
    m_codeValid(kCodeValidUnknown),
    m_lastCheckMsec(0)
{
}

void
GameReg::Process(GameAppHandler& inAppHandler)
{
    if (inAppHandler.LatchedKeyStateTake(GLKeys::kKeyMouse1))
    {
        try
        {
            PlatformMiscUtils::LaunchURL(m_regURL);
        }
        catch (MushcoreNonFatalFail& e)
        {

            PlatformMiscUtils::MinorErrorBox("Failed to open URL '"+m_regURL+"'.  Please open in your browser.");
        }
    }
    
    for (char i = '0'; i <= '9'; ++i)
    {
        if (inAppHandler.LatchedKeyStateTake(i))
        {
            if (m_regCode.length() < m_regCodeLength)
            {
                m_regCode += i;
                m_codeValid = kCodeValidUnknown;
            }
        }
    }
    
    if (inAppHandler.LatchedKeyStateTake(8) || inAppHandler.LatchedKeyStateTake(127) ) // Backspace and delete
    {
        if (m_regCode.length() > 0)
        {
            m_regCode = m_regCode.substr(0, m_regCode.length() - 1);
            m_codeValid = kCodeValidUnknown;
        }
    }
    
    if (m_codeValid == kCodeValidUnknown && m_regCode.length() == m_regCodeLength)
    {
        m_codeValid = kCodeValidFail;
        if (m_regCode.length() == m_regCodeLength)
        {
            if (GameUtils::CodeVerify(m_regCode))
            {
                m_codeValid = kCodeValidPass;
                SaveToFile();
            }
        }
        m_lastCheckMsec = m_currentMsec;
    }
    
    if (inAppHandler.LatchedKeyStateTake(' ') ||
        m_codeValid == kCodeValidPass && m_lastCheckMsec + 2000 < m_currentMsec)
    {
        inAppHandler.GameModeEnter(true);
    }
    GLUtils::PostRedisplay();
}

void
GameReg::Display(GameAppHandler& inAppHandler)
{
    GLUtils::DisplayPrologue();
    GLUtils::ClearScreen();
    GLUtils::OrthoPrologue();
    
    GameAppHandler& gameAppHandler=dynamic_cast<GameAppHandler &>(MushcoreAppHandler::Sgl());
    
    m_currentMsec=gameAppHandler.MillisecondsGet();
    
    GLState::DepthSet(GLState::kDepthNone);
    GLState::ModulationSet(GLState::kModulationColour);
    GLState::BlendSet(GLState::kBlendTransparent);
    
    GLState::ColourSet(1.0,1.0,1.0,1.0);
    GLUtils orthoGL;
    
    {
        orthoGL.MoveRelative(0, 0.2);
        GLString glStr(MushcoreInfo::Sgl().ApplicationNameGet(), GLFontRef("font-system1", 0.04), 0);
        glStr.Render();
    }
    
    {
        GLState::ColourSet(0.8,0.8,1.0,1);
        orthoGL.MoveRelative(0, -0.03);
        GLString glStr("Version: "+MushcoreInfo::Sgl().PackageVersionGet()+"  ID: "+MushcoreInfo::Sgl().PackageIDGet(), GLFontRef("font-system1", 0.018), 0);
        glStr.Render();
    }
    
    {
        GLState::ColourSet(1.0,1.0,1.0,1.0);
        orthoGL.MoveRelative(0, -0.12);
        GLString glStr("Registration Code", GLFontRef("font-system1", 0.03), 0);
        glStr.Render();
    }
    
    {
        GLState::ColourSet(0.8,0.8,1.0,1.0);
        GLString glStr("Click this window to buy", GLFontRef("font-system1", 0.02), 0);
        orthoGL.MoveRelative(0, -0.06);
        glStr.Render();
        
        GLState::ColourSet(0.8,0.8,1.0,1.0);
        glStr.TextSet("or enter your code");
        orthoGL.MoveRelative(0, -0.02);
        glStr.Render();
    }
    
    if (m_codeValid == kCodeValidPass)
    {
        {
            GLState::ColourSet(0.4,1.0,0.4,1.0);
            GLString glStr("Code Valid", GLFontRef("font-system1", 0.06), 0);
            
            orthoGL.MoveRelative(0, -0.06);
            glStr.Render();
        }
        {
            GLState::ColourSet(0.8,0.8,1.0,1.0);
            GLString glStr("Thank you", GLFontRef("font-system1", 0.02), 0);
            
            orthoGL.MoveRelative(0, -0.06);
            glStr.Render();
        }
    }
    else
    {
        if (m_codeValid == kCodeValidFail)
        {
            GLState::ColourSet(1.0,0.4,0.4,0.5+0.5*sin(m_currentMsec/100));
        }
        else
        {
            GLState::ColourSet(1.0,1.0,1.0,1.0);
        }
        {
            GLString glStr(m_regCode, GLFontRef("font-system1", 0.06), 0);
            
            orthoGL.MoveRelative(0, -0.06);
            glStr.Render();
        }
        if (m_codeValid == kCodeValidFail)
        {
            GLState::ColourSet(1.0,1.0,1.0,1.0);
            GLString glStr("Code Invalid", GLFontRef("font-system1", 0.02), 0);
            
            orthoGL.MoveRelative(0, -0.06);
            glStr.Render();
        }
        else
        {
            GLState::ColourSet(0.8,0.8,1.0,1.0);
            GLString glStr("(Space to skip)", GLFontRef("font-system1", 0.02), 0);
            
            orthoGL.MoveRelative(0, -0.06);
            glStr.Render();
        }
    }
    
    GLUtils::OrthoEpilogue();
    GLUtils::DisplayEpilogue();
}

bool
GameReg::CodeVerify(const std::string& inCode)
{
    bool success = true;
    if (inCode.length() != m_regCodeLength)
    {
        success = false;
    }
    else
    {
        std::istringstream prodCodeStrm(inCode.substr(0,m_regCodeLength/2));
        std::istringstream prodHashStrm(inCode.substr(m_regCodeLength/2,m_regCodeLength/2));
        U32 prodCode, prodHash;
        
        if (success && !(prodCodeStrm >> prodCode))
        {
            success = false;
        }
        if (success && !(prodHashStrm >> prodHash))
        {
            success = false;
        }
        for (U32 i=0; i<256; ++i)
        {
            prodCode ^= 1;
            U32 prodMask = (prodCode << 7) | (prodCode >> (32 - 7));
            prodCode ^= prodMask;
            U32 rotValue = prodCode & 31;
            prodCode = (prodCode << rotValue) | (prodCode >> (32 - rotValue));
        }
        cout << "prodCode=" << prodCode << ", prodHash=" << prodHash << endl;
        if (prodCode % 1000000 != prodHash)
        {
            success = false;   
        }
    }
    m_lastCheckMsec = m_currentMsec;
    return success;
}

void
GameReg::ScriptFunction(const string& inName, GameAppHandler& inAppHandler) const
{
}

void
GameReg::SwapIn(GameAppHandler& inAppHandler)
{
    GLAppHandler& glAppHandler=dynamic_cast<GLAppHandler &>(MushcoreAppHandler::Sgl());
    glAppHandler.EnterScreen(PlatformVideoUtils::Sgl().ModeDefGet(0));
}

void
GameReg::SwapOut(GameAppHandler& inAppHandler)
{
}

void
GameReg::SaveToFile(void)
{
    string filenameStr;
    const MushcoreScalar *pScalar;
    if (MushcoreEnv::Sgl().VariableGetIfExists(pScalar, "REG_FILENAME"))
    {
        filenameStr = pScalar->StringGet();
    }

    if (filenameStr != "")
    {
        ofstream outputFile(filenameStr.c_str());
        if (!outputFile) throw(MushcoreFileFail(filenameStr, "Could not open file"));
        MushcoreXMLOStream xmlOut(outputFile);
        
        GameCode *pGameCode = MushcoreData<GameCode>::Sgl().
            Give(MushcoreInfo::Sgl().PackageNameGet(), new GameCode);
        pGameCode->CodeSet(m_regCode);
        xmlOut << *pGameCode;
    }
}

//%outOfLineFunctions {

const char *GameReg::AutoNameGet(void) const
{
    return "GameReg";
}

MushcoreVirtualObject *GameReg::AutoClone(void) const
{
    return new GameReg(*this);
}

MushcoreVirtualObject *GameReg::AutoCreate(void) const
{
    return new GameReg;
}

MushcoreVirtualObject *GameReg::AutoVirtualFactory(void)
{
    return new GameReg;
}
namespace
{
void AutoInstall(void)
{
    MushcoreFactory::Sgl().FactoryAdd("GameReg", GameReg::AutoVirtualFactory);
}
MushcoreInstaller AutoInstaller(AutoInstall);
} // end anonymous namespace
void
GameReg::AutoPrint(std::ostream& ioOut) const
{
    ioOut << "[";
    ioOut << "regURL=" << m_regURL << ", ";
    ioOut << "regCodeLength=" << m_regCodeLength << ", ";
    ioOut << "authValue=" << m_authValue << ", ";
    ioOut << "]";
}
bool
GameReg::AutoXMLDataProcess(MushcoreXMLIStream& ioIn, const std::string& inTagStr)
{
    if (inTagStr == "obj")
    {
        ioIn >> *this;
    }
    else if (inTagStr == "regURL")
    {
        ioIn >> m_regURL;
    }
    else if (inTagStr == "regCodeLength")
    {
        ioIn >> m_regCodeLength;
    }
    else if (inTagStr == "authValue")
    {
        ioIn >> m_authValue;
    }
    else
    {
        return false;
    }
    return true;
}
void
GameReg::AutoXMLPrint(MushcoreXMLOStream& ioOut) const
{
    ioOut.TagSet("regURL");
    ioOut << m_regURL;
    ioOut.TagSet("regCodeLength");
    ioOut << m_regCodeLength;
    ioOut.TagSet("authValue");
    ioOut << m_authValue;
}
//%outOfLineFunctions } UjVeTVX86evV8ly5K5YldA

