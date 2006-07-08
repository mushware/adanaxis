//%Header {
/*****************************************************************************
 *
 * File: src/Game/GameReg.cpp
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
//%Header } w2A217EHVnN/AC475uoR/A
/*
 * $Id: GameReg.cpp,v 1.10 2006/06/01 15:38:59 southa Exp $
 * $Log: GameReg.cpp,v $
 * Revision 1.10  2006/06/01 15:38:59  southa
 * DrawArray verification and fixes
 *
 * Revision 1.9  2005/07/02 00:42:37  southa
 * Conditioning tweaks
 *
 * Revision 1.8  2005/06/20 14:30:34  southa
 * Adanaxis work
 *
 * Revision 1.7  2005/06/16 17:25:38  southa
 * Client/server work
 *
 * Revision 1.6  2005/05/27 12:48:37  southa
 * Registration box tweaks
 *
 * Revision 1.5  2005/05/26 00:46:40  southa
 * Made buildable on win32
 *
 * Revision 1.4  2005/05/19 13:02:03  southa
 * Mac release work
 *
 * Revision 1.3  2005/04/19 23:25:39  southa
 * Mode switching and recognition
 *
 * Revision 1.2  2005/04/11 23:31:41  southa
 * Startup and registration screen
 *
 * Revision 1.1  2005/04/10 00:09:22  southa
 * Registration
 *
 */

#include "GameReg.h"


#include "GameAppHandler.h"
#include "GameSTL.h"
#include "GameUtils.h"

#include "mushGL.h"
#include "mushMedia.h"
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
    if (inAppHandler.LatchedKeyStateTake(MediaKeyboard::kKeyMouse0))
    {
        try
        {
            PlatformMiscUtils::LaunchURL(m_regURL);
        }
        catch (MushcoreNonFatalFail& e)
        {
            PlatformMiscUtils::MinorErrorBox("Failed to open URL '"+m_regURL+"' ("+e.what()+").  Please open in your browser.");
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
        inAppHandler.LatchedKeyStateTake('r');
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
        GLString glStr(MushcoreInfo::Sgl().ApplicationNameGet(), GLFontRef("font-mono1", 0.04), 0);
        glStr.Render();
    }
    
    {
        GLState::ColourSet(0.8,0.8,1.0,1);
        orthoGL.MoveRelative(0, -0.03);
        GLString glStr("Version: "+MushcoreInfo::Sgl().PackageVersionGet()+"  ID: "+MushcoreInfo::Sgl().PackageIDGet(), GLFontRef("font-mono1", 0.018), 0);
        glStr.Render();
    }
    
    {
        GLState::ColourSet(1.0,1.0,1.0,1.0);
        orthoGL.MoveRelative(0, -0.12);
        GLString glStr("Registration Code", GLFontRef("font-mono1", 0.03), 0);
        glStr.Render();
    }
    
    {
        GLState::ColourSet(0.8,0.8,1.0,1.0);
        GLString glStr("Click this window to buy,", GLFontRef("font-mono1", 0.02), 0);
        orthoGL.MoveRelative(0, -0.06);
        glStr.Render();
        
        GLState::ColourSet(0.8,0.8,1.0,1.0);
        glStr.TextSet("or enter your code below");
        orthoGL.MoveRelative(0, -0.02);
        glStr.Render();
    }
    
    if (m_codeValid == kCodeValidPass)
    {
        {
            GLState::ColourSet(0.4,1.0,0.4,1.0);
            GLString glStr("Code Valid", GLFontRef("font-mono1", 0.06), 0);
            
            orthoGL.MoveRelative(0, -0.06);
            glStr.Render();
        }
        {
            GLState::ColourSet(0.8,0.8,1.0,1.0);
            GLString glStr("Thank you", GLFontRef("font-mono1", 0.02), 0);
            
            orthoGL.MoveRelative(0, -0.06);
            glStr.Render();
        }
    }
    else
    {
        GLState::ColourSet(0.1,0.1,0.3,1.0);
        GLUtils::DrawRectangle(-0.4, -0.09, 0.4, -0.03);
        
        if (m_codeValid == kCodeValidFail)
        {
            GLState::ColourSet(1.0,0.4,0.4,0.5+0.5*sin(m_currentMsec/100));
        }
        else
        {
            GLState::ColourSet(1.0,1.0,1.0,1.0);
        }
        
        {
            std::string regCode = m_regCode;
            if (inAppHandler.HasFocus() && static_cast<U32>(m_currentMsec) % 1000 > 500)
            {
                regCode += " ";
            }
            else
            {
                regCode += "|";
            }
            GLString glStr(regCode, GLFontRef("font-mono1", 0.06), 0);
            
            orthoGL.MoveRelative(0, -0.06);
            glStr.Render();
        }
        if (m_codeValid == kCodeValidFail)
        {
            GLState::ColourSet(1.0,1.0,1.0,1.0);
            GLString glStr("Code Invalid", GLFontRef("font-mono1", 0.02), 0);
            
            orthoGL.MoveRelative(0, -0.06);
            glStr.Render();
        }
        else
        {
            GLState::ColourSet(0.8,0.8,1.0,1.0);
            GLString glStr("(Space to skip)", GLFontRef("font-mono1", 0.02), 0);
            
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

const char *GameReg::AutoName(void) const
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
        AutoInputPrologue(ioIn);
        ioIn >> *this;
        AutoInputEpilogue(ioIn);
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
//%outOfLineFunctions } +WGSujrVJYuJwX8jNp/RWA

