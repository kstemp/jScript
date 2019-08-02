#pragma once

#include <curlpp/cURLpp.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Easy.hpp>

#define RAPIDJSON_HAS_STDSTRING 1
#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

#include <sstream>

#include <future>

#include "testdata.h"
#include "utils/getenv-helper.h"

class AppVeyor final {

public:

  static void post(std::string const& url, std::string const& body) {

    std::list<std::string> header;
    header.push_back("Content-Type: application/json");
    curlpp::Cleanup clean;
    curlpp::Easy r;
    r.setOpt(new curlpp::options::Url(url));
    r.setOpt(new curlpp::options::HttpHeader(header));
    r.setOpt(new curlpp::options::PostFields(body));
    r.setOpt(new curlpp::options::PostFieldSize(body.length()));
    std::ostringstream response;
    r.setOpt(new curlpp::options::WriteStream(&response));
    r.perform();
    // return std::string(response.str());

  }

  static std::string getJSONTestDescription(const TestData& testData){
    
	rapidjson::Document document;
    document.SetObject();
    auto& allocator = document.GetAllocator();
    
    document.AddMember("testName", testData.description, allocator);
    document.AddMember("testFramework", "NUnit", allocator); //TODO change to test-runner or sth like that
    document.AddMember("fileName", testData.fileName, allocator); //TODO change fileName 
    document.AddMember("outcome", "Passed", allocator);  //TODO passed or failed
    document.AddMember("durationMiliseconds", testData.duration, allocator);
    document.AddMember("ErrorMessage", testData.errorMessage, allocator);
    document.AddMember("ErrorStackTrace", testData.stackTrace, allocator);
    document.AddMember("StdOut", testData.stdOut, allocator);
    document.AddMember("StdErr", testData.stdErr, allocator);

    rapidjson::StringBuffer sb;
    rapidjson::Writer<rapidjson::StringBuffer> writer(sb);
    document.Accept(writer);

    return sb.GetString();

  }

  static void uploadTestResult(const TestData& testData){

    const std::optional<std::string> appVeyorURL = GetEnvHelper::getenv("APPVEYOR_API_URL");

    if (!appVeyorURL.has_value())
      return; // TODO throw

    const std::string postURL =  appVeyorURL.value() + "api/tests";
    post(postURL, getJSONTestDescription(testData));

  }

};

