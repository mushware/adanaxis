; $Id: installer.nsi,v 1.3 2002/06/25 18:05:49 southa Exp $
; $Log: installer.nsi,v $
; Revision 1.3  2002/06/25 18:05:49  southa
; Path and icon fixes
;
; Revision 1.2  2002/06/13 15:53:20  southa
; More work
;

; NOTE: this .NSI script is designed for NSIS v1.8+

Name "Infernal Contractor II"
OutFile "IC2setup.exe"

LicenseText "You must agree to this licence before installing."
LicenseData "..\LICENCE"

; Some default compiler settings (uncomment and change at will):
; SetCompress auto ; (can be off or force)
; SetDatablockOptimize on ; (can be off)
; CRCCheck on ; (can be off)
; AutoCloseWindow false ; (can be true for the window go away automatically at end)
; ShowInstDetails hide ; (can be show to have them shown, or nevershow to disable)
; SetDateSave off ; (can be on to have files restored to their orginal date)

InstallDir "$PROGRAMFILES\Infernal Contractor II"
InstallDirRegKey HKEY_LOCAL_MACHINE "SOFTWARE\Mushware Limited\Infernal Contractor II" ""
DirShow show ; (make this hide to not let the user change it)
DirText "Select the directory to install Infernal Contractor II in:"

Section "" ; (default section)
SetOutPath "$INSTDIR"
CreateDirectory "$OUTDIR/system"
; add files / whatever that need to be installed here.
GetDLLVersion glut32 $R1 $R2
IfErrors err1 noerr1
err1:
File /oname=$OUTDIR\system\glut32.dll win32libs\glut32.dll
noerr1:

GetDLLVersion libexpat $R1 $R2
IfErrors err2 noerr2
err2:
File /oname=$OUTDIR\system\libexpat.dll win32libs\libexpat.dll
noerr2:

GetDLLVersion libjpeg $R1 $R2
IfErrors err3 noerr3
err3:
File /oname=$OUTDIR\system\libjpeg.dll win32libs\libjpeg.dll
noerr3:

GetDLLVersion libtiff $R1 $R2
IfErrors err4 noerr4
err4:
File /oname=$OUTDIR\system\libtiff.dll win32libs\libtiff.dll
noerr4:

GetDLLVersion libungif $R1 $R2
IfErrors err5 noerr5
err5:
File /oname=$OUTDIR\system\libungif.dll win32libs\libungif.dll
noerr5:

GetDLLVersion pcre $R1 $R2
IfErrors err6 noerr6
err6:
File /oname=$OUTDIR\system\pcre.dll win32libs\pcre.dll
noerr6:

GetDLLVersion SDL $R1 $R2
IfErrors err7 noerr7
err7:
File /oname=$OUTDIR\system\SDL.dll win32libs\SDL.dll
noerr7:

GetDLLVersion SDL_mixer $R1 $R2
IfErrors err8 noerr8
err8:
File /oname=$OUTDIR\system\SDL_mixer.dll win32libs\SDL_mixer.dll
noerr8:

GetDLLVersion smpeg $R1 $R2
IfErrors err9 noerr9
err9:
File /oname=$OUTDIR\system\smpeg.dll win32libs\smpeg.dll
noerr9:

GetDLLVersion zlib $R1 $R2
IfErrors err10 noerr10
err10:
File /oname=$OUTDIR\system\zlib.dll win32libs\zlib.dll
noerr10:

File /oname=$OUTDIR\system\COPYING ..\COPYING
File /r ..\release\*.*

WriteRegStr HKEY_LOCAL_MACHINE "SOFTWARE\Mushware Limited\Infernal Contractor II" "" "$INSTDIR"
WriteRegStr HKEY_LOCAL_MACHINE "Software\Microsoft\Windows\CurrentVersion\Uninstall\Infernal Contractor II" "DisplayName" "Infernal Contractor II"
WriteRegStr HKEY_LOCAL_MACHINE "Software\Microsoft\Windows\CurrentVersion\Uninstall\Infernal Contractor II" "UninstallString" '"$INSTDIR\uninst.exe"'

SetOutPath "$INSTDIR\system"
CreateShortCut "$DESKTOP\Infernal Contractor II.lnk" "$OUTDIR\contractor.exe" "" "$OUTDIR\ic2_app.ico" 0
CreateShortCut "$INSTDIR\Infernal Contractor II.lnk" "$OUTDIR\contractor.exe" "" "$OUTDIR\ic2_app.ico" 0
CreateDirectory "$STARTMENU\Programs\Mushware"
CreateShortCut "$STARTMENU\Programs\Mushware\Infernal Contractor II.lnk" "$OUTDIR\contractor.exe" "" "$OUTDIR\ic2_app.ico" 
CreateShortCut "$STARTMENU\Programs\Mushware\Uninstall Infernal Contractor II.lnk" "$INSTDIR\uninst.exe"
SetOutPath "$INSTDIR"

; write out uninstaller
WriteUninstaller "$INSTDIR\uninst.exe"
SectionEnd ; end of default section


; begin uninstall settings/section
UninstallText "This will uninstall Infernal Contractor II from your system"

Section Uninstall
; add delete commands to delete whatever files/registry keys/etc you installed here.
Delete "$INSTDIR\uninst.exe"
DeleteRegKey HKEY_LOCAL_MACHINE "SOFTWARE\Mushware Limited\Infernal Contractor II"
DeleteRegKey HKEY_LOCAL_MACHINE "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\Infernal Contractor II"
RMDir /r "$INSTDIR"
Delete "$DESKTOP\Infernal Contractor II.lnk"
Delete "$STARTMENU\Programs\Mushware\Infernal Contractor II.lnk"
Delete "$STARTMENU\Programs\Mushware\Uninstall Infernal Contractor II.lnk"
FindFirst $R1 $R2 "$STARTMENU\Programs\Mushware\*.lnk"
IfErrors err20 noerr20
err20:
RmDir "$STARTMENU\Programs\Mushware"
noerr20:
FindClose $R1
SectionEnd ; end of uninstall section

; eof

