# Microsoft Developer Studio Project File - Name="core_app" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

CFG=core_app - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "core_app.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "core_app.mak" CFG="core_app - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "core_app - Win32 Release" (based on "Win32 (x86) External Target")
!MESSAGE "core_app - Win32 Debug" (based on "Win32 (x86) External Target")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "core_app - Win32 Release"

# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Cmd_Line "NMAKE /f core_app.mak"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "core_app.exe"
# PROP BASE Bsc_Name "core_app.bsc"
# PROP BASE Target_Dir ""
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Cmd_Line "NMAKE /f core_app.mak"
# PROP Rebuild_Opt "/a"
# PROP Target_File "core_app.exe"
# PROP Bsc_Name "core_app.bsc"
# PROP Target_Dir ""

!ELSEIF  "$(CFG)" == "core_app - Win32 Debug"

# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Cmd_Line "NMAKE /f core_app.mak"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "core_app.exe"
# PROP BASE Bsc_Name "core_app.bsc"
# PROP BASE Target_Dir ""
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Cmd_Line "C:\cygwin\home\mushware\core-app\VisualC\core_app.bat"
# PROP Rebuild_Opt "/a"
# PROP Target_File "core_app.exe"
# PROP Bsc_Name "core_app.bsc"
# PROP Target_Dir ""

!ENDIF 

# Begin Target

# Name "core_app - Win32 Release"
# Name "core_app - Win32 Debug"

!IF  "$(CFG)" == "core_app - Win32 Release"

!ELSEIF  "$(CFG)" == "core_app - Win32 Debug"

!ENDIF 

# Begin Group "TestMushMesh"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\src\TestMushMesh\TestMushMeshApp.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\TestMushMesh\TestMushMeshApp.h
# End Source File
# Begin Source File

SOURCE=..\..\src\TestMushMesh\TestMushMeshArray.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\TestMushMesh\TestMushMeshArray.h
# End Source File
# Begin Source File

SOURCE=..\..\src\TestMushMesh\TestMushMeshBox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\TestMushMesh\TestMushMeshBox.h
# End Source File
# Begin Source File

SOURCE=..\..\src\TestMushMesh\TestMushMeshMain.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\TestMushMesh\TestMushMeshMain.h
# End Source File
# Begin Source File

SOURCE=..\..\src\TestMushMesh\TestMushMeshStandard.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\TestMushMesh\TestMushMeshStandard.h
# End Source File
# Begin Source File

SOURCE=..\..\src\TestMushMesh\TestMushMeshSubdivide.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\TestMushMesh\TestMushMeshSubdivide.h
# End Source File
# Begin Source File

SOURCE=..\..\src\TestMushMesh\TestMushMeshUtils.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\TestMushMesh\TestMushMeshUtils.h
# End Source File
# Begin Source File

SOURCE=..\..\src\TestMushMesh\TestMushMeshVector.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\TestMushMesh\TestMushMeshVector.h
# End Source File
# End Group
# Begin Group "MushMesh"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\src\MushMesh\MushMesh.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\MushMesh\MushMesh.h
# End Source File
# Begin Source File

SOURCE=..\..\src\MushMesh\MushMeshArray.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\MushMesh\MushMeshArray.h
# End Source File
# Begin Source File

SOURCE=..\..\src\MushMesh\MushMeshBox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\MushMesh\MushMeshBox.h
# End Source File
# Begin Source File

SOURCE=..\..\src\MushMesh\MushMeshMath.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\MushMesh\MushMeshMath.h
# End Source File
# Begin Source File

SOURCE=..\..\src\MushMesh\MushMeshPatch.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\MushMesh\MushMeshPatch.h
# End Source File
# Begin Source File

SOURCE=..\..\src\MushMesh\MushMeshPatchPipe.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\MushMesh\MushMeshPatchPipe.h
# End Source File
# Begin Source File

SOURCE=..\..\src\MushMesh\MushMeshStandard.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\MushMesh\MushMeshStandard.h
# End Source File
# Begin Source File

SOURCE=..\..\src\MushMesh\MushMeshSTL.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\MushMesh\MushMeshSTL.h
# End Source File
# Begin Source File

SOURCE=..\..\src\MushMesh\MushMeshSubdivide.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\MushMesh\MushMeshSubdivide.h
# End Source File
# Begin Source File

SOURCE=..\..\src\MushMesh\MushMeshUtils.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\MushMesh\MushMeshUtils.h
# End Source File
# Begin Source File

SOURCE=..\..\src\MushMesh\MushMeshVector.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\MushMesh\MushMeshVector.h
# End Source File
# End Group
# Begin Group "Mushcore"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\src\Mushcore\Mushcore.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\Mushcore\Mushcore.h
# End Source File
# Begin Source File

SOURCE=..\..\src\Mushcore\MushcoreAbstractSingleton.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\Mushcore\MushcoreAbstractSingleton.h
# End Source File
# Begin Source File

SOURCE=..\..\src\Mushcore\MushcoreAppHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\Mushcore\MushcoreAppHandler.h
# End Source File
# Begin Source File

SOURCE=..\..\src\Mushcore\MushcoreAppSignal.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\Mushcore\MushcoreAppSignal.h
# End Source File
# Begin Source File

SOURCE=..\..\src\Mushcore\MushcoreAutoMonkey.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\Mushcore\MushcoreAutoMonkey.h
# End Source File
# Begin Source File

SOURCE=..\..\src\Mushcore\MushcoreBison.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\Mushcore\MushcoreBison.h
# End Source File
# Begin Source File

SOURCE=..\..\src\Mushcore\MushcoreBisonDefs.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\Mushcore\MushcoreBisonDefs.h
# End Source File
# Begin Source File

SOURCE=..\..\src\Mushcore\MushcoreBuiltinHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\Mushcore\MushcoreBuiltinHandler.h
# End Source File
# Begin Source File

SOURCE=..\..\src\Mushcore\MushcoreCommand.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\Mushcore\MushcoreCommand.h
# End Source File
# Begin Source File

SOURCE=..\..\src\Mushcore\MushcoreCommandHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\Mushcore\MushcoreCommandHandler.h
# End Source File
# Begin Source File

SOURCE=..\..\src\Mushcore\MushcoreConfig.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\Mushcore\MushcoreConfig.h
# End Source File
# Begin Source File

SOURCE=..\..\src\Mushcore\MushcoreData.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\Mushcore\MushcoreData.h
# End Source File
# Begin Source File

SOURCE=..\..\src\Mushcore\MushcoreDataRef.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\Mushcore\MushcoreDataRef.h
# End Source File
# Begin Source File

SOURCE=..\..\src\Mushcore\MushcoreEnv.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\Mushcore\MushcoreEnv.h
# End Source File
# Begin Source File

SOURCE=..\..\src\Mushcore\MushcoreEnvOutput.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\Mushcore\MushcoreEnvOutput.h
# End Source File
# Begin Source File

SOURCE=..\..\src\Mushcore\MushcoreFactory.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\Mushcore\MushcoreFactory.h
# End Source File
# Begin Source File

SOURCE=..\..\src\Mushcore\MushcoreFail.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\Mushcore\MushcoreFail.h
# End Source File
# Begin Source File

SOURCE=..\..\src\Mushcore\MushcoreFlex.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\Mushcore\MushcoreFlex.h
# End Source File
# Begin Source File

SOURCE=..\..\src\Mushcore\MushcoreFunction.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\Mushcore\MushcoreFunction.h
# End Source File
# Begin Source File

SOURCE=..\..\src\Mushcore\MushcoreGlobalConfig.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\Mushcore\MushcoreGlobalConfig.h
# End Source File
# Begin Source File

SOURCE=..\..\src\Mushcore\MushcoreHistory.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\Mushcore\MushcoreHistory.h
# End Source File
# Begin Source File

SOURCE=..\..\src\Mushcore\MushcoreInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\Mushcore\MushcoreInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\src\Mushcore\MushcoreInstaller.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\Mushcore\MushcoreInstaller.h
# End Source File
# Begin Source File

SOURCE=..\..\src\Mushcore\MushcoreInterpreter.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\Mushcore\MushcoreInterpreter.h
# End Source File
# Begin Source File

SOURCE=..\..\src\Mushcore\MushcoreIO.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\Mushcore\MushcoreIO.h
# End Source File
# Begin Source File

SOURCE=..\..\src\Mushcore\MushcoreObject.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\Mushcore\MushcoreObject.h
# End Source File
# Begin Source File

SOURCE=..\..\src\Mushcore\MushcoreParamList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\Mushcore\MushcoreParamList.h
# End Source File
# Begin Source File

SOURCE=..\..\src\Mushcore\MushcorePickle.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\Mushcore\MushcorePickle.h
# End Source File
# Begin Source File

SOURCE=..\..\src\Mushcore\MushcoreRegExp.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\Mushcore\MushcoreRegExp.h
# End Source File
# Begin Source File

SOURCE=..\..\src\Mushcore\MushcoreScalar.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\Mushcore\MushcoreScalar.h
# End Source File
# Begin Source File

SOURCE=..\..\src\Mushcore\MushcoreScript.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\Mushcore\MushcoreScript.h
# End Source File
# Begin Source File

SOURCE=..\..\src\Mushcore\MushcoreSingleton.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\Mushcore\MushcoreSingleton.h
# End Source File
# Begin Source File

SOURCE=..\..\src\Mushcore\MushcoreStandard.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\Mushcore\MushcoreStandard.h
# End Source File
# Begin Source File

SOURCE=..\..\src\Mushcore\MushcoreSTL.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\Mushcore\MushcoreSTL.h
# End Source File
# Begin Source File

SOURCE=..\..\src\Mushcore\MushcoreStreamUtil.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\Mushcore\MushcoreStreamUtil.h
# End Source File
# Begin Source File

SOURCE=..\..\src\Mushcore\MushcoreSwitches.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\Mushcore\MushcoreSwitches.h
# End Source File
# Begin Source File

SOURCE=..\..\src\Mushcore\MushcoreUninstaller.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\Mushcore\MushcoreUninstaller.h
# End Source File
# Begin Source File

SOURCE=..\..\src\Mushcore\MushcoreUtil.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\Mushcore\MushcoreUtil.h
# End Source File
# Begin Source File

SOURCE=..\..\src\Mushcore\MushcoreVirtualObject.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\Mushcore\MushcoreVirtualObject.h
# End Source File
# Begin Source File

SOURCE=..\..\src\Mushcore\MushcoreXML.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\Mushcore\MushcoreXML.h
# End Source File
# Begin Source File

SOURCE=..\..\src\Mushcore\MushcoreXMLIStream.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\Mushcore\MushcoreXMLIStream.h
# End Source File
# Begin Source File

SOURCE=..\..\src\Mushcore\MushcoreXMLOStream.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\Mushcore\MushcoreXMLOStream.h
# End Source File
# Begin Source File

SOURCE=..\..\src\Mushcore\MushcoreXMLStream.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\Mushcore\MushcoreXMLStream.h
# End Source File
# End Group
# Begin Group "Scripts"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\app.Makefile.am
# End Source File
# Begin Source File

SOURCE=..\..\autogen.sh
# End Source File
# Begin Source File

SOURCE=..\..\configure.in
# End Source File
# Begin Source File

SOURCE=..\..\ic2.configure.in
# End Source File
# Begin Source File

SOURCE=..\..\slog.configure.in
# End Source File
# Begin Source File

SOURCE=..\..\SourceConditioner.pl
# End Source File
# Begin Source File

SOURCE=..\..\SourceProcess.pm
# End Source File
# End Group
# End Target
# End Project
