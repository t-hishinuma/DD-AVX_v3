#pragma once
#ifndef DD_AVX_CORE_MUL_HPP_
#define DD_AVX_CORE_MUL_HPP_

#include <immintrin.h>
#define DD_AVX_FUNC(NAME) _mm256_##NAME
using AVXreg = __m256d;

namespace ddavx_core{

	inline void Mul(
			__m256d& a_hi, __m256d& a_lo,
			const __m256d& b_hi, const __m256d& b_lo,
			const __m256d& c_hi, const __m256d& c_lo,
			registers c
			)
	{
		c.bh = b_hi; 
		c.bl = b_lo; 
		c.ch = c_hi; 
		c.cl = c_lo;

#if 1
		c.p1 = DD_AVX_FUNC(mul_pd)(c.minus, c.bh); 
		c.p1 = DD_AVX_FUNC(mul_pd)(c.p1, c.ch); 
		c.p2 = DD_AVX_FUNC(fmadd_pd)(c.bh, c.ch, c.p1); 
		c.p1 = DD_AVX_FUNC(mul_pd)(c.minus, c.p1); 
		c.p2 = DD_AVX_FUNC(fmadd_pd)(c.bh, c.cl, c.p2); 
		c.p2 = DD_AVX_FUNC(fmadd_pd)(c.bl, c.ch, c.p2);
		c.ch = DD_AVX_FUNC(add_pd)(c.p1, c.p2);
#else
		c.p1  = DD_AVX_FUNC(mul_pd)(c.bh, c.ch);
		c.sh  = DD_AVX_FUNC(mul_pd)(c.sp, c.bh);
		c.sl  = DD_AVX_FUNC(mul_pd)(c.sp, c.ch);
		c.th  = DD_AVX_FUNC(sub_pd)(c.sh, c.bh);
		c.tl  = DD_AVX_FUNC(sub_pd)(c.sl, c.ch);
		c.sh  = DD_AVX_FUNC(sub_pd)(c.sh, c.th);
		c.sl  = DD_AVX_FUNC(sub_pd)(c.sl, c.tl);
		c.t1  = DD_AVX_FUNC(mul_pd)(c.bh, c.cl);
		c.wh  = DD_AVX_FUNC(sub_pd)(c.bh, c.sh);
		c.t2  = DD_AVX_FUNC(mul_pd)(c.ch, c.bl);
		c.wl  = DD_AVX_FUNC(sub_pd)(c.ch, c.sl);
		c.t0  = DD_AVX_FUNC(mul_pd)(c.wh, c.wl);
		c.p2  = DD_AVX_FUNC(mul_pd)(c.sh, c.sl);
		c.sh  = DD_AVX_FUNC(mul_pd)(c.sh, c.wl);
		c.sl  = DD_AVX_FUNC(mul_pd)(c.sl, c.wh);
		c.p2  = DD_AVX_FUNC(sub_pd)(c.p2, c.p1);
		c.p2  = DD_AVX_FUNC(add_pd)(c.p2, c.sh);
		c.p2  = DD_AVX_FUNC(add_pd)(c.p2, c.sl);
		c.p2  = DD_AVX_FUNC(add_pd)(c.p2, c.t0);
		c.p2  = DD_AVX_FUNC(add_pd)(c.p2, c.t1);
		c.p2  = DD_AVX_FUNC(add_pd)(c.p2, c.t2);
		c.ch  = DD_AVX_FUNC(add_pd)(c.p1, c.p2);
#endif
		a_hi  = c.ch;
		c.ch  = DD_AVX_FUNC(sub_pd)(c.ch, c.p1);
		c.p2  = DD_AVX_FUNC(sub_pd)(c.p2, c.ch);
		a_lo  = c.p2;
	}

	inline void Mul(
			__m256d& a_hi, 
			const __m256d& b_hi, const __m256d& b_lo,
			const __m256d& c_hi, const __m256d& c_lo,
			registers c
			)
	{
		c.bh = b_hi; 
		c.bl = b_lo; 
		c.ch = c_hi; 
		c.cl = c_lo;

#if 1
		c.p1 = DD_AVX_FUNC(mul_pd)(c.minus, c.bh); 
		c.p1 = DD_AVX_FUNC(mul_pd)(c.p1, c.ch); 
		c.p2 = DD_AVX_FUNC(fmadd_pd)(c.bh, c.ch, c.p1); 
		c.p1 = DD_AVX_FUNC(mul_pd)(c.minus, c.p1); 
		c.p2 = DD_AVX_FUNC(fmadd_pd)(c.bh, c.cl, c.p2); 
		c.p2 = DD_AVX_FUNC(fmadd_pd)(c.bl, c.ch, c.p2);
		c.ch = DD_AVX_FUNC(add_pd)(c.p1, c.p2);
#else
		c.p1  = DD_AVX_FUNC(mul_pd)(c.bh, c.ch);
		c.sh  = DD_AVX_FUNC(mul_pd)(c.sp, c.bh);
		c.sl  = DD_AVX_FUNC(mul_pd)(c.sp, c.ch);
		c.th  = DD_AVX_FUNC(sub_pd)(c.sh, c.bh);
		c.tl  = DD_AVX_FUNC(sub_pd)(c.sl, c.ch);
		c.sh  = DD_AVX_FUNC(sub_pd)(c.sh, c.th);
		c.sl  = DD_AVX_FUNC(sub_pd)(c.sl, c.tl);
		c.t1  = DD_AVX_FUNC(mul_pd)(c.bh, c.cl);
		c.wh  = DD_AVX_FUNC(sub_pd)(c.bh, c.sh);
		c.t2  = DD_AVX_FUNC(mul_pd)(c.ch, c.bl);
		c.wl  = DD_AVX_FUNC(sub_pd)(c.ch, c.sl);
		c.t0  = DD_AVX_FUNC(mul_pd)(c.wh, c.wl);
		c.p2  = DD_AVX_FUNC(mul_pd)(c.sh, c.sl);
		c.sh  = DD_AVX_FUNC(mul_pd)(c.sh, c.wl);
		c.sl  = DD_AVX_FUNC(mul_pd)(c.sl, c.wh);
		c.p2  = DD_AVX_FUNC(sub_pd)(c.p2, c.p1);
		c.p2  = DD_AVX_FUNC(add_pd)(c.p2, c.sh);
		c.p2  = DD_AVX_FUNC(add_pd)(c.p2, c.sl);
		c.p2  = DD_AVX_FUNC(add_pd)(c.p2, c.t0);
		c.p2  = DD_AVX_FUNC(add_pd)(c.p2, c.t1);
		c.p2  = DD_AVX_FUNC(add_pd)(c.p2, c.t2);
		c.ch  = DD_AVX_FUNC(add_pd)(c.p1, c.p2);
#endif
		a_hi  = c.ch;
	}


	inline void Muld(
			__m256d& a_hi, __m256d& a_lo,
			const __m256d& b_hi, const __m256d& b_lo,
			const __m256d& c_hi,
			registers c
			)
	{

		c.bh  = b_hi; 
		c.bl  = b_lo; 
		c.ch  = c_hi;

#if 1
		c.p1 = DD_AVX_FUNC(mul_pd)(c.minus, c.bh); 
		c.p1 = DD_AVX_FUNC(mul_pd)(c.p1, c.ch); 
		c.p2 = DD_AVX_FUNC(fmadd_pd)(c.bh, c.ch, c.p1); 
		c.p1 = DD_AVX_FUNC(mul_pd)(c.minus, c.p1); 
		c.p2 = DD_AVX_FUNC(fmadd_pd)(c.bl, c.ch, c.p2); 
		c.ch = DD_AVX_FUNC(add_pd)(c.p1, c.p2);
#else
		c.p1  = DD_AVX_AVX_FUNC(mul_pd)(c.bh, c.ch);
		c.bl  = DD_AVX_AVX_FUNC(mul_pd)(c.bl, c.ch);
		c.sh  = DD_AVX_AVX_FUNC(mul_pd)(c.sp, c.bh);
		c.th  = DD_AVX_AVX_FUNC(sub_pd)(c.sh, c.bh);
		c.sh  = DD_AVX_AVX_FUNC(sub_pd)(c.sh, c.th);
		c.bh  = DD_AVX_AVX_FUNC(sub_pd)(c.bh, c.sh);
		c.sl  = DD_AVX_AVX_FUNC(mul_pd)(c.sp, c.ch);
		c.tl  = DD_AVX_AVX_FUNC(sub_pd)(c.sl, c.ch);
		c.sl  = DD_AVX_AVX_FUNC(sub_pd)(c.sl, c.tl);
		c.ch  = DD_AVX_AVX_FUNC(sub_pd)(c.ch, c.sl);
		c.t2  = DD_AVX_AVX_FUNC(mul_pd)(c.bh, c.ch);
		c.p2  = DD_AVX_AVX_FUNC(mul_pd)(c.sh, c.sl);
		c.t0  = DD_AVX_AVX_FUNC(mul_pd)(c.sh, c.ch);
		c.t1  = DD_AVX_AVX_FUNC(mul_pd)(c.sl, c.bh);
		c.p2  = DD_AVX_AVX_FUNC(sub_pd)(c.p2, c.p1);
		c.p2  = DD_AVX_AVX_FUNC(add_pd)(c.p2, c.t0);
		c.p2  = DD_AVX_AVX_FUNC(add_pd)(c.p2, c.t1);
		c.p2  = DD_AVX_AVX_FUNC(add_pd)(c.p2, c.t2);
		c.p2  = DD_AVX_AVX_FUNC(add_pd)(c.p2, c.bl);
		c.ch  = DD_AVX_AVX_FUNC(add_pd)(c.p1, c.p2);
#endif
		a_hi  = c.ch;
		c.ch  = DD_AVX_FUNC(sub_pd)(c.ch, c.p1);
		c.p2  = DD_AVX_FUNC(sub_pd)(c.p2, c.ch);
		a_lo  = c.p2;
	}

	inline void Mul(
			double& a_hi, double& a_lo,
			const double& b_hi, const double& b_lo,
			const double& c_hi, const double& c_lo)
	{
		dd_real a, b, c;
		a.x[0] = a_hi; a.x[1] = a_lo;
		b.x[0] = b_hi; b.x[1] = b_lo;
		c.x[0] = c_hi; c.x[1] = c_lo;
		a = b * c;

		a_hi = a.x[0], a_lo = a.x[1];
	}

	inline void Mul(
			double& a_hi, 
			const double& b_hi, const double& b_lo,
			const double& c_hi, const double& c_lo)
	{
		dd_real a, b, c;
		a.x[0] = a_hi; a.x[1] = 0.0;
		b.x[0] = b_hi; b.x[1] = b_lo;
		c.x[0] = c_hi; c.x[1] = c_lo;
		a = b * c;

		a_hi = a.x[0];
	}

	inline void Muld(
			double& a_hi, double& a_lo,
			const double& b_hi, const double& b_lo,
			const double& c_hi)
	{
		dd_real a, b, c;
		a.x[0] = a_hi; a.x[1] = a_lo;
		b.x[0] = b_hi; b.x[1] = b_lo;
		c.x[0] = c_hi; c.x[1] = 0.0;
		a = b * c;

		a_hi = a.x[0];
	}

}
#endif
