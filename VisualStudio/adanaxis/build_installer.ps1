
param(
    [Parameter(Mandatory)]$Configuration,
    [Parameter(Mandatory)]$Version
)

Set-StrictMode -Version 3.0
$ErrorActionPreference = "Stop"

function SignFile {
    param (
        [Parameter(Mandatory)]$PathToSign
    )

    if ($env:ADANAXIS_POST_F_OPT) {
        $f_opt = $env:ADANAXIS_POST_F_OPT
        $p_opt = $env:ADANAXIS_POST_P_OPT
        $ac_opt = $env:ADANAXIS_POST_AC_OPT
    } ElseIf ($env:ADANAXIS_BRANCH_POST_F_OPT) {
        $f_opt = $env:ADANAXIS_BRANCH_POST_F_OPT
        $p_opt = $env:ADANAXIS_BRANCH_POST_P_OPT
        $ac_opt = $env:ADANAXIS_BRANCH_POST_AC_OPT
    } Else {
        Write-Host "No code signing configuration so will not sign binaries"
        Return
    }
    
    $ErrorActionPreference = "SilentlyContinue"
    $machine_cert = $(Import-PfxCertificate -FilePath "$f_opt" -CertStoreLocation Cert:\LocalMachine\My -Password $(ConvertTo-SecureString -String "$p_opt" -AsPlainText -Force)) 2>&1
    $user_cert = $(Import-PfxCertificate -FilePath "$f_opt" -CertStoreLocation Cert:\CurrentUser\My -Password $(ConvertTo-SecureString -String "$p_opt" -AsPlainText -Force)) 2>&1
    $ErrorActionPreference = "Stop"

    $sign_arglist = @("sign",  "/d", "`"From the Adanaxis project`"", "/du", "`"https://www.mushware.com/`"", "/fd", "sha256", "/tr", "`"http://timestamp.digicert.com?alg=sha256`"", "/td", "sha256", "/v")

    If ($machine_cert) {
        Write-Host "Signing with machine cert thumbprint: $($machine_cert.Thumbprint)"
        $sign_arglist += @("/sha1", $machine_cert.Thumbprint, "/sm")
    } ElseIf ($user_cert) {
        Write-Host "Signing with user cert thumbprint: $($user_cert.Thumbprint)"
        $sign_arglist += @("/sha1", $user_cert.Thumbprint)
    } Else {
        Throw "Failed to install signing certificate"
    }

    If ($ac_opt) {
        $sign_arglist += @("/ac", "`"$ac_opt`"")
    }

    $sign_arglist += @($PathToSign)
    $sign_process = Start-Process -NoNewWindow -PassThru -Wait -FilePath "signtool.exe" -RedirectStandardError signtool_errors.txt -ArgumentList $sign_arglist

    # Capture and print the first failure without output to stderr (that would cause the build to fail)
    Get-Content signtool_errors.txt
    
    If ($sign_process.ExitCode -ne 0) {
        Write-Host "Signing process failed ($($sign_process.ExitCode)), retrying..."

        $sign_process = Start-Process -NoNewWindow -PassThru -Wait -FilePath "signtool.exe" -ArgumentList $sign_arglist

        If ($sign_process.ExitCode -ne 0) {
            Throw "Code signing failed ($($sign_process.ExitCode))"
        }
    }

    If ($env:ADANAXIS_POST_F_OPT) {
        $verify_process = Start-Process -NoNewWindow -PassThru -Wait -FilePath "signtool.exe" -ArgumentList "verify", "/a", "/pa", "/tw", $PathToSign

        If ($verify_process.ExitCode -ne 0) {
            Throw "Code signature verification failed ($($verify_process.ExitCode))"
        }
    }
}

$outpath = "obj\$Configuration\"
$exe_path = "..\..\adanaxis-data\system\adanaxis.exe"
$msi_path = "msi\$Configuration\Adanaxis.msi"
$candle_args_pre = @()
$candle_args_post = @()
$light_args_post = @()

Remove-Item -ErrorAction Ignore -Force $msi_path

SignFile($exe_path)

$datadirs = @("mush", "mushruby", "pixels", "ruby", "spaces", "system", "waves")
ForEach ($datadir In $datadirs) {
    $sourcedir = "..\..\adanaxis-data\$datadir"
    $destfile="obj\$Configuration\adanaxis_$datadir.wxi"
    $candle_args_pre += "-dadanaxis_$datadir=""$sourcedir"""  
    $candle_args_post += $destfile
    $obj_file = "${outpath}adanaxis_$datadir.wixobj"
    $light_args_post += $obj_file
    Remove-Item -ErrorAction Ignore -Force $destfile
    Remove-Item -ErrorAction Ignore -Force $obj_file
    $heat_command="heat.exe dir $sourcedir -dr INSTALLFOLDER -cg Adanaxis_$datadir -gg -sfrag -var var.adanaxis_$datadir -v -o $destfile"
    Write-Host "Executing $heat_command`n"
    Invoke-Expression -ErrorAction Stop $heat_command
}

$candle_command = "candle.exe $($candle_args_pre -join "" "") -dadanaxis_version=""$Version"" -v -out $outpath -arch x86 Adanaxis.wxs $($candle_args_post -join "" "")"
Write-Host "Executing $candle_command`n"
Invoke-Expression -ErrorAction Stop $candle_command

$light_command = "light.exe -ext WixUIExtension -cultures:en-us -out ""$msi_path"" -pdbout msi\$Configuration\Adanaxis.wixpdb -contentsfile obj\$Configuration\adanaxis-wixsetup.wixproj.BindContentsFileListnull.txt -outputsfile obj\$Configuration\adanaxis-wixsetup.wixproj.BindOutputsFileListnull.txt -builtoutputsfile obj\$Configuration\adanaxis-wixsetup.wixproj.BindBuiltOutputsFileListnull.txt obj\$Configuration\Adanaxis.wixobj $($light_args_post -join "" "")"
Write-Host "Executing $light_command`n"
Invoke-Expression -ErrorAction Stop $light_command

SignFile($msi_path)

Write-Host Installer build complete.
