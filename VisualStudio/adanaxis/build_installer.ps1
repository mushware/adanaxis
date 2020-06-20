
Param(
    [Parameter(Mandatory)]$Configuration,
    [Parameter(Mandatory)]$Version
)

Set-StrictMode -Version 3.0
$ErrorActionPreference = "Stop"

$outpath = "obj\$Configuration\"
$msi_path = "msi\$Configuration\Adanaxis.msi"
$candle_args_pre = @()
$candle_args_post = @()
$light_args_post = @()

Remove-Item -ErrorAction Ignore -Force $msi_path

$datadirs = @("mush", "mushruby", "pixels", "ruby", "spaces", "system", "waves")
foreach ($datadir in $datadirs) {
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

Write-Host Installer build complete.
