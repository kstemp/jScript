#pragma once

#include <iostream>

#define Assert_IsTrue(expr) do {\
	if (!(expr)) {\
		return false;\
	} else {\
		return true;\
	}\
} while(0)

#define Assert_AreEqual(actual, expected) do {\
	return (actual == expected);\
} while(0)




