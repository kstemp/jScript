/*

	jScript
	copyright (C) 2019 K. Stempinski

	@filename:		Scope.h
	@description:	TODO

*/

#pragma once

#include <string>
#include <map>

#include "Variable.h"

struct Scope {

	const std::string name;

	std::map<std::string, Variable> variables;

	Scope(const std::string name = "")
		: name(name) {}

	~Scope() {
		clear();
	}

	void clear(){

		variables.clear();

	}

};
