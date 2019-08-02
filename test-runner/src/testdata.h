#pragma once

#include <string>

struct TestData {

    std::string description;
    std::string fileName; 
    bool passed; 
    std::string duration;
    std::string errorMessage;
    std::string stackTrace;
    std::string stdOut;
    std::string stdErr;
 
};