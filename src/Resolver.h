/*

	jScript
	copyright (C) 2019 K. Stempinski

*/

#pragma once

struct Resolver;

#include "Node.h"

struct Resolver {

	template<class T>
	void visit(T& node);

};
