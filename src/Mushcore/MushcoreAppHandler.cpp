/*****************************************************************************
 *
 * (Mushware file header version 1.2)
 *
 * This file contains original work by Andy Southgate.
 * Copyright Andy Southgate 2002.  All rights reserved.
 * Contact details can be found at http://www.mushware.com/
 *
 ****************************************************************************/

/*
 * $Id: MushcoreAppHandler.cpp,v 1.12 2002/12/29 20:59:50 southa Exp $
 * $Log: MushcoreAppHandler.cpp,v $
 * Revision 1.12  2002/12/29 20:59:50  southa
 * More build fixes
 *
 * Revision 1.11  2002/12/20 13:17:31  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.10  2002/11/18 11:31:13  southa
 * Return to game mode
 *
 * Revision 1.9  2002/10/22 20:41:57  southa
 * Source conditioning
 *
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

#include "MushcoreAppHandler.h"
#include "MushcoreApp.h"
#include "MushcorePOSIX.h"

using namespace Mushware;
using namespace std;

MushcoreAppHandler *MushcoreAppHandler::m_instance = NULL;

void
MushcoreAppHandler::Mutate(MushcoreAppHandler *inAppHandler)
{
    delete(m_instance);
    m_instance=inAppHandler;
}

void
MushcoreAppHandler::Initialise(void)
{

}

void
MushcoreAppHandler::MainLoop(void)
{
    Idle();
}

void
MushcoreAppHandler::Idle(void)
{
    int childCount;
    MushcoreApp::Instance().ServiceChildren(childCount);
#ifdef HAVE_POSIX
    cout << "Sleeping in MushcoreAppHandler" << endl;
    sleep(1);
#endif
}

void
MushcoreAppHandler::Signal(const MushcoreAppSignal& inSignal)
{
    switch (inSignal.SigNumberGet())
    {
        case MushcoreAppSignal::kQuit:
            cerr << "Quit signal.  Bye!" << endl;
            exit(0);
            break;

        case MushcoreAppSignal::kEscape:
            Signal(MushcoreAppSignal(MushcoreAppSignal::kQuit));
            break;
            
        default:
            cerr << "Unhandled MushcoreApp signal 0x" << hex << inSignal.SigNumberGet() << dec << endl;
            break;
    }
}
