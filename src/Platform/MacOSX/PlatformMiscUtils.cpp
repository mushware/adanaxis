/*****************************************************************************
 *
 * (Mushware file header version 1.1)
 *
 * This file contains original work by Andy Southgate.  Contact details can be
 * found at http://www.mushware.com.  This file was placed in the Public
 * Domain by Andy Southgate and Mushware Limited in 2002.
 *
 * This software carries NO WARRANTY of any kind.
 *
 ****************************************************************************/

/*
 * $Id: PlatformMiscUtils.cpp,v 1.14 2002/10/22 20:42:07 southa Exp $
 * $Log: PlatformMiscUtils.cpp,v $
 * Revision 1.14  2002/10/22 20:42:07  southa
 * Source conditioning
 *
 * Revision 1.13  2002/10/17 12:35:30  southa
 * Save path and update check
 *
 * Revision 1.12  2002/10/15 18:16:41  southa
 * Mac error box
 *
 * Revision 1.11  2002/10/15 14:02:31  southa
 * Mode changes
 *
 * Revision 1.10  2002/10/14 15:13:40  southa
 * Frame rate tweaks for Mac
 *
 * Revision 1.9  2002/10/10 13:51:17  southa
 * Speed fixes and various others
 *
 * Revision 1.8  2002/10/06 22:10:00  southa
 * Initial lighting test
 *
 * Revision 1.7.4.2  2002/09/07 10:58:41  southa
 * Removed usleep
 *
 * Revision 1.7.4.1  2002/09/04 10:18:04  southa
 * Fixed for MacOS X 10.2
 *
 * Revision 1.7  2002/08/27 08:56:29  southa
 * Source conditioning
 *
 * Revision 1.6  2002/08/07 13:36:51  southa
 * Conditioned source
 *
 * Revision 1.5  2002/07/06 18:04:20  southa
 * More designer work
 *
 * Revision 1.4  2002/06/27 12:36:08  southa
 * Build process fixes
 *
 * Revision 1.3  2002/06/27 00:07:06  southa
 * Catch up
 *
 * Revision 1.2  2002/06/13 15:15:56  southa
 * New directory structure, FPS printing, load command
 *
 * Revision 1.1  2002/06/11 16:25:00  southa
 * New paths to data files
 *
 */

#include "mushPlatform.h"
#include "mushMedia.h"

#include <Carbon/Carbon.h>

#include "PlatformBoxes.h"

#include <sys/types.h>
#include <sys/stat.h>

OSStatus FSPathMakeFSSpec(const UInt8 *path, FSSpec *spec, Boolean *isDirectory);
OSErr FinderLaunch(long nTargets, FSSpec *targetList);

void
PlatformMiscUtils::Initialise(void)
{
    char *home = getenv("HOME");
    if (home != NULL)
    {
        CoreGlobalConfig::Instance().Set("HOME", home);
    }
}

string
PlatformMiscUtils::GetApplPath(int argc, char *argv[])
{
    string systemPath=GetSystemPath(argc, argv);
    string::size_type pos=string::npos;
    pos = systemPath.rfind('/', pos-1);
    if (pos==string::npos) pos = systemPath.rfind('\\', pos-1);
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
    if (ioStr.substr(0, 4) == "-psn") ioStr="";
}

bool
PlatformMiscUtils::DirectoryExists(const string& inName)
{
    FSSpec fileSpec;
    Boolean isDirectory=false;
    if (FSPathMakeFSSpec(reinterpret_cast<const UInt8 *>(inName.c_str()), &fileSpec, &isDirectory) == noErr)
    {
        return isDirectory;
    }
    return false;
}

void
PlatformMiscUtils::MakeDirectory(const string& inName)
{
    errno=0;
    if (mkdir(inName.c_str(), 0700) != 0)
    {
        throw(CommandFail("mkdir "+inName+" failed: "+strerror(errno)));
    }
}

void
PlatformMiscUtils::ErrorBox(const string& inStr)
{
    SDL_ShowCursor(SDL_ENABLE);
    MediaSDL::Instance().QuitVideoIfRequired();
    ShowCursor();
    Str255 messageP;
    CopyCStringToPascal(inStr.c_str(), messageP);
    ParamText(messageP, "\p", "\p", "\p");
    StopAlert(kPlatformAboutBox, nil);
}

void
PlatformMiscUtils::MinorErrorBox(const string& inStr)
{
    SDL_ShowCursor(SDL_ENABLE);
    Str255 messageP;
    CopyCStringToPascal(inStr.c_str(), messageP);
    ParamText(messageP, "\p", "\p", "\p");
    NoteAlert(kPlatformAboutBox, nil);
}

void
PlatformMiscUtils::UpdateCheck(void)
{
    if (CoreGlobalConfig::Instance().Exists("FIRST_RUN"))
    {
        ShowUpdateAlert();
    }
}

void
PlatformMiscUtils::ShowUpdateAlert(void)
{    
    AlertStdAlertParamRec	param;

    SInt16			alertType=kAlertNoteAlert;
    Str255			text="\pInfernal Contractor II";
    Str255          desc="\pThank you for installing Infernal Contractor II!  As this is the first time you are running this application, we recommend that you visit the Mushware web site to check for any important information or updates.  Would you like to do this now?";
	SInt16			itemHit;

    param.movable 		= true;
    param.filterProc 	= nil;
    param.defaultText 	= "\pVisit Update Site";
    param.cancelText 	= "\pStart Game";
    param.otherText 	= "\pQuit";
    param.helpButton 	= false;
    param.defaultButton = kAlertStdAlertOKButton;
    param.cancelButton 	= kAlertStdAlertCancelButton;
    param.position 		= kWindowDefaultPosition;

    if (StandardAlert(alertType, text, desc, &param, &itemHit) == noErr)
    {
        switch (itemHit)
        {
            case kAlertStdAlertOKButton:
            {
                string updateFile=CoreGlobalConfig::Instance().Get("SYSTEMPATH").StringGet()+"/UpdateCheck.url";
                LaunchFile(updateFile);
                exit(0);
            }
            break;

            case kAlertStdAlertOtherButton:
                exit(0);
                break;

            default:
                break;
                
        }
    }
}

void
PlatformMiscUtils::LaunchFile(const string& inFile)
{
    FSSpec fileSpec;
    if (FSPathMakeFSSpec(reinterpret_cast<const UInt8 *>(inFile.c_str()), &fileSpec, NULL) == noErr)
    {
        FinderLaunch(1, &fileSpec);
    }
}

// From Apple sample code MoreFilesX.c
OSStatus
FSPathMakeFSSpec(
                 const UInt8 *path,
                 FSSpec *spec,
                 Boolean *isDirectory) /* can be NULL */
{
    OSStatus result;
    FSRef  ref;
     /* check parameters */
    require_action(NULL != spec, BadParameter, result = paramErr);
     /* convert the POSIX path to an FSRef */
    result = FSPathMakeRef(path, &ref, isDirectory);
    require_noerr(result, FSPathMakeRef);
     /* and then convert the FSRef to an FSSpec */
    result = FSGetCatalogInfo(&ref, kFSCatInfoNone, NULL, NULL, spec, NULL);
    require_noerr(result, FSGetCatalogInfo);
    FSGetCatalogInfo:
FSPathMakeRef:
BadParameter:
         return ( result );
}


// From Apple sample code FinderLaunch.c
OSErr FinderLaunch(long nTargets, FSSpec *targetList) {
    OSErr err;
    AppleEvent theAEvent, theReply;
    AEAddressDesc fndrAddress;
    AEDescList targetListDesc;
    OSType fndrCreator;
    Boolean wasChanged;
    AliasHandle targetAlias;
    long index;
      /* verify parameters */
    if ((nTargets == 0) || (targetList == NULL)) return paramErr;
      /* set up locals  */
    AECreateDesc(typeNull, NULL, 0, &theAEvent);
    AECreateDesc(typeNull, NULL, 0, &fndrAddress);
    AECreateDesc(typeNull, NULL, 0, &theReply);
    AECreateDesc(typeNull, NULL, 0, &targetListDesc);
    targetAlias = NULL;
    fndrCreator = 'MACS';
      /* create an open documents event targeting the finder */
    err = AECreateDesc(typeApplSignature, (Ptr) &fndrCreator,
                       sizeof(fndrCreator), &fndrAddress);
    if (err != noErr) goto bail;
    err = AECreateAppleEvent(kCoreEventClass, kAEOpenDocuments,
                             &fndrAddress, kAutoGenerateReturnID,
                             kAnyTransactionID, &theAEvent);
    if (err != noErr) goto bail;
      /* create the list of files to open */
    err = AECreateList(NULL, 0, false, &targetListDesc);
    if (err != noErr) goto bail;
    for ( index=0; index < nTargets; index++) {
        if (targetAlias == NULL)
            err = NewAlias(NULL, (targetList + index), &targetAlias);
        else err = UpdateAlias(NULL, (targetList + index), targetAlias, &wasChanged);
        if (err != noErr) goto bail;
        HLock((Handle) targetAlias);
        err = AEPutPtr(&targetListDesc, (index + 1), typeAlias, *targetAlias, GetHandleSize((Handle) targetAlias));
        HUnlock((Handle) targetAlias);
        if (err != noErr) goto bail;
    }
      /* add the file list to the apple event */
    err = AEPutParamDesc(&theAEvent, keyDirectObject, &targetListDesc);
    if (err != noErr) goto bail;
      /* send the event to the Finder */
    err = AESend(&theAEvent, &theReply, kAENoReply,
                 kAENormalPriority, kAEDefaultTimeout, NULL, NULL);
      /* clean up and leave */
bail:
        if (targetAlias != NULL) DisposeHandle((Handle) targetAlias);
    AEDisposeDesc(&targetListDesc);
    AEDisposeDesc(&theAEvent);
    AEDisposeDesc(&fndrAddress);
    AEDisposeDesc(&theReply);
    return err;
}


    


