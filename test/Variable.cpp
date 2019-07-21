#include "pch.h"
#include "CppUnitTest.h"

#include "../src/Variable.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace test{

	TEST_CLASS(TestVariable){

	public:
		
		TEST_METHOD(InitializeVariableWithTypes) {

			Variable var1;
			Variable var2 = 120;
			Variable var3 = 65.6;

			Assert::AreEqual(true, var1.isUndefined(), L"should be undefined");
			Assert::AreEqual(size_t(1), var2.data.index(), L"should be integer");
			Assert::AreEqual(size_t(2), var3.data.index(), L"should be double");

		};
		TEST_METHOD(InitializeVariableWithAnotherVariable) {

			Variable var1 = 809;
			Variable var2 = var1;

			Assert::AreEqual(false, var1.isUndefined(), L"should NOT be undefined");
			Assert::AreEqual(size_t(1), var2.data.index(), L"should be integer");
			Assert::AreEqual(809, var2.getData<int>(), L"value should be 809");

		};

		TEST_METHOD(CheckIsUndefined) {

			Variable var1 = 809;
			Variable var2;

			Assert::AreNotEqual(true, var1.isUndefined(), L"should NOT be undefined");
			Assert::AreEqual(true, var2.isUndefined(), L"should be undefined");

		};

	};
}
