
Set-StrictMode -Version 3.0

$SDLVersion="2.0.12"

if ($PSScriptRoot) {
    $ProjectRoot = $(Join-Path -Resolve $PSScriptRoot -ChildPath "..")
} Else {
    $ProjectRoot = $(Join-Path -Resolve $pwd -ChildPath "..")
}

$DepRoot = $(Join-Path $ProjectRoot -ChildPath "windeps")

Write-Host "Fetching build dependecies for Adanaxis into ${DepRoot}"
$_ = New-Item -ItemType "directory" -Path $DepRoot -Force -ErrorAction Stop

$SDLLeafname = "SDL2-devel-${SDLVersion}-VC.zip"
$SDLUri = "https://www.libsdl.org/release/${SDLLeafname}"
Write-Host "Fetching libSDL2 ${SDLVersion} to ${SDLLeafname} from ${SDLUri}"
Invoke-WebRequest -Uri $SDLUri -ErrorAction Stop -OutFile $(Join-Path $DepRoot $SDLLeafname)

$SDLTempPath = $(Join-Path $DepRoot "SDL2-temp")
$SDLDestPath = $(Join-Path $DepRoot "SDL2-devel")
Remove-Item -Recurse -Force $SDLDestPath

Expand-Archive $(Join-Path $DepRoot $SDLLeafname) -DestinationPath $SDLTempPath
Move-Item $(Join-Path $SDLTempPath "SDL2-${SDLVersion}") $SDLDestPath
Remove-Item $SDLTempPath
Write-Host "SDL2 ${SDLVersion} downloaded to ${SDLDestPath}"
