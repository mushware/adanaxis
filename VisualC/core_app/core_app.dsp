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

# Begin Source File

SOURCE=..\..\src\MushMesh\MushMeshSTL.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\MushMesh\MushMeshSTL.h
# End Source File
# Begin Source File

SOURCE=..\..\src\MushMesh\MushMeshVector.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\MushMesh\MushMeshVector.h
# End Source File
# End Target
# End Project
