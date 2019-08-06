#pragma once

#include <optional>

class GetEnvHelper final {
public:

    static std::optional<std::string> getenv(const std::string& varName){

		const char* buffer = std::getenv(varName.c_str());
        
        if (buffer != NULL)
            return { std::string(buffer) };
        else 
            return { };

    }

};

