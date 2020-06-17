

powershell.exe -NonInteractive -NoProfile -ExecutionPolicy Bypass -Command scripts/GetWindowsDeps.ps1

SET "PATH=C:\Program Files (x86)\Microsoft Visual Studio\2017\BuildTools\MSBuild\15.0\Bin;%PATH%"
CD "VisualStudio\adanaxis"
MSBuild adanaxis.sln
