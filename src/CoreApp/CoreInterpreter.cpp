/*
 * $Id$
 * $Log$
 */

#include "CoreInterpreter.hp"
#include "CommandHandler.hp"

CoreInterpreter *CoreInterpreter::m_instance = NULL;

void
CoreInterpreter::Execute(const string& inStr)
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
                    ExecuteSub(command);
                }
                start=i+1;
                break;
        }
    }
    if (start < i)
    {
        string command(inStr, start, i-start);
        ExecuteSub(command);
    }
}

void
CoreInterpreter::ExecuteSub(const string& inStr)
{
    for (Size i=0; i<m_handlers.size(); i++)
    {
        try
        {
            if (m_handlers[i]->HandleCommand(inStr))
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
    cerr << "Unknown command '" << inStr << "'" << endl;
}

void
CoreInterpreter::AddHandler(CommandHandler& inHandler)
{
    m_handlers.push_back(&inHandler);
}
