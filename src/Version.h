/*

	jScript
	copyright (C) 2019 K. Stempinski

	@filename:		Version.h
	@description:	

*/
#pragma once

#include <string>

constexpr int VERSION_MAJOR = 0;
constexpr int VERSION_MINOR = 1;

std::string getVersionInfoString() {

	return std::to_string(VERSION_MAJOR) + "." + std::to_string(VERSION_MINOR);

}