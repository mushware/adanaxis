#%Header {
##############################################################################
#
# File VisualStudio/adanaxis/GetWindowsDeps.ps1
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
#%Header } 5TLoRmpAW1F+uK00eD58iw

Set-StrictMode -Version 3.0
$ErrorActionPreference = "Stop"

$SDLVersion="2.0.12"
$SDL_mixerVersion="2.0.4"

if ($PSScriptRoot) {
    $ProjectRoot = $(Join-Path -Resolve $PSScriptRoot -ChildPath "..\..")
} Else {
    $ProjectRoot = $(Join-Path -Resolve $pwd -ChildPath "..\..")
}

$DepRoot = $(Join-Path $ProjectRoot -ChildPath "win32deps")

Write-Host "Fetching build dependecies for Adanaxis into ${DepRoot}"
New-Item -ItemType "directory" -Path $DepRoot -Force | Foreach-Object { "Created directory $($_.FullName)" }

# 
# Fetch libSDL
#

$SDLLeafname = "SDL2-devel-${SDLVersion}-VC.zip"
$SDLUri = "https://www.libsdl.org/release/${SDLLeafname}"
$SDLTempPath = $(Join-Path $DepRoot "SDL2-temp")
$SDLDestPath = $(Join-Path $DepRoot "SDL2-devel")

if (Test-Path $SDLDestPath) {
    Write-Host "libSDL2 already present in $SDLDestPath"
} else {
    Write-Host "Fetching libSDL2 ${SDLVersion} to ${SDLLeafname} from ${SDLUri}"
    Invoke-WebRequest -Uri $SDLUri -OutFile $(Join-Path $DepRoot $SDLLeafname)

    Remove-Item -Recurse -Force -ErrorAction Ignore $SDLDestPath
    Expand-Archive $(Join-Path $DepRoot $SDLLeafname) -DestinationPath $SDLTempPath
    Move-Item $(Join-Path $SDLTempPath "SDL2-${SDLVersion}") $SDLDestPath
    Remove-Item $SDLTempPath
    Write-Host "SDL2 ${SDLVersion} downloaded to ${SDLDestPath}"
}

#
# Fetch SDL_mixer
#

$SDL_mixerLeafname = "SDL2_mixer-devel-${SDL_mixerVersion}-VC.zip"
$SDL_mixerUri = "https://www.libsdl.org/projects/SDL_mixer/release/${SDL_mixerLeafname}"
$SDL_mixerTempPath = $(Join-Path $DepRoot "SDL2_mixer-temp")
$SDL_mixerDestPath = $(Join-Path $DepRoot "SDL2_mixer-devel")

if (Test-Path $SDL_mixerDestPath) {
    Write-Host "libSDL2_mixer already present in $SDL_mixerDestPath"
} else {
    Write-Host "Fetching libSDL2_mixer ${SDL_mixerVersion} to ${SDL_mixerLeafname} from ${SDL_mixerUri}"
    Invoke-WebRequest -Uri $SDL_mixerUri -OutFile $(Join-Path $DepRoot $SDL_mixerLeafname)

    Remove-Item -Recurse -Force -ErrorAction Ignore $SDL_mixerDestPath
    Expand-Archive $(Join-Path $DepRoot $SDL_mixerLeafname) -DestinationPath $SDL_mixerTempPath
    Move-Item $(Join-Path $SDL_mixerTempPath "SDL2_mixer-${SDL_mixerVersion}") $SDL_mixerDestPath
    Remove-Item $SDL_mixerTempPath
    Write-Host "SDL2_mixer ${SDL_mixerVersion} downloaded to ${SDL_mixerDestPath}"
}
