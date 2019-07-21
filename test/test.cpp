#include "pch.h"
#include "CppUnitTest.h"

#include "../src/Variable.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace test{

	TEST_CLASS(Variable){

	public:
		
		TEST_METHOD(InitializeVariableWithAppropriateType){

			Variable var1;
			Variable var2 = 120;
			Variable var3 = 45.76;

			Assert::AreEqual(var1.isUndefined(), false);
			
		}
	};
}
