/*
 * $Id$
 * $Log$
 */

#include "CoreAppHandler.hp"
#include "CorePOSIX.hp"
#include "CoreApp.hp"

CoreAppHandler *CoreAppHandler::m_instance = NULL;

void
CoreAppHandler::Mutate(CoreAppHandler *inAppHandler)
{
    delete(m_instance);
    m_instance=inAppHandler;
}

void
CoreAppHandler::Initialise(void)
{

}

void
CoreAppHandler::MainLoop(void)
{
    bool quit=false;
    while (!quit)
    {
        int uSleepFor=0;
        Idle(quit, uSleepFor);
        if (uSleepFor > 0) usleep(uSleepFor);
    }
}

void
CoreAppHandler::Idle(bool& outQuit, int& outUSleepFor)
{
    int childCount;
    CoreApp::Instance().ServiceChildren(childCount);
    outUSleepFor=1000;
    outQuit=(childCount == 0);
}
