/*
 * $Id: CoreApp.cpp,v 1.1.1.1 2002/02/11 22:30:08 southa Exp $
 * $Log: CoreApp.cpp,v $
 * Revision 1.1.1.1  2002/02/11 22:30:08  southa
 * Created
 *
 */

#include "CoreApp.hp"
#include "CorePOSIX.hp"
#include "CommandHandler.hp"
#include "CoreCommand.hp"
#include "CoreInterpreter.hp"

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
        list<ChildRecord>::iterator p=m_children.begin();
        list<ChildRecord>::iterator oldP=p;
        do
        {
            ChildStatus status;
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
    m_children.push_back(ChildRecord(pid, inPipe, outPipe));
}

void CoreApp::AddHandler(CommandHandler& inHandler)
{
    CoreInterpreter::Instance().AddHandler(inHandler);
}

