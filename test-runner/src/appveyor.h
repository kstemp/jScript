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

class AppVeyor {

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

    static void uploadTestResult(std::string description, bool passed){

        rapidjson::Document document;
        document.SetObject();
        auto& allocator = document.GetAllocator();

        document.AddMember("testName", description, allocator);
        document.AddMember("testFramework", "NUnit", allocator); //TODO change to test-runner or sth like that
        document.AddMember("fileName", "code.j", allocator); //TODO change fileName 
        document.AddMember("outcome", passed ? "Passed" : "Failed", allocator); 
        document.AddMember("durationMiliseconds", "1000", allocator);
        document.AddMember("ErrorMessage", "sample error message", allocator);
        document.AddMember("ErrorStackTrace", "in function test() whatever", allocator);
        document.AddMember("StdOut", "standard output", allocator);
        document.AddMember("StdErr", "standard error output", allocator);  

        rapidjson::StringBuffer sb;
        rapidjson::Writer<rapidjson::StringBuffer> writer(sb);

        document.Accept(writer);

        char const* tmp = std::getenv("APPVEYOR_API_URL");
if ( tmp == NULL ) {
  return;
    //  TODO throw or whatever
} 

    std::string s(tmp);
    s += "api/tests";
  
          post(s, sb.GetString());



    }




};

