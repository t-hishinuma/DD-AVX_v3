#pragma once
#ifndef DD_AVX_CORE_ADD_HPP_
#define DD_AVX_CORE_ADD_HPP_

#include <immintrin.h>
#define DD_AVX_FUNC(NAME) _mm256_##NAME
using AVXreg = __m256d;

namespace ddavx_core{
	inline void Add(
			__m256d& a_hi, __m256d& a_lo,
			const __m256d& b_hi, const __m256d& b_lo,
			const __m256d& c_hi, const __m256d& c_lo,
			registers& c
			)
	{
		c.bh = b_hi; 
		c.bl = b_lo; 
		c.ch = c_hi; 
		c.p2 = c_lo;

		c.sh = DD_AVX_FUNC(add_pd)(c.bh,c.ch); 
		c.th = DD_AVX_FUNC(sub_pd)(c.sh,c.bh); 
		c.t0 = DD_AVX_FUNC(sub_pd)(c.sh,c.th); 
		c.ch = DD_AVX_FUNC(sub_pd)(c.ch,c.th); 
		c.bh = DD_AVX_FUNC(sub_pd)(c.bh,c.t0); 
		c.bh = DD_AVX_FUNC(add_pd)(c.bh,c.ch); 
		c.sl = DD_AVX_FUNC(add_pd)(c.bl,c.p2); 
		c.th = DD_AVX_FUNC(sub_pd)(c.sl,c.bl); 
		c.t0 = DD_AVX_FUNC(sub_pd)(c.sl,c.th); 
		c.p2 = DD_AVX_FUNC(sub_pd)(c.p2,c.th); 
		c.bl = DD_AVX_FUNC(sub_pd)(c.bl,c.t0); 
		c.bl = DD_AVX_FUNC(add_pd)(c.bl,c.p2); 
		c.bh = DD_AVX_FUNC(add_pd)(c.bh,c.sl); 
		c.th = c.sh; 
		c.th = DD_AVX_FUNC(add_pd)(c.th,c.bh); 
		c.sh = DD_AVX_FUNC(sub_pd)(c.th,c.sh); 
		c.bh = DD_AVX_FUNC(sub_pd)(c.bh,c.sh); 
		c.bh = DD_AVX_FUNC(add_pd)(c.bh,c.bl); 
		c.sh = DD_AVX_FUNC(add_pd)(c.th,c.bh); 

		a_hi = c.sh;
		c.sh = DD_AVX_FUNC(sub_pd)(c.sh,c.th); 
		c.bh = DD_AVX_FUNC(sub_pd)(c.bh,c.sh);
		a_lo = c.bh;
	}

	inline void Add(
			__m256d& a_hi,
			const __m256d& b_hi, const __m256d& b_lo,
			const __m256d& c_hi, const __m256d& c_lo,
			registers& c
			)
	{
		c.bh = b_hi; 
		c.bl = b_lo; 
		c.ch = c_hi; 
		c.p2 = c_lo;

		c.sh = DD_AVX_FUNC(add_pd)(c.bh,c.ch); 
		c.th = DD_AVX_FUNC(sub_pd)(c.sh,c.bh); 
		c.t0 = DD_AVX_FUNC(sub_pd)(c.sh,c.th); 
		c.ch = DD_AVX_FUNC(sub_pd)(c.ch,c.th); 
		c.bh = DD_AVX_FUNC(sub_pd)(c.bh,c.t0); 
		c.bh = DD_AVX_FUNC(add_pd)(c.bh,c.ch); 
		c.sl = DD_AVX_FUNC(add_pd)(c.bl,c.p2); 
		c.th = DD_AVX_FUNC(sub_pd)(c.sl,c.bl); 
		c.t0 = DD_AVX_FUNC(sub_pd)(c.sl,c.th); 
		c.p2 = DD_AVX_FUNC(sub_pd)(c.p2,c.th); 
		c.bl = DD_AVX_FUNC(sub_pd)(c.bl,c.t0); 
		c.bl = DD_AVX_FUNC(add_pd)(c.bl,c.p2); 
		c.bh = DD_AVX_FUNC(add_pd)(c.bh,c.sl); 
		c.th = c.sh; 
		c.th = DD_AVX_FUNC(add_pd)(c.th,c.bh); 
		c.sh = DD_AVX_FUNC(sub_pd)(c.th,c.sh); 
		c.bh = DD_AVX_FUNC(sub_pd)(c.bh,c.sh); 
		c.bh = DD_AVX_FUNC(add_pd)(c.bh,c.bl); 
		c.sh = DD_AVX_FUNC(add_pd)(c.th,c.bh); 

		a_hi = c.sh;
	}

	inline void Add(
			double& a_hi, double& a_lo,
			const double& b_hi, const double& b_lo,
			const double& c_hi, const double& c_lo)
	{
		dd_real a, b, c;
		a.x[0] = a_hi; a.x[1] = a_lo;
		b.x[0] = b_hi; b.x[1] = b_lo;
		c.x[0] = c_hi; c.x[1] = c_lo;
		a = b + c;

		a_hi = a.x[0], a_lo = a.x[1];
	}

	inline void Add(
			double& a_hi, 
			const double& b_hi, const double& b_lo,
			const double& c_hi, const double& c_lo)
	{
		dd_real a, b, c;
		a.x[0] = a_hi; a.x[1] = 0.0;
		b.x[0] = b_hi; b.x[1] = b_lo;
		c.x[0] = c_hi; c.x[1] = c_lo;
		a = b + c;

		a_hi = a.x[0];
	}

}
#endif
