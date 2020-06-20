
Set-StrictMode -Version 3.0

# This only works in Windows Server so ignore failure
$ErrorActionPreference = "SilentlyContinue"
Install-WindowsFeature Net-Framework-Core

$ErrorActionPreference = "Stop"
cinst --no-progress --version=3.11.2 -y wixtoolset
