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
        appPath=string(pBuffer);
        string::size_type pos=string::npos;
        pos = appPath.rfind('/', pos-1);
        if (pos==string::npos || pos == 0)
        {
            cerr << "Couldn't decode application path from '" << appPath << "'" << endl;
            exit(1);
        }
        appPath.resize(pos);
    }
    else
    {
        cerr << "Couldn't decode application path from '" << appPath << "'" << endl;
        exit(1);
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
        appPath=string(pBuffer);
    }
    else
    {
        cerr << "Couldn't decode system path from '" << appPath << "'" << endl;
        exit(1);
    }
    delete[] pBuffer;
    return appPath;
}

void
PlatformMiscUtils::TweakArgs(string& ioStr)
{
}
