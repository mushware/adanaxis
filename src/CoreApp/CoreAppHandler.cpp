/*
 * $Id: CoreAppHandler.cpp,v 1.3 2002/05/31 15:18:15 southa Exp $
 * $Log: CoreAppHandler.cpp,v $
 * Revision 1.3  2002/05/31 15:18:15  southa
 * Keyboard reading
 *
 * Revision 1.2  2002/05/10 16:39:38  southa
 * Changed .hp files to .h
 *
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
    Idle();
}

void
CoreAppHandler::Idle(void)
{
    int childCount;
    CoreApp::Instance().ServiceChildren(childCount);
#ifdef HAVE_POSIX
    cout << "Sleeping in CoreAppHandler" << endl;
    sleep(1);
#endif
}

void
CoreAppHandler::Signal(const CoreAppSignal& inSignal)
{
    switch (inSignal.SigNumberGet())
    {
        case CoreAppSignal::kQuit:
            cerr << "Quit signal.  Bye!" << endl;
            exit(0);
            break;

        case CoreAppSignal::kEscape:
            Instance().Signal(CoreAppSignal(CoreAppSignal::kQuit));
            break;
            
        default:
            cerr << "Unhandled CoreApp signal 0x" << hex << inSignal.SigNumberGet() << dec << endl;
            break;
    }
}
