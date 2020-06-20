
Param(
    [Parameter(Mandatory)]$Configuration,
    [Parameter(Mandatory)]$BuildNumber,
    [Parameter(Mandatory=$false)][Switch]$InstallWix
)

Set-StrictMode -Version 3.0
$ErrorActionPreference = "Stop"

If ($BuildNumber) {
    If ($BuildNumber -gt 65534) {
        Throw "Build number too large"
    }
    $Version = "1.5.$BuildNumber.0"
} Else {
    $Version = "0.0.0.0"
}

Write-Host -ForegroundColor Blue @"
*
*
* Beginning Adanaxis $Configuration build for version $Version.
*
*

Environment is:

"@

Get-ChildItem env:* | Sort-Object -Property Name

Write-Host "Path is:"
Get-ChildItem env:PATH | ForEach-Object { $_.Value.Split(';') }

If ($Configuration -eq "") {
    Write-Host "Configuration not supplied so using Debug"
    $Configuration = "Debug"
}

if ($PSScriptRoot) {
    Set-Location $PSScriptRoot
}

$getdeps_job = Start-Job -Init ([ScriptBlock]::Create("Set-Location '$pwd'")) -File ./GetWindowsDeps.ps1

$msbuild_root="C:\Program Files (x86)\Microsoft Visual Studio\2017\BuildTools\MSBuild\15.0\Bin"
$wix_root="C:\Program Files (x86)\WiX Toolset v3.11\bin"

If (Test-Path $wix_root) {
    Write-Host "WiX already installed."
    $wix_job = Start-Job -ScriptBlock { Write-Output "(output from null install job) WiX already installed" }
} Else {
    If ($InstallWix) {
        Write-Host "Launching job to install WiX."
        $wix_job = Start-Job -File "./install_wix.ps1"
    } Else {
        Throw "WiX not found but cannot install, please install or supply -InstallWix as a parameter."
    }
}

# Need to wait for dependencies before build, since they supply headers
Receive-Job -Job $getdeps_job -Wait
Receive-Job -Job $wix_job -Wait

$env:PATH = "$wix_root;$msbuild_root;$env:PATH"

$build_process = Start-Process -NoNewWindow -PassThru -Wait -FilePath "MSBuild.exe" -ArgumentList "adanaxis.sln", "/t:adanaxis",  "/p:Configuration=`"$Configuration`"", "/p:Version=`"$Version`""

if ($build_process.ExitCode -ne 0) {
    throw "Build failed ($($build_process.ExitCode))"   
}

Write-Host "Output of previous WiX install job:"
Receive-Job -Job $wix_job -Wait

$installer_log_filename = "install.log"
$install_process = Start-Process -NoNewWindow -PassThru -Wait -FilePath "msiexec.exe" -ArgumentList "/lv*", $installer_log_filename, "/q", "/i", "msi\$Configuration\Adanaxis.msi"
if ($install_process.ExitCode -ne 0) {
    Write-Host "Installation failed.  Log dump:"
    Get-Content $installer_log_filename | Write-Host
    throw "Installer failed"   
}
Write-Host "Installation successful.  Package details:"
Get-Package "Adanaxis" | Select-Object *
Uninstall-Package "Adanaxis" | ForEach-Object { Write-Host "Uninstall successful, $($_ | Select-Object Status)" }

Write-Host -ForegroundColor Green @"

**************************
*                        *
*    BUILD SUCCESSFUL    *
*                        *
**************************

"@

Write-Host -ForegroundColor Blue "$Configuration build complete for Adanaxis version $Version"
