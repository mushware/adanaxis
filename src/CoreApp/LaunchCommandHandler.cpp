/*
 * $Id: LaunchCommandHandler.cpp,v 1.1.1.1 2002/02/11 22:30:08 southa Exp $
 * $Log: LaunchCommandHandler.cpp,v $
 * Revision 1.1.1.1  2002/02/11 22:30:08  southa
 * Created
 *
 */
 
#include "LaunchCommandHandler.hp"
#include "CoreApp.hp"
#include "Installer.hp"
#include "CorePOSIX.hp"
#include "CoreCommand.hp"

LaunchCommandHandler *LaunchCommandHandler::m_instance = NULL;

Installer LaunchCommandHandlerInstaller(LaunchCommandHandler::Install);

CoreScalar
LaunchCommandHandler::Execute(CoreCommand& ioCommand, CoreEnv &ioEnv)
{
    string funcName(ioCommand.AllParams());
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
        char *args=new char[funcName.size()+3];
        char inQuotes='\0';
        char lastFuncName=' ';
        Size j=0;
        for (Size i=0; i<funcName.size(); i++)
        {
            if (inQuotes != '\0')
            {
                if (funcName[i] == inQuotes)
                {
                    inQuotes = '\0';
                    args[j++]='\0';
                }
                else
                {
                    args[j++]=funcName[i];
                }
            }
            else if (funcName[i] == '"' || funcName[i] == '\'')
            {
                argvector.push_back(&args[j]);
                inQuotes=funcName[i];
            }
            else if (funcName[i] > ' ' && lastFuncName <= ' ')
            {
                // Start of new arg
                argvector.push_back(&args[j]);
                args[j++]=funcName[i];
            }
            else if (funcName[i] <= ' ' && lastFuncName > ' ')
            {
                // End of word
                args[j++]='\0'; // Null terminate arg
            }
            else
            {
                args[j++]=funcName[i];
            }
            lastFuncName=funcName[i];
        }
        args[j++]='\0';
        argvector.push_back(0);

        if (inQuotes != '\0')
        {
            // Message to be picked up by the parent
            cout << "Launch of '" << funcName << "' failed: Mismatched " << inQuotes << endl;
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
        cout << "Launch of '" << funcName << "' failed: " << strerror(errno) << endl;
        _exit(1);
    }
    else
    {
        close(p[kStdout]);
        CoreApp::Instance().AddChild(cpid, p[kStdin], NULL);
    }
    return CoreScalar(0);
}

void
LaunchCommandHandler::Install(void)
{
    CoreApp::Instance().AddHandler("launch", Instance());
}