# Microsoft Developer Studio Project File - Name="mustl" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=mustl - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "mustl.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "mustl.mak" CFG="mustl - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "mustl - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "mustl - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe

!IF  "$(CFG)" == "mustl - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "mustl - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "mustl___"
# PROP BASE Intermediate_Dir "mustl___"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "mustl___"
# PROP Intermediate_Dir "mustl___"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /W3 /GR /GX /Od /I "..\src\Mushcore" /I "..\..\msvclibs\expat\source\lib" /I "..\..\msvclibs\pcre" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# SUBTRACT CPP /Z<none> /Fr
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "mustl - Win32 Release"
# Name "mustl - Win32 Debug"
# Begin Source File

SOURCE=..\src\Mustl\Mustl.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Mustl\Mustl.h
# End Source File
# Begin Source File

SOURCE=..\src\Mustl\MustlAddress.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Mustl\MustlAddress.h
# End Source File
# Begin Source File

SOURCE=..\src\Mustl\MustlAssert.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Mustl\MustlAssert.h
# End Source File
# Begin Source File

SOURCE=..\src\Mustl\MustlClient.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Mustl\MustlClient.h
# End Source File
# Begin Source File

SOURCE=..\src\Mustl\MustlConfig.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Mustl\MustlConfig.h
# End Source File
# Begin Source File

SOURCE=..\src\Mustl\MustlConfigDef.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Mustl\MustlConfigDef.h
# End Source File
# Begin Source File

SOURCE=..\src\Mustl\MustlConfigDefBool.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Mustl\MustlConfigDefBool.h
# End Source File
# Begin Source File

SOURCE=..\src\Mustl\MustlConfigDefMenuString.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Mustl\MustlConfigDefMenuString.h
# End Source File
# Begin Source File

SOURCE=..\src\Mustl\MustlConfigDefPassword.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Mustl\MustlConfigDefPassword.h
# End Source File
# Begin Source File

SOURCE=..\src\Mustl\MustlConfigDefString.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Mustl\MustlConfigDefString.h
# End Source File
# Begin Source File

SOURCE=..\src\Mustl\MustlConfigDefU32.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Mustl\MustlConfigDefU32.h
# End Source File
# Begin Source File

SOURCE=..\src\Mustl\MustlConfigDefVal.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Mustl\MustlConfigDefVal.h
# End Source File
# Begin Source File

SOURCE=..\src\Mustl\MustlData.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Mustl\MustlData.h
# End Source File
# Begin Source File

SOURCE=..\src\Mustl\MustlFail.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Mustl\MustlFail.h
# End Source File
# Begin Source File

SOURCE=..\src\Mustl\MustlHTTP.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Mustl\MustlHTTP.h
# End Source File
# Begin Source File

SOURCE=..\src\Mustl\MustlID.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Mustl\MustlID.h
# End Source File
# Begin Source File

SOURCE=..\src\Mustl\MustlIDNull.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Mustl\MustlIDNull.h
# End Source File
# Begin Source File

SOURCE=..\src\Mustl\MustlIDString.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Mustl\MustlIDString.h
# End Source File
# Begin Source File

SOURCE=..\src\Mustl\MustlLink.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Mustl\MustlLink.h
# End Source File
# Begin Source File

SOURCE=..\src\Mustl\MustlLog.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Mustl\MustlLog.h
# End Source File
# Begin Source File

SOURCE=..\src\Mustl\MustlMessageHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Mustl\MustlMessageHandler.h
# End Source File
# Begin Source File

SOURCE=..\src\Mustl\MustlMushcore.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Mustl\MustlMushcore.h
# End Source File
# Begin Source File

SOURCE=..\src\Mustl\MustlMushcoreSingleton.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Mustl\MustlMushcoreSingleton.h
# End Source File
# Begin Source File

SOURCE=..\src\Mustl\MustlPlatform.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Mustl\MustlPlatform.h
# End Source File
# Begin Source File

SOURCE=..\src\Mustl\MustlPlatformError.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Mustl\MustlPlatformError.h
# End Source File
# Begin Source File

SOURCE=..\src\Mustl\MustlPlatformHeaders.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Mustl\MustlPlatformHeaders.h
# End Source File
# Begin Source File

SOURCE=..\src\Mustl\MustlProtocol.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Mustl\MustlProtocol.h
# End Source File
# Begin Source File

SOURCE=..\src\Mustl\MustlRouter.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Mustl\MustlRouter.h
# End Source File
# Begin Source File

SOURCE=..\src\Mustl\MustlServer.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Mustl\MustlServer.h
# End Source File
# Begin Source File

SOURCE=..\src\Mustl\MustlStandard.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Mustl\MustlStandard.h
# End Source File
# Begin Source File

SOURCE=..\src\Mustl\MustlSTL.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Mustl\MustlSTL.h
# End Source File
# Begin Source File

SOURCE=..\src\Mustl\MustlTimer.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Mustl\MustlTimer.h
# End Source File
# Begin Source File

SOURCE=..\src\Mustl\MustlUtils.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Mustl\MustlUtils.h
# End Source File
# Begin Source File

SOURCE=..\src\Mustl\MustlWebCommands.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Mustl\MustlWebCommands.h
# End Source File
# Begin Source File

SOURCE=..\src\Mustl\MustlWebLink.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Mustl\MustlWebLink.h
# End Source File
# Begin Source File

SOURCE=..\src\Mustl\MustlWebRouter.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Mustl\MustlWebRouter.h
# End Source File
# Begin Source File

SOURCE=..\src\Mustl\MustlWebServer.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Mustl\MustlWebServer.h
# End Source File
# End Target
# End Project
