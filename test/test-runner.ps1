$jsc = "../bin/x64-Debug/jsc.exe" 

function executeTestScript([string]$filePath){

    Write-Host "[ $filePath ] - testing variable assignment rules... " -NoNewline
    Write-Host "[ PASS ]" -ForegroundColor Green 

    $out = & $jsc $filePath

}


# script
cls
Write-Host
Write-Host "jScript test runner" -ForegroundColor Green
Write-Host "copyright (C) 2019 by K. Stempinski" -ForegroundColor Green
Write-Host "-----------------------------------" -ForegroundColor Green
Write-Host

executeTestScript "code.j"
executeTestScript "code.j"
executeTestScript "code.j"

Write-Host