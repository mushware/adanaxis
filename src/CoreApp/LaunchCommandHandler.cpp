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
 * $Id: LaunchCommandHandler.cpp,v 1.14 2002/10/22 20:41:59 southa Exp $
 * $Log: LaunchCommandHandler.cpp,v $
 * Revision 1.14  2002/10/22 20:41:59  southa
 * Source conditioning
 *
 * Revision 1.13  2002/08/27 09:09:06  southa
 * Fixed file corruption
 *
 * Revision 1.11  2002/08/27 08:56:18  southa
 * Source conditioning
 *
 * Revision 1.10  2002/08/07 13:36:46  southa
 * Conditioned source
 *
 * Revision 1.9  2002/07/06 18:04:17  southa
 * More designer work
 *
 * Revision 1.8  2002/07/02 14:27:12  southa
 * First floor map designer build
 *
 * Revision 1.7  2002/06/27 12:36:05  southa
 * Build process fixes
 *
 * Revision 1.6  2002/06/24 16:41:14  southa
 * Fixed for mingw32
 *
 * Revision 1.5  2002/05/24 16:23:10  southa
 * Config and typenames
 *
 * Revision 1.4  2002/05/10 16:39:37  southa
 * Changed .hp files to .h
 *
 * Revision 1.3  2002/03/07 22:24:34  southa
 * Command interpreter working
 *
 * Revision 1.2  2002/03/05 22:44:46  southa
 * Changes to command handling
 *
 * Revision 1.1.1.1  2002/02/11 22:30:08  southa
 * Created
 *
 */
 
#include "LaunchCommandHandler.h"
#include "CoreApp.h"
#include "CoreCommand.h"
#include "CoreInstaller.h"
#include "CorePOSIX.h"

using namespace Mushware;

CoreInstaller LaunchCommandHandlerInstaller(LaunchCommandHandler::Install);

CoreScalar
LaunchCommandHandler::Launch(CoreCommand& ioCommand, CoreEnv &ioEnv)
{
#ifdef HAVE_POSIX
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
        tSize j=0;
        for (tSize i=0; i<funcName.size(); i++)
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
        
        for (tSize i=0; i<argvector.size(); i++)
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
        CoreApp::Instance().AddChild(cpid, p[kStdin], 0);
    }
    return CoreScalar(0);
#endif
}

void
LaunchCommandHandler::Install(void)
{
#ifdef HAVE_POSIX
// Disabled for security reasons
#if 0    
    CoreApp::Instance().AddHandler("launch", Launch);
#endif
#endif
}
