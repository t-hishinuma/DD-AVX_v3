#ifndef DD_AVX__INTERNAL_HPP
#define DD_AVX_INTERNAL_HPP

#include"../../include/DD-AVX.hpp"

#if USE_AVX2==1
	#include "./AVX2_core.hpp"
#elif USE_AVX512==1 // for AVX512
	#include "./AVX512_core.hpp"
#endif

	#include "./add.hpp"
	#include "./mul.hpp"
	#include "./fma.hpp"

#endif
