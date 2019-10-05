#pragma once

#include "../src/cpptest.h"

#include "..//..//src///Variable.h"

void testVariable() {

	CppTest::describe("The Variable module",

		CppTest::test("Initializes to [int] when initialized with an integer", []() {

			Variable p(123);
			Assert::AreEqual(p.getTypeName(), "int");

		}),

		CppTest::test("Initializes to [double] when initialized with a double", []() {

			Variable p(123.07);
			Assert::AreEqual(p.getTypeName(), "int");

		}),

		CppTest::test("Initializes to [undefined] when default constructor is used", []() {

			Variable p;
			Assert::AreEqual(p.getTypeName(), "int");

		})

	);

}

