/*
 * $Id$
 * $Log$
 */
 
#include "LaunchCommandHandler.hp"
#include "CoreApp.hp"
#include "Installer.hp"
#include "CorePOSIX.hp"

LaunchCommandHandler *LaunchCommandHandler::m_instance = NULL;

Installer LaunchCommandHandlerInstaller(LaunchCommandHandler::Install);

bool
LaunchCommandHandler::HandleCommand(const string& str)
{
    if (str.substr(0,6) == "launch") Launch(str.substr(6));
    else return false;
    
    return true;
}

void
LaunchCommandHandler::Launch(const string& inStr)
{
    typedef enum
    {
        kStdin=0,
        kStdout=1
    };
    int   p[2];
    int   cpid=0;

    pipe(p);

    cpid = fork();
    if (cpid == 0)
    {
        // Child process
        close(kStdout);
        dup(p[kStdout]);
        close(p[kStdin]);
        close(p[kStdout]);

        vector<char *> argvector;
        // Condition input string
        char *args=new char[inStr.size()+3];
        char inQuotes='\0';
        char lastInStr=' ';
        Size j=0;
        for (Size i=0; i<inStr.size(); i++)
        {
            if (inQuotes != '\0')
            {
                if (inStr[i] == inQuotes)
                {
                    inQuotes = '\0';
                    args[j++]='\0';
                }
                else
                {
                    args[j++]=inStr[i];
                }
            }
            else if (inStr[i] == '"' || inStr[i] == '\'')
            {
                argvector.push_back(&args[j]);
                inQuotes=inStr[i];
            }
            else if (inStr[i] > ' ' && lastInStr <= ' ')
            {
                // Start of new arg
                argvector.push_back(&args[j]);
                args[j++]=inStr[i];
            }
            else if (inStr[i] <= ' ' && lastInStr > ' ')
            {
                // End of word
                args[j++]='\0'; // Null terminate arg
            }
            else
            {
                args[j++]=inStr[i];
            }
            lastInStr=inStr[i];
        }
        args[j++]='\0';
        argvector.push_back(0);

        if (inQuotes != '\0')
        {
            // Message to be picked up by the parent
            cout << "Launch of '" << inStr << "' failed: Mismatched " << inQuotes << endl;
            _exit(1);
        }
        char **argv=new (char *)[argvector.size()];
        
        for (Size i=0; i<argvector.size(); i++)
        {
            argv[i] = argvector[i];
        }
        errno=0;
        execve(argv[0], &argv[0], 0);
        // Message to be picked up by the parent
        cout << "Launch of '" << inStr << "' failed: " << strerror(errno) << endl;
        _exit(1);
    }
    else
    {
        close(p[kStdout]);
        CoreApp::Instance().AddChild(cpid, p[kStdin], NULL);
    }
}

void
LaunchCommandHandler::Install(void)
{
    CoreApp::Instance().AddHandler(Instance());
}