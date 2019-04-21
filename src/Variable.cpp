#include "Variable.h"

Variable operator + (const Variable& v1, const Variable& v2) {
	return getVar(v1, v2, [](auto a1, auto a2) { return a1 + a2; });
}

Variable operator - (const Variable& v1, const Variable& v2) {
	return getVar(v1, v2, [](auto a1, auto a2) { return a1 - a2; });
}

Variable operator * (const Variable& v1, const Variable& v2) {
	return getVar(v1, v2, [](auto a1, auto a2) { return a1 * a2; });
}

Variable operator / (const Variable& v1, const Variable& v2) {
	return getVar(v1, v2, [](auto a1, auto a2) { return a1 / a2; });
}

Variable operator > (const Variable& v1, const Variable& v2) {
	return getVar(v1, v2, [](auto a1, auto a2) { return a1 > a2; });
}

Variable operator < (const Variable& v1, const Variable& v2) {
	return getVar(v1, v2, [](auto a1, auto a2) { return a1 < a2; });
}

Variable operator == (const Variable& v1, const Variable& v2) {
	return getVar(v1, v2, [](auto a1, auto a2) { return a1 == a2; });
}
