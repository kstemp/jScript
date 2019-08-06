/*

	jScript
	copyright (C) 2019 K. Stempinski

	@filename:		Visitor.h
	@description:	definition of Visitor class, which is reponsible for traversing the AST 
					and evaluating its nodes appropriately.

*/

#pragma once

struct Visitor;

#include "Node.h"

struct Visitor {

	Variable result;

	template<class T>
	void visit(T& node);

};
