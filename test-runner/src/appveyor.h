#pragma once

#include <curlpp/cURLpp.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Easy.hpp>

#include <sstream>

#include <future>

class AppVeyor {

public:

static std::future<std::string> invoke(std::string const& url, std::string const& body) {
  return std::async(std::launch::async,
    [](std::string const& url, std::string const& body) mutable {
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

      return std::string(response.str());
    }, url, body);
}

    static void uploadTestResult(const std::string& description){

        std::cout << "APPVEYOR URL: " << std::getenv("APPVEYOR_API_URL") << "\n";
       // invoke(std::getenv("APPVEYOR_API_URL"), "");



    }




};

