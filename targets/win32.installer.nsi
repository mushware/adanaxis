; $Id: installer.nsi,v 1.12 2003/04/30 20:28:47 southa Exp $
; $Log: installer.nsi,v $
; Revision 1.12  2003/04/30 20:28:47  southa
; Removed win32 licence
;
; Revision 1.11  2002/11/24 10:26:14  southa
; Added SDL_net
;
; Revision 1.10  2002/10/20 22:31:06  southa
; Fixed win32 release build
;
; Revision 1.9  2002/08/27 13:18:11  southa
; Fixed line endings in LICENCE file
;
; Revision 1.8  2002/08/07 11:48:23  southa
; Preparation for release 0.0.3
;
; Revision 1.7  2002/08/07 10:47:44  southa
; Preparation for release 0.0.3
;
; Revision 1.6  2002/07/16 17:53:48  southa
; Added ReadMe file link
;
; Revision 1.5  2002/06/27 13:34:05  southa
; Fixed path to executable
;
; Revision 1.4  2002/06/26 15:52:27  southa
; Licence fixes
;
; Revision 1.3  2002/06/25 18:05:49  southa
; Path and icon fixes
;
; Revision 1.2  2002/06/13 15:53:20  southa
; More work
;

; NOTE: this .NSI script is designed for NSIS v2.0.6+

  !include "MUI.nsh"

Name "@NSI_APP_NAME@"
OutFile "@NSI_OUTFILE@"
SetCompressor lzma

  !define MUI_ABORTWARNING

  !define MUI_FINISHPAGE_RUN
  !define MUI_FINISHPAGE_RUN_TEXT "Create shortcut on desktop"
  !define MUI_FINISHPAGE_RUN_FUNCTION desktopCreate

  !insertmacro MUI_PAGE_WELCOME
  !insertmacro MUI_PAGE_LICENSE "..\release\Adanaxis\documents\Licence.txt"
  !insertmacro MUI_PAGE_DIRECTORY
  !insertmacro MUI_PAGE_INSTFILES
  !insertmacro MUI_PAGE_FINISH
    
  !insertmacro MUI_UNPAGE_WELCOME
  !insertmacro MUI_UNPAGE_CONFIRM
  !insertmacro MUI_UNPAGE_INSTFILES
  !insertmacro MUI_UNPAGE_FINISH
  
  !insertmacro MUI_LANGUAGE "English"

Function desktopCreate
SetOutPath "$INSTDIR\system"
CreateShortCut "$DESKTOP\@NSI_APP_NAME@.lnk" "$OUTDIR\MUSH_APP_PACKAGE.exe" 
FunctionEnd

; LicenseText "You should at least read the WARRANTY line of this licence before installing."
; LicenseData "LICENCE"

VIAddVersionKey "ProductName" "@NSI_APP_NAME@"
VIAddVersionKey "CompanyName" "Mushware Limited"
VIAddVersionKey "LegalCopyright" "�Mushware Limited and Andy Southgate"
VIAddVersionKey "FileVersion" "MUSH_APP_VERSION"
VIAddVersionKey "FileDescription" "Mushware software installer.  See http://www.mushware.com/."
VIProductVersion "MUSH_APP_VERSION.0"

Icon icons/MUSH_APP_PACKAGE_inst_app.ico
UninstallIcon icons/MUSH_APP_PACKAGE_uninst_app.ico

InstallDir "$PROGRAMFILES\@NSI_APP_NAME@"
InstallDirRegKey HKEY_LOCAL_MACHINE "SOFTWARE\Mushware Limited\@NSI_APP_NAME@" ""
; DirShow show ; (make this hide to not let the user change it)
DirText "Select the directory to install @NSI_APP_NAME@ in:"

Section "" ; (default section)
SetOutPath "$INSTDIR"

# Autogenerated file list
@INSTFILES@
# End of autogenerated file list

WriteRegStr HKEY_LOCAL_MACHINE "SOFTWARE\Mushware Limited\@NSI_APP_NAME@" "" "$INSTDIR"
WriteRegStr HKEY_LOCAL_MACHINE "Software\Microsoft\Windows\CurrentVersion\Uninstall\@NSI_APP_NAME@" "DisplayName" "@NSI_APP_NAME@"
WriteRegStr HKEY_LOCAL_MACHINE "Software\Microsoft\Windows\CurrentVersion\Uninstall\@NSI_APP_NAME@" "UninstallString" '"$INSTDIR\Uninstall @NSI_APP_NAME@.exe"'

SetOutPath "$INSTDIR\system"
CreateShortCut "$INSTDIR\@NSI_APP_NAME@.lnk" "$OUTDIR\MUSH_APP_PACKAGE.exe" 
CreateShortCut "$INSTDIR\@NSI_APP_NAME@ (Recovery Mode).lnk" "$OUTDIR\MUSH_APP_PACKAGE.exe" "load('start_safe.txt')"

CreateDirectory "$STARTMENU\Programs\@NSI_APP_NAME@"
CreateShortCut "$STARTMENU\Programs\@NSI_APP_NAME@\@NSI_APP_NAME@.lnk" "$OUTDIR\MUSH_APP_PACKAGE.exe"
CreateShortCut "$STARTMENU\Programs\@NSI_APP_NAME@\@NSI_APP_NAME@ (Safe Mode).lnk" "$OUTDIR\MUSH_APP_PACKAGE.exe" "load('start_safe.txt')"

CreateShortCut "$STARTMENU\Programs\@NSI_APP_NAME@\Uninstall @NSI_APP_NAME@.lnk" "$INSTDIR\Uninstall @NSI_APP_NAME@.exe"
CreateShortCut "$STARTMENU\Programs\@NSI_APP_NAME@\About @NSI_APP_NAME@.lnk" "$INSTDIR\About_MUSH_APP_UNDERSCORED_NAME.pdf"
CreateShortCut "$STARTMENU\Programs\@NSI_APP_NAME@\Explore @NSI_APP_NAME@ Files.lnk" "$INSTDIR\"
CreateShortCut "$STARTMENU\Programs\@NSI_APP_NAME@\Mushware web site.lnk" "$INSTDIR\Mushware web site.url"

SetOutPath "$INSTDIR"

; write out uninstaller
WriteUninstaller "$INSTDIR\Uninstall @NSI_APP_NAME@.exe"
SectionEnd ; end of default section

; begin uninstall settings/section
UninstallText "This will uninstall @NSI_APP_NAME@ from your system"

Section Uninstall
; add delete commands to delete whatever files/registry keys/etc you installed here.
DeleteRegKey HKEY_LOCAL_MACHINE "SOFTWARE\Mushware Limited\@NSI_APP_NAME@"
DeleteRegKey HKEY_LOCAL_MACHINE "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\@NSI_APP_NAME@"

Delete "$INSTDIR\@NSI_APP_NAME@.lnk"
Delete "$INSTDIR\@NSI_APP_NAME@ (Safe Mode).lnk"
Delete "$INSTDIR\system\stdout.txt"
Delete "$INSTDIR\system\stderr.txt"
RmDir "$INSTDIR\mushware-cache"

# Autogenerated file list
@UNINSTFILES@
# End of autogenerated file list

Delete "$STARTMENU\Programs\@NSI_APP_NAME@\@NSI_APP_NAME@.lnk"
Delete "$STARTMENU\Programs\@NSI_APP_NAME@\@NSI_APP_NAME@ (Safe Mode).lnk"
Delete "$STARTMENU\Programs\@NSI_APP_NAME@\Uninstall @NSI_APP_NAME@.lnk"
Delete "$STARTMENU\Programs\@NSI_APP_NAME@\About @NSI_APP_NAME@.lnk"
Delete "$STARTMENU\Programs\@NSI_APP_NAME@\Explore @NSI_APP_NAME@ Files.lnk"
Delete "$STARTMENU\Programs\@NSI_APP_NAME@\Mushware web site.lnk"

Delete "$DESKTOP\@NSI_APP_NAME@.lnk"
RmDir "$STARTMENU\Programs\@NSI_APP_NAME@"

Delete "$INSTDIR\Uninstall @NSI_APP_NAME@.exe"

RmDir "$INSTDIR"

SectionEnd ; end of uninstall section

; eof

