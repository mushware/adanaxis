#%Header {
##############################################################################
#
# File VisualStudio/adanaxis/build.ps1
#
# Copyright: Andy Southgate 2002-2007, 2020
#
# Permission is hereby granted, free of charge, to any person obtaining a
# copy of this software and associated documentation files (the "Software"),
# to deal in the Software without restriction, including without limitation
# the rights to use, copy, modify, merge, publish, distribute, sublicense,
# and/or sell copies of the Software, and to permit persons to whom the
# Software is furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
# DEALINGS IN THE SOFTWARE.
#
##############################################################################
#%Header } Qr5Vw09MMnMYlaXKb6VQrA

Param(
    [Parameter(Mandatory)]$Configuration,
    [Parameter(Mandatory)]$BuildNumber,
    [Parameter(Mandatory=$false)][Switch]$InstallMissing
)

Set-StrictMode -Version 3.0

$ErrorActionPreference = "Stop"

$DepsVersion = "0.0.4.16"

If ($BuildNumber) {
    If ($BuildNumber -as [int] -gt 65534) {
        Throw "Build number too large"
    }
    $Version = "1.4.0.$BuildNumber"
    If ($env:TRAVIS_TAG) {
        If ($env:TRAVIS_TAG -match "^v\d+\.\d+\.\d+$") {
            $Version = "$($env:TRAVIS_TAG.Substring(1)).$BuildNumber"
        } Else {
            Write-Error "Badly formed or non-release git tag ""$($env:TRAVIS_TAG)"""
        }
    } else {
    }
} Else {
    $Version = "0.0.0.0"
}

Write-Host -ForegroundColor Blue @"
*
*
* Beginning Adanaxis $Configuration build for version $Version with deps $DepsVersion.
*
*
"@

Write-Host "Path is:"
Get-ChildItem env:PATH | ForEach-Object { $_.Value.Split(';') }

If ($Configuration -eq "") {
    Write-Host "Configuration not supplied so using Debug"
    $Configuration = "Debug"
}

if ($PSScriptRoot) {
    $ProjectRoot = $(Join-Path -Resolve $PSScriptRoot -ChildPath "..\..")
} Else {
    $ProjectRoot = $(Join-Path -Resolve $pwd -ChildPath "..\..")
}
$AdanaxisBuildRoot = $(Join-Path -Resolve $ProjectRoot -ChildPath "VisualStudio\adanaxis")
$SpdlogRoot = $(Join-Path -Resolve $ProjectRoot -ChildPath "spdlog")
$SpdlogBuildRoot = $(Join-Path $SpdlogRoot -ChildPath "build")
Set-Location $AdanaxisBuildRoot

$cmake_root="C:\Program Files\CMake\bin"
$msbuild_root="C:\Program Files (x86)\Microsoft Visual Studio\2017\BuildTools\MSBuild\15.0\Bin"
$signtool_root="C:\Program Files (x86)\Windows Kits\10\bin\10.0.18362.0\x86"
$wix_root="C:\Program Files (x86)\WiX Toolset v3.11\bin"

If (Test-Path $wix_root) {
    Write-Host "WiX already installed."
    $wix_job = Start-Job -ScriptBlock { Write-Output "(output from null install job) WiX already installed" }
} Else {
    If ($InstallMissing) {
        Write-Host "Launching job to install WiX."
        $wix_job = Start-Job -File "./install_wix.ps1"
    } Else {
        Throw "WiX not found but cannot install, please install or supply -InstallMissing as a parameter."
    }
}

Write-Host "Launching job to get deps."
$getdeps_job = Start-Job -Init ([ScriptBlock]::Create("Set-Location '$pwd'")) -File "./get_adanaxis_deps.ps1" -ArgumentList $Configuration, $DepsVersion

$env:PATH = "$msbuild_root;$wix_root;$signtool_root;$cmake_root;$env:PATH"

Write-Host "Path for build is:"
Get-ChildItem env:PATH | ForEach-Object { $_.Value.Split(';') }

If ($null -eq (Get-Command -ErrorAction SilentlyContinue cmake)) {
    Throw "CMake not installed, use e.g. choco install --yes cmake.install --version 3.16.2"
}

Write-Host -ForegroundColor DarkCyan @"

********************************************
*                                          *
*    Building spdlog library               *
*    Props to https://github.com/gabime    *
*                                          *
********************************************

"@

New-Item -ItemType "directory" -Path $SpdlogBuildRoot -Force | Foreach-Object { "Created directory $($_.FullName)" }

Set-Location $SpdlogBuildRoot
$spdlog_cmake_process = Start-Process -NoNewWindow -PassThru -FilePath "cmake.exe" -ArgumentList "-A", "Win32", "-G", "`"Visual Studio 15 2017`"", ".."
$handle = $spdlog_cmake_process.Handle # Fix for missing ExitCode
$spdlog_cmake_process.WaitForExit()

if ($spdlog_cmake_process.ExitCode -ne 0) {
    throw "Spdlog CMake failed ($($spdlog_cmake_process.ExitCode))"
}

Set-Location $SpdlogRoot

$spdlog_build_process = Start-Process -NoNewWindow -PassThru -FilePath "MSBuild.exe" -ArgumentList "build\spdlog.sln", "-maxCpuCount", "-nodeReuse:false", "-target:spdlog", "-property:UseSharedCompilation=false"
$handle = $spdlog_build_process.Handle # Fix for missing ExitCode
$spdlog_build_process.WaitForExit()

if ($spdlog_build_process.ExitCode -ne 0) {
    throw "Spdlog make failed ($($spdlog_build_process.ExitCode))"
}

Write-Host -ForegroundColor DarkCyan @"

********************************************
*                                          *
*    Starting Adanaxis dependency setup    *
*                                          *
********************************************

"@

# Need to wait for dependencies before Adanaxis build
Set-Location $AdanaxisBuildRoot
Write-Host -ForegroundColor DarkCyan "Waiting for dependency fetch job..."
Receive-Job -Job $getdeps_job -Wait
Write-Host -ForegroundColor DarkCyan "Waiting for WiX installation job..."
Receive-Job -Job $wix_job -Wait

Write-Host -ForegroundColor DarkCyan @"

**************************************
*                                    *
*    Starting Adanaxis main build    *
*                                    *
**************************************

"@

Set-Location $AdanaxisBuildRoot

$build_process = Start-Process -NoNewWindow -PassThru -FilePath "MSBuild.exe" -ArgumentList "adanaxis.sln", "-maxCpuCount", "-nodeReuse:false", "-target:adanaxis", "-property:Configuration=`"$Configuration`"", "-property:Version=`"$Version`""
$handle = $build_process.Handle # Fix for missing ExitCode
$build_process.WaitForExit()

if ($build_process.ExitCode -ne 0) {
    throw "Build failed ($($build_process.ExitCode))"   
}

Write-Host "Output of previous WiX install job:"
Receive-Job -Job $wix_job -Wait

$installer_log_filename = "install.log"
$install_process = Start-Process -NoNewWindow -PassThru -FilePath "cmd.exe" -ArgumentList  "/Cmsiexec.exe", "/lv*", $installer_log_filename, "/q", "/i", "msi\$Configuration\Adanaxis.msi"
$handle = $install_process.Handle # Fix for missing ExitCode
$install_process.WaitForExit()

if ($install_process.ExitCode -ne 0) {
    Write-Host "Installation failed.  Log dump:"
    Get-Content $installer_log_filename | Write-Host
    throw "Installer failed"   
}
Write-Host "Installation successful.  Package details:"
Get-Package "Adanaxis" | Select-Object *
Uninstall-Package "Adanaxis" | ForEach-Object { Write-Host "Uninstall successful, $($_ | Select-Object Status)" }

$underscore_version = $Version.Replace(".", "_")
If ($Configuration -eq "Debug") {
    Rename-Item "msi\${Configuration}\Adanaxis.msi" "Adanaxis_Debug_${underscore_version}.msi"
} Else {
    Rename-Item "msi\${Configuration}\Adanaxis.msi" "Adanaxis_${underscore_version}.msi"
}
Write-Host -ForegroundColor Green @"

**************************
*                        *
*    BUILD SUCCESSFUL    *
*                        *
**************************

"@

Write-Host -ForegroundColor Blue "$Configuration build complete for Adanaxis version $Version with deps $DepsVersion"
