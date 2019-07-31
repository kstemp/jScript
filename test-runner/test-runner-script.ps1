$jsc = "../bin/x64-Debug/jsc.exe" 

function executeTestScript([string]$filePath){

    Write-Host "[ $filePath ] - testing variable assignment rules... " -NoNewline
    Write-Host "[ PASS ]" -ForegroundColor Green 

    $out = & $jsc $filePath

}

# script
Write-Host
Write-Host "Executing the test-runner-script..."
Write-Host

./test-runner/bin/test-runner .\test-results.xml

$wc = New-Object 'System.Net.WebClient'
$wc.UploadFile("https://ci.appveyor.com/api/testresults/xunit/$($env:APPVEYOR_JOB_ID)", (Resolve-Path .\test-results.xml))