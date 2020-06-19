
CD "VisualStudio\adanaxis"

powershell.exe -ExecutionPolicy Bypass -NonInteractive -NoProfile -File ./GetWindowsDeps.ps1

SET "MSBUILD_ROOT=C:\Program Files (x86)\Microsoft Visual Studio\2017\BuildTools\MSBuild\15.0\Bin"
SET "WIX_ROOT=C:\Program Files (x86)\WiX Toolset v3.11\bin"

IF NOT EXIST "%WIX_ROOT%" powershell.exe -ExecutionPolicy Bypass -NonInteractive -NoProfile -File ./install_wix.ps1

SET "PATH=%WIX_ROOT%;%MSBUILD_ROOT%;%PATH%"

MSBuild.exe adanaxis.sln /t:adanaxis /p:Configuration="Debug"
MSBuild.exe adanaxis.sln /t:adanaxis /p:Configuration="Release"

START /B /WAIT "" msiexec.exe /q /i msi\Release\Adanaxis.msi
powershell.exe -ExecutionPolicy Bypass -NonInteractive -NoProfile -Command "Uninstall-Package Adanaxis"
