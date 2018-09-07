$exists = Test-Path build

If (!$exists) {
    New-Item build -type directory | Out-Null
    Write-Host "Build folder created"
}

Set-Location build
cmake -G "Visual Studio 15 2017 Win64" ..
Set-Location ..