/*
 * $Id$
 * $Log$
 */

#include "CoreApp.hp"
#include "CorePOSIX.hp"
#include "CommandHandler.hp"

CoreApp *CoreApp::m_instance = NULL;

void
CoreApp::Process(const string& inStr)
{
    Size start=0;
    Size i;
    for (i=0; i<inStr.size(); i++)
    {
        switch (inStr[i])
        {
            case ';':
            case 10:
            case 13:
                if (start < i)
                {
                    string command(inStr, start, i-start);
                    Execute(command);
                }
                start=i+1;
                break;
        }
    }
    if (start < i)
    {
        string command(inStr, start, i-start);
        Execute(command);
    }
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
CoreApp::Execute(const string& command)
{
    for (Size i=0; i<m_handlers.size(); i++)
    {
        try
        {
            if (m_handlers[i]->HandleCommand(command))
            {
                // Command was handled
                return;
            }
        }
        catch (CommandFail& cf)
        {
            cerr << "Command failed: " << cf << endl;
            return;
        }
    }
    cerr << "Unknown command '" << command << "'" << endl;
}

void
CoreApp::AddChild(int pid, int inPipe, int outPipe)
{
    m_children.push_back(ChildRecord(pid, inPipe, outPipe));
}

void
CoreApp::AddHandler(CommandHandler& inHandler)
{
    m_handlers.push_back(&inHandler);
}
