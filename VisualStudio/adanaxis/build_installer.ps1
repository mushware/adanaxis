
$outpath = "obj\Debug\"
$msi_path = "msi\Debug\Adanaxis.msi"
$candle_args_pre = @()
$candle_args_post = @()
$light_args_post = @()

Remove-Item -ErrorAction Ignore -Force $msi_path

$datadirs = @("mush", "mushruby", "pixels", "ruby", "spaces", "system", "waves")
foreach ($datadir in $datadirs) {
    if ($datadir -eq "mushruby") {
        $sourcedir = "../../adanaxis-mushruby/$datadir"
    } else {
        $sourcedir = "../../adanaxis-data/$datadir"
    }
    $destfile="adanaxis_$datadir.wxi"
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

$candle_command = "candle.exe $($candle_args_pre -join "" "") -v -out $outpath -arch x86 Adanaxis.wxs $($candle_args_post -join "" "")"
Write-Host "Executing $candle_command`n"
Invoke-Expression -ErrorAction Stop $candle_command

$light_command = "light.exe -ext WixUIExtension -cultures:en-us -out ""$msi_path"" -pdbout msi\Debug\Adanaxis.wixpdb -contentsfile obj\Debug\adanaxis-wixsetup.wixproj.BindContentsFileListnull.txt -outputsfile obj\Debug\adanaxis-wixsetup.wixproj.BindOutputsFileListnull.txt -builtoutputsfile obj\Debug\adanaxis-wixsetup.wixproj.BindBuiltOutputsFileListnull.txt obj\Debug\Adanaxis.wixobj $($light_args_post -join "" "")"
Write-Host "Executing $light_command`n"
Invoke-Expression -ErrorAction Stop $light_command
