/*
 * $Id$
 * $Log$
 */

#include "GameQuit.h"

#include "GameAppHandler.h"
#include "GameConfigDef.h"

#include "mushMedia.h"
#include "mushGL.h"
#include "mushPlatform.h"

GameQuit::GameQuit() :
    m_gameState(kGameStateInit)
{
}

void
GameQuit::Process(void)
{
    switch (m_gameState)
    {
        case kGameStateInit:
            Init();
            m_gameState=kGameStateTiming;
            break;

        case kGameStateTiming:
            Timing();
            break;

        default:
            throw(LogicFail("Bad value for m_gameState"));
    }
}

void
GameQuit::Display(void)
{
    GLUtils::DisplayPrologue();
    GLUtils::ClearScreen();
    GLUtils::OrthoPrologue();

    GameAppHandler& gameAppHandler=dynamic_cast<GameAppHandler &>(CoreAppHandler::Instance());

    tVal msecNow=gameAppHandler.MillisecondsGet() - m_startMsec;
    
    GLState::ColourSet(1.0,1.0,1.0,1.0);
    GLUtils orthoGL;

    {
        orthoGL.MoveRelative(0, 0.2);
        GLString glStr(CoreInfo::ApplicationNameGet(), GLFontRef("font-system1", 0.04), 0);
        glStr.Render();
    }

    {
        GLState::ColourSet(0.8,0.8,1.0,1);
        orthoGL.MoveRelative(0, -0.03);
        GLString glStr("Version: "+CoreInfo::PackageVersionGet()+"  ID: "+CoreInfo::PackageIDGet(), GLFontRef("font-system1", 0.018), 0);
        glStr.Render();
    }
    
    
    {
        GLState::ColourSet(1.0,1.0,1.0,0.75+0.25*sin(msecNow/100));
        orthoGL.MoveRelative(0, -0.12);
        GLString glStr("Quitting", GLFontRef("font-system1", 0.03), 0);
        glStr.Render();
    }
    GLUtils::OrthoEpilogue();
    GLUtils::DisplayEpilogue();
}

void
GameQuit::Init(void)
{
    GameAppHandler& gameAppHandler=dynamic_cast<GameAppHandler &>(CoreAppHandler::Instance());

    MediaNetLog::Instance().Log() << "Waiting to quit" << endl;
    m_startMsec=gameAppHandler.MillisecondsGet();
}    

void
GameQuit::Timing(void)
{
    MediaNetWebServer::Instance().Accept();
    MediaNetWebRouter::Instance().ReceiveAll();
    GLUtils::PostRedisplay();
    GameAppHandler& gameAppHandler=dynamic_cast<GameAppHandler &>(CoreAppHandler::Instance());
    U32 currentMsec=gameAppHandler.MillisecondsGet();

    if (m_startMsec + kQuitHangTime < currentMsec)
    {
        // Quit after quit hang time if all web links are closed
        if (CoreData<MediaNetWebLink>::Instance().Size() == 0)
        {
            MediaNetLog::Instance().Log() << "Quitting" << endl;
            gameAppHandler.AppQuit();
        }
    }
    
    if (m_startMsec + kQuitTimeout < currentMsec)
    {
        MediaNetLog::Instance().Log() << "Quitting on timeout" << endl;
        gameAppHandler.AppQuit();
    }
}

void
GameQuit::ScriptFunction(const string& inName) const
{
}

void
GameQuit::SwapIn(void)
{
}

void
GameQuit::SwapOut(void)
{
}
