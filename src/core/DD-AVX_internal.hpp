#ifndef DD_AVX__INTERNAL_HPP
#define DD_AVX_INTERNAL_HPP

#include "../../include/DD-AVX.hpp"

#if defined USE_AVX2
#include "./AVX2_core.hpp"
#endif

#if defined USE_AVX
#include "./AVX2_core.hpp"
#endif

#if defined USE_AVX512
#include "./AVX512_core.hpp"
#endif

#include "./add.hpp"
#include "./mul.hpp"
#include "./fma.hpp"

#endif
