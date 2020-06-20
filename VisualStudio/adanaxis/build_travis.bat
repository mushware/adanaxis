
START "" /B /D "VisualStudio\adanaxis" /WAIT powershell.exe -ExecutionPolicy Bypass -NonInteractive -NoProfile -File build_travis.ps1 "%BUILD_CONFIGURATION%" -InstallWix
EXIT /B %ERRORLEVEL%
