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
 * $Id: CoreApp.cpp,v 1.12 2002/12/20 13:17:31 southa Exp $
 * $Log: CoreApp.cpp,v $
 * Revision 1.12  2002/12/20 13:17:31  southa
 * Namespace changes, licence changes and source conditioning
 *
 * Revision 1.11  2002/10/22 20:41:57  southa
 * Source conditioning
 *
 * Revision 1.10  2002/08/27 08:56:15  southa
 * Source conditioning
 *
 * Revision 1.9  2002/08/07 13:36:44  southa
 * Conditioned source
 *
 * Revision 1.8  2002/07/06 18:04:14  southa
 * More designer work
 *
 * Revision 1.7  2002/07/02 14:27:12  southa
 * First floor map designer build
 *
 * Revision 1.6  2002/06/27 12:36:02  southa
 * Build process fixes
 *
 * Revision 1.5  2002/05/10 16:39:38  southa
 * Changed .hp files to .h
 *
 * Revision 1.4  2002/03/07 22:24:32  southa
 * Command interpreter working
 *
 * Revision 1.3  2002/03/05 22:44:45  southa
 * Changes to command handling
 *
 * Revision 1.2  2002/03/02 12:08:23  southa
 * First stage rework of command handler
 * Added core target
 *
 * Revision 1.1.1.1  2002/02/11 22:30:08  southa
 * Created
 *
 */

#include "CoreApp.h"
#include "CoreCommand.h"
#include "CoreCommandHandler.h"
#include "CoreInterpreter.h"
#include "CorePOSIX.h"

using namespace Mushware;
using namespace std;

CoreApp *CoreApp::m_instance = NULL;

void
CoreApp::Process(const string& inStr)
{
    CoreCommand command(inStr);
    command.Execute();
}

void
CoreApp::ServiceChildren(int &outCount)
{
    while (!m_children.empty())
    {
        bool done=false;
        list<CoreChildRecord>::iterator p=m_children.begin();
        list<CoreChildRecord>::iterator oldP=p;
        do
        {
            CoreChildStatus status;
            string outputStr;
            oldP=p;
            // Must do this now because erase might invalidate the current object
            if (++p == m_children.end()) done=true;

            if (oldP->OutputAppend(outputStr))
            {
                cout << outputStr;
            }
            if (oldP->StatusGet(status))
            {
                cout << "Status: " << status << endl;
                if (status.Dead())
                {
                    m_children.erase(oldP); // Modifes the list
                }
            }
        } while (!done);
    }
    outCount=m_children.size();
}


void
CoreApp::AddChild(int pid, int inPipe, int outPipe)
{
    m_children.push_back(CoreChildRecord(pid, inPipe, outPipe));
}

void
CoreApp::AddHandler(const string& inName, CoreCommandHandler inHandler)
{
    CoreInterpreter::Instance().AddHandler(inName, inHandler);
}

