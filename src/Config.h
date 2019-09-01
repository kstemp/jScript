#pragma once

namespace Config {

	#ifdef _DEBUG
		constexpr bool debug = true;
	#else
		constexpr bool debug = false;
	#endif

}
