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
 * $Id: PlatformMiscUtils.cpp,v 1.6 2002/09/01 22:00:38 southa Exp $
 * $Log: PlatformMiscUtils.cpp,v $
 * Revision 1.6  2002/09/01 22:00:38  southa
 * Moved to real install paths
 *
 * Revision 1.5  2002/08/27 08:56:29  southa
 * Source conditioning
 *
 * Revision 1.4  2002/08/07 13:36:51  southa
 * Conditioned source
 *
 * Revision 1.3  2002/07/06 18:04:20  southa
 * More designer work
 *
 * Revision 1.2  2002/06/27 12:36:08  southa
 * Build process fixes
 *
 * Revision 1.1  2002/06/26 17:56:34  southa
 * Created
 *
 * Revision 1.5  2002/06/20 11:06:15  southa
 * Updated for cygwin
 *
 * Revision 1.4  2002/06/13 15:53:33  southa
 * Path fixes
 *
 * Revision 1.3  2002/06/11 18:12:04  southa
 * Fixed for cygwin
 *
 * Revision 1.2  2002/06/11 16:36:13  southa
 * Fixes
 *
 * Revision 1.1  2002/06/11 16:25:00  southa
 * New paths to data files
 *
 */

#include "mushPlatform.h"


string
PlatformMiscUtils::GetApplPath(int argc, char *argv[])
{
    string systemPath=GetSystemPath(argc, argv);
    string::size_type pos=string::npos;
    pos = systemPath.rfind('/', pos-1);
    if (pos==string::npos || pos == 0)
    {
        cerr << "Couldn't decode application path from '" << systemPath << "'" << endl;
        exit(1);
    }
    systemPath.resize(pos);

    return systemPath;
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
