$testCountFailed = 0

$testName = "test A"
$frameworkName = "jsc-test-runner"
$jscBinaryName = "jsc.exe"
$outcome = "Passed"

Add-AppveyorTest    -Name $testName 
                    -Framework $frameworkName -
                    -Filename $jscBinaryName 
                    -Outcome $outcome 

exit testCountFailed