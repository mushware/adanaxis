#%Header {
##############################################################################
#
# File VisualStudio/adanaxis/get_adanaxis_deps.ps1
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
#%Header } wr2dJHVwhK27kAN2SRrhIQ

Param(
    [Parameter(Mandatory)]$Configuration,
    [Parameter(Mandatory)]$DepsVersion,
    [Parameter(Mandatory)]$MushRubyTag,
    [Parameter(Mandatory)]$MushRubyVersion
)

Set-StrictMode -Version 3.0
$ErrorActionPreference = "Stop"

if ($PSScriptRoot) {
    $ProjectRoot = $(Join-Path -Resolve $PSScriptRoot -ChildPath "..\..")
} Else {
    $ProjectRoot = $(Join-Path -Resolve $pwd -ChildPath "..\..")
}

$underscore_deps_version = $DepsVersion.Replace(".", "_")
$deps_tag = "v" + ($DepsVersion.Split(".")[0..2] -join ".")

$DepsName = "adanaxis-win64deps-$Configuration-$underscore_deps_version"
$DepsZipName = "$DepsName.zip"
$DepsTagName = "tagfile_${Configuration}_${underscore_deps_version}.txt"
$DepsUrl = "https://github.com/mushware/adanaxis-win64deps/releases/download/$deps_tag/$DepsZipName"
$DepsRoot = $(Join-Path $ProjectRoot -ChildPath "deps")
$DepsZipPath = $(Join-Path $ProjectRoot -ChildPath $DepsZipName)
$DepsManifestPath = $(Join-Path $DepsRoot -ChildPath "manifest.ps1")
$DepsTagPath = $(Join-Path $DepsRoot -ChildPath $DepsTagName)

# 
# Fetch deps
#

if (Test-Path $DepsTagPath) {
    Write-Host -ForegroundColor Green @"

File ${DepsName} already present in ${DepsRoot} so not downloading.

"@
} else {
    if (Test-Path $DepsRoot) {
        if (!(Test-Path $DepsManifestPath)) {
            throw "Deps directory ${DepsRoot} present but manifest ${DepsManifestPath} missing, so abandoning for safety"
        }
        Write-Host "Removing previous deps directory ${DepsRoot}"
        Remove-Item -Path $DepsRoot -Recurse
    } 

    New-Item -ItemType "directory" -Path $DepsRoot -Force | Foreach-Object { "Created directory $($_.FullName)" }

    Write-Host  -ForegroundColor Blue @"

Fetching ${DepsZipName}
to ${DepsZipPath}
from ${DepsUrl}

"@

    try {
        Invoke-WebRequest -Uri $DepsUrl -OutFile $DepsZipPath

        Expand-Archive $DepsZipPath -DestinationPath $DepsRoot
    }
    catch {
        Write-Host  -ForegroundColor DarkRed "Removing deps directory ${DepsRoot} after failure"
        Remove-Item -Path $DepsRoot
        throw
    }

    Write-Host -ForegroundColor Green @"

File ${DepsName} downloaded into ${DepsRoot} successfully.

"@
}

$underscore_MushRuby_version = $MushRubyVersion.Replace(".", "_")
$MushRuby_tag = "v" + ($MushRubyTag.Split(".")[0..2] -join ".")

$MushRubyName = "MushRuby_${Configuration}_${underscore_MushRuby_version}"
$MushRubyZipName = "$MushRubyName.zip"
$MushRubyUrl = "https://github.com/mushware/ruby/releases/download/$MushRuby_tag/$MushRubyZipName"
$MushRubyRoot = $(Join-Path $ProjectRoot -ChildPath "MushRuby")
$MushRubyTagPath = $(Join-Path $MushRubyRoot -ChildPath "README.txt")
$MushRubyZipPath = $(Join-Path $ProjectRoot -ChildPath $MushRubyZipName)
# 
# Fetch MushRuby
#

if (Test-Path $MushRubyTagPath) {
    Write-Host -ForegroundColor Green @"

File ${MushRubyName} already present in ${MushRubyRoot} so not downloading.

"@
} else {
    if (Test-Path $MushRubyRoot) {
        if (!(Test-Path $MushRubyManifestPath)) {
            throw "MushRuby directory ${MushRubyRoot} present but tag file ${MushRubyTagPath} missing, so abandoning for safety"
        }
        Write-Host "Removing previous MushRuby directory ${MushRubyRoot}"
        Remove-Item -Path $MushRubyRoot -Recurse
    }

    New-Item -ItemType "directory" -Path $MushRubyRoot -Force | Foreach-Object { "Created directory $($_.FullName)" }

    Write-Host  -ForegroundColor Blue @"

Fetching ${MushRubyZipName}
to ${MushRubyZipPath}
from ${MushRubyUrl}

"@

    try {
        Invoke-WebRequest -Uri $MushRubyUrl -OutFile $MushRubyZipPath

        Expand-Archive $MushRubyZipPath -DestinationPath $MushRubyRoot
    }
    catch {
        Write-Host  -ForegroundColor DarkRed "Removing MushRuby directory ${MushRubyRoot} after failure"
        Remove-Item -Path $MushRubyRoot
        throw
    }

    Write-Host -ForegroundColor Green @"

File ${MushRubyName} downloaded into ${MushRubyRoot} successfully.

"@
}
