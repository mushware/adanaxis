/*****************************************************************************
 *
 * (Mushware file header version 1.0)
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.co.uk.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/

/*
 * $Id: CoreApp.cpp,v 1.6 2002/06/27 12:36:02 southa Exp $
 * $Log: CoreApp.cpp,v $
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
#include "CorePOSIX.h"
#include "CoreCommandHandler.h"
#include "CoreCommand.h"
#include "CoreInterpreter.h"

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

