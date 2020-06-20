
START "" /B /D "VisualStudio\adanaxis" /WAIT powershell.exe -ExecutionPolicy Bypass -NonInteractive -NoProfile -File build.ps1 "%BUILD_CONFIGURATION%" "%TRAVIS_BUILD_NUMBER%" -InstallWix
EXIT /B %ERRORLEVEL%
