/*
 * $Id: CoreAppHandler.cpp,v 1.1.1.1 2002/02/11 22:30:08 southa Exp $
 * $Log: CoreAppHandler.cpp,v $
 * Revision 1.1.1.1  2002/02/11 22:30:08  southa
 * Created
 *
 */

#include "CoreAppHandler.h"
#include "CorePOSIX.h"
#include "CoreApp.h"

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
