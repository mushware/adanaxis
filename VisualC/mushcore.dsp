# Microsoft Developer Studio Project File - Name="mushcore" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=mushcore - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "mushcore.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "mushcore.mak" CFG="mushcore - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "mushcore - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "mushcore - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe

!IF  "$(CFG)" == "mushcore - Win32 Release"

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

!ELSEIF  "$(CFG)" == "mushcore - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /Od /I "..\..\msvclibs\expat\source\lib" /I "..\..\msvclibs\pcre" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /Zm1000 /c
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "mushcore - Win32 Release"
# Name "mushcore - Win32 Debug"
# Begin Source File

SOURCE=..\src\Mushcore\Mushcore.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Mushcore\Mushcore.h
# End Source File
# Begin Source File

SOURCE=..\src\Mushcore\MushcoreAbstractSingleton.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Mushcore\MushcoreAbstractSingleton.h
# End Source File
# Begin Source File

SOURCE=..\src\Mushcore\MushcoreAppHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Mushcore\MushcoreAppHandler.h
# End Source File
# Begin Source File

SOURCE=..\src\Mushcore\MushcoreAppSignal.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Mushcore\MushcoreAppSignal.h
# End Source File
# Begin Source File

SOURCE=..\src\Mushcore\MushcoreAutoMonkey.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Mushcore\MushcoreAutoMonkey.h
# End Source File
# Begin Source File

SOURCE=..\src\Mushcore\MushcoreBison.cpp

!IF  "$(CFG)" == "mushcore - Win32 Release"

!ELSEIF  "$(CFG)" == "mushcore - Win32 Debug"

# ADD CPP /Ze /Gi- /Od
# SUBTRACT CPP /nologo /Gf /Gy /YX

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\src\Mushcore\MushcoreBison.h
# End Source File
# Begin Source File

SOURCE=..\src\Mushcore\MushcoreBisonDefs.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Mushcore\MushcoreBisonDefs.h
# End Source File
# Begin Source File

SOURCE=..\src\Mushcore\MushcoreBuiltinHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Mushcore\MushcoreBuiltinHandler.h
# End Source File
# Begin Source File

SOURCE=..\src\Mushcore\MushcoreCommand.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Mushcore\MushcoreCommand.h
# End Source File
# Begin Source File

SOURCE=..\src\Mushcore\MushcoreCommandHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Mushcore\MushcoreCommandHandler.h
# End Source File
# Begin Source File

SOURCE=..\src\Mushcore\MushcoreConfig.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Mushcore\MushcoreConfig.h
# End Source File
# Begin Source File

SOURCE=..\src\Mushcore\MushcoreData.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Mushcore\MushcoreData.h
# End Source File
# Begin Source File

SOURCE=..\src\Mushcore\MushcoreDataRef.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Mushcore\MushcoreDataRef.h
# End Source File
# Begin Source File

SOURCE=..\src\Mushcore\MushcoreEnv.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Mushcore\MushcoreEnv.h
# End Source File
# Begin Source File

SOURCE=..\src\Mushcore\MushcoreEnvOutput.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Mushcore\MushcoreEnvOutput.h
# End Source File
# Begin Source File

SOURCE=..\src\Mushcore\MushcoreFail.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Mushcore\MushcoreFail.h
# End Source File
# Begin Source File

SOURCE=..\src\Mushcore\MushcoreFlex.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Mushcore\MushcoreFlex.h
# End Source File
# Begin Source File

SOURCE=..\src\Mushcore\MushcoreFunction.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Mushcore\MushcoreFunction.h
# End Source File
# Begin Source File

SOURCE=..\src\Mushcore\MushcoreGlobalConfig.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Mushcore\MushcoreGlobalConfig.h
# End Source File
# Begin Source File

SOURCE=..\src\Mushcore\MushcoreHistory.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Mushcore\MushcoreHistory.h
# End Source File
# Begin Source File

SOURCE=..\src\Mushcore\MushcoreInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Mushcore\MushcoreInfo.h
# End Source File
# Begin Source File

SOURCE=..\src\Mushcore\MushcoreInstaller.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Mushcore\MushcoreInstaller.h
# End Source File
# Begin Source File

SOURCE=..\src\Mushcore\MushcoreInterpreter.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Mushcore\MushcoreInterpreter.h
# End Source File
# Begin Source File

SOURCE=..\src\Mushcore\MushcoreParamList.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Mushcore\MushcoreParamList.h
# End Source File
# Begin Source File

SOURCE=..\src\Mushcore\MushcorePickle.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Mushcore\MushcorePickle.h
# End Source File
# Begin Source File

SOURCE=..\src\Mushcore\MushcoreRegExp.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Mushcore\MushcoreRegExp.h
# End Source File
# Begin Source File

SOURCE=..\src\Mushcore\MushcoreScalar.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Mushcore\MushcoreScalar.h
# End Source File
# Begin Source File

SOURCE=..\src\Mushcore\MushcoreScript.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Mushcore\MushcoreScript.h
# End Source File
# Begin Source File

SOURCE=..\src\Mushcore\MushcoreSingleton.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Mushcore\MushcoreSingleton.h
# End Source File
# Begin Source File

SOURCE=..\src\Mushcore\MushcoreStandard.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Mushcore\MushcoreStandard.h
# End Source File
# Begin Source File

SOURCE=..\src\Mushcore\MushcoreSTL.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Mushcore\MushcoreSTL.h
# End Source File
# Begin Source File

SOURCE=..\src\Mushcore\MushcoreStreamUtil.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Mushcore\MushcoreStreamUtil.h
# End Source File
# Begin Source File

SOURCE=..\src\Mushcore\MushcoreSwitches.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Mushcore\MushcoreSwitches.h
# End Source File
# Begin Source File

SOURCE=..\src\Mushcore\MushcoreUninstaller.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Mushcore\MushcoreUninstaller.h
# End Source File
# Begin Source File

SOURCE=..\src\Mushcore\MushcoreUtil.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Mushcore\MushcoreUtil.h
# End Source File
# Begin Source File

SOURCE=..\src\Mushcore\MushcoreXML.cpp
# End Source File
# Begin Source File

SOURCE=..\src\Mushcore\MushcoreXML.h
# End Source File
# End Target
# End Project
