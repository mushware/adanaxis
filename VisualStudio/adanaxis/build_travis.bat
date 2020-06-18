
powershell.exe -NonInteractive -NoProfile -ExecutionPolicy Bypass -Command scripts/GetWindowsDeps.ps1

SET "PATH=C:\Program Files (x86)\Microsoft Visual Studio\2017\BuildTools\MSBuild\15.0\Bin;%PATH%"
CD "VisualStudio\adanaxis"
MSBuild.exe adanaxis.sln

SET "WIX_ROOT=C:\Program Files (x86)\WiX Toolset v3.11\bin"

IF NOT EXIST "%WIX_ROOT%" powershell.exe -NonInteractive -NoProfile -ExecutionPolicy Bypass -Command ./install_wix.ps1

SET "PATH=%WIX_ROOT%;%PATH%"

powershell.exe -NonInteractive -NoProfile -ExecutionPolicy Bypass -Command ./build_installer.ps1
