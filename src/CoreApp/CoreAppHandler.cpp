/*****************************************************************************
 *
 * (Mushware file header version 1.1)
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/

/*
 * $Id: CoreAppHandler.cpp,v 1.8 2002/08/27 08:56:15 southa Exp $
 * $Log: CoreAppHandler.cpp,v $
 * Revision 1.8  2002/08/27 08:56:15  southa
 * Source conditioning
 *
 * Revision 1.7  2002/08/07 13:36:44  southa
 * Conditioned source
 *
 * Revision 1.6  2002/07/06 18:04:14  southa
 * More designer work
 *
 * Revision 1.5  2002/06/27 12:36:02  southa
 * Build process fixes
 *
 * Revision 1.4  2002/06/24 16:41:14  southa
 * Fixed for mingw32
 *
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
