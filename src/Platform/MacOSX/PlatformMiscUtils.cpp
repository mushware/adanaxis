/*
 * $Id$
 * $Log$
 */

#include "PlatformMiscUtils.h"

string
PlatformMiscUtils::GetApplPath(int argc, char *argv[])
{
    string appPath;
    char *pBuffer=new char[MAXPATHLEN];
    if (getcwd(pBuffer, MAXPATHLEN) &&
        strlen(pBuffer) > 1)
    {
        // Started from ProjectBuilder
        appPath=string(pBuffer)+"/contractor";
    }
    else
    {
        // Started from Finder
        appPath=string(argv[0]);

        string::size_type pos=string::npos;
        for (U32 i=0; i<5; ++i)
        {
            pos = appPath.rfind('/', pos-1);
            if (pos==string::npos || pos == 0)
            {
                cerr << "Couldn't decode application path from '" << appPath << "'" << endl;
                exit(1);
            }
        }
        appPath.resize(pos);
    }
    delete[] pBuffer;
    return appPath;
}

string
PlatformMiscUtils::GetSystemPath(int argc, char *argv[])
{
    string appPath;
    char *pBuffer=new char[MAXPATHLEN];
    if (getcwd(pBuffer, MAXPATHLEN) &&
        strlen(pBuffer) > 1)
    {
        // Started from ProjectBuilder
        appPath=string(pBuffer)+"/contractor/system";
    }
    else
    {
        // Started from Finder
        appPath=string(argv[0]);

        string::size_type pos=string::npos;
        for (U32 i=0; i<4; ++i)
        {
            pos = appPath.rfind('/', pos-1);
            if (pos==string::npos || pos == 0)
            {
                cerr << "Couldn't decode system path from '" << appPath << "'" << endl;
                exit(1);
            }
        }
        appPath.resize(pos);
    }
    delete[] pBuffer;
    return appPath;
}

void
PlatformMiscUtils::TweakArgs(string& ioStr)
{
    if (ioStr.substr(0, 4) == "-psn") ioStr="";
}
