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

Name "Tesseract Trainer"
OutFile "tesseracttrainer-win32-0.1.2.exe"
SetCompressor lzma

  !define MUI_ABORTWARNING

  !define MUI_FINISHPAGE_RUN
  !define MUI_FINISHPAGE_RUN_TEXT "Create shortcut on desktop"
  !define MUI_FINISHPAGE_RUN_FUNCTION desktopCreate

  !insertmacro MUI_PAGE_WELCOME
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
CreateShortCut "$DESKTOP\Tesseract Trainer.lnk" "$OUTDIR\tesseracttrainer.exe" 
FunctionEnd

; LicenseText "You should at least read the WARRANTY line of this licence before installing."
; LicenseData "LICENCE"

VIAddVersionKey "ProductName" "Tesseract Trainer"
VIAddVersionKey "CompanyName" "Mushware Limited"
VIAddVersionKey "LegalCopyright" "©Mushware Limited and Andy Southgate"
VIAddVersionKey "FileVersion" "0.1.2"
VIAddVersionKey "FileDescription" "Mushware software installer.  See http://www.mushware.com/."
VIProductVersion "0.0.1.2"

Icon tesseracttrainer_inst_app.ico
UninstallIcon tesseracttrainer_uninst_app.ico

InstallDir "$PROGRAMFILES\Tesseract Trainer"
InstallDirRegKey HKEY_LOCAL_MACHINE "SOFTWARE\Mushware Limited\Tesseract Trainer" ""
; DirShow show ; (make this hide to not let the user change it)
DirText "Select the directory to install Tesseract Trainer in:"

Section "" ; (default section)
SetOutPath "$INSTDIR"
File /r "..\release\Tesseract Trainer\*.*"

WriteRegStr HKEY_LOCAL_MACHINE "SOFTWARE\Mushware Limited\Tesseract Trainer" "" "$INSTDIR"
WriteRegStr HKEY_LOCAL_MACHINE "Software\Microsoft\Windows\CurrentVersion\Uninstall\Tesseract Trainer" "DisplayName" "Tesseract Trainer"
WriteRegStr HKEY_LOCAL_MACHINE "Software\Microsoft\Windows\CurrentVersion\Uninstall\Tesseract Trainer" "UninstallString" '"$INSTDIR\Uninstall Tesseract Trainer.exe"'

SetOutPath "$INSTDIR\system"
CreateShortCut "$INSTDIR\Tesseract Trainer.lnk" "$OUTDIR\tesseracttrainer.exe" 
CreateShortCut "$INSTDIR\Tesseract Trainer (Safe Mode).lnk" "$OUTDIR\tesseracttrainer.exe" "load('start_safe.txt')"

CreateDirectory "$STARTMENU\Programs\Tesseract Trainer"
CreateShortCut "$STARTMENU\Programs\Tesseract Trainer\Tesseract Trainer.lnk" "$OUTDIR\tesseracttrainer.exe"
CreateShortCut "$STARTMENU\Programs\Tesseract Trainer\Tesseract Trainer (Safe Mode).lnk" "$OUTDIR\tesseracttrainer.exe" "load('start_safe.txt')"

CreateShortCut "$STARTMENU\Programs\Tesseract Trainer\Uninstall Tesseract Trainer.lnk" "$INSTDIR\Uninstall Tesseract Trainer.exe"
CreateShortCut "$STARTMENU\Programs\Tesseract Trainer\About Tesseract Trainer.lnk" "$INSTDIR\About Tesseract Trainer.pdf"
CreateShortCut "$STARTMENU\Programs\Tesseract Trainer\Explore Tesseract Trainer Files.lnk" "$INSTDIR\"
CreateShortCut "$STARTMENU\Programs\Tesseract Trainer\Mushware web site.lnk" "$INSTDIR\Mushware web site.url"

SetOutPath "$INSTDIR"

; write out uninstaller
WriteUninstaller "$INSTDIR\Uninstall Tesseract Trainer.exe"
SectionEnd ; end of default section

; begin uninstall settings/section
UninstallText "This will uninstall Tesseract Trainer from your system"

Section Uninstall
; add delete commands to delete whatever files/registry keys/etc you installed here.
Delete "$INSTDIR\Uninstall tesseracttrainer.exe"
DeleteRegKey HKEY_LOCAL_MACHINE "SOFTWARE\Mushware Limited\Tesseract Trainer"
DeleteRegKey HKEY_LOCAL_MACHINE "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\Tesseract Trainer"
RMDir /r "$INSTDIR"
Delete "$STARTMENU\Programs\Tesseract Trainer\Tesseract Trainer.lnk"
Delete "$STARTMENU\Programs\Tesseract Trainer\Tesseract Trainer (Safe Mode).lnk"
Delete "$STARTMENU\Programs\Tesseract Trainer\Uninstall Tesseract Trainer.lnk"
Delete "$STARTMENU\Programs\Tesseract Trainer\About Tesseract Trainer.lnk"
Delete "$STARTMENU\Programs\Tesseract Trainer\Explore Tesseract Trainer Files.lnk"
Delete "$STARTMENU\Programs\Tesseract Trainer\Mushware web site.lnk"

Delete "$DESKTOP\Tesseract Trainer.lnk"
RmDir "$STARTMENU\Programs\Tesseract Trainer"

SectionEnd ; end of uninstall section

; eof

