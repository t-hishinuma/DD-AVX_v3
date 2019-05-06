#pragma once
#ifndef DD_AVX_CORE_ADD_HPP_
#define DD_AVX_CORE_ADD_HPP_

#include <immintrin.h>
#define DD_AVX_FUNC(NAME) _mm256_##NAME
using AVXreg = __m256d;

namespace ddavx_core{

	//d = a + b * c
	inline void Fma(
			__m256d& d_hi, __m256d& d_lo,
			const __m256d& a_hi, const __m256d& a_lo,
			const __m256d& b_hi, const __m256d& b_lo,
			const __m256d& c_hi, const __m256d& c_lo,
			registers& c
			)
	{
		bh = b_hi;
		ch = c_hi;
		bl = b_lo;
		cl = c_lo;

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

		c.t1  = DD_AVX_AVX_FUNC(sub_pd)(ch,p1); 
		c.p2  = DD_AVX_AVX_FUNC(sub_pd)(p2,t1); 
		c.bh  = a_hi; 
		c.bl  = a_lo;

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

		d_hi = c.sh;
		c.sh = DD_AVX_FUNC(sub_pd)(c.sh,c.th); 
		c.bh = DD_AVX_FUNC(sub_pd)(c.bh,c.sh);
		d_lo = c.bh;

	}

	inline void Fma(
			double& d_hi, double& d_lo,
			const double& a_hi, const double& a_lo,
			const double& b_hi, const double& b_lo,
			const double& c_hi, const double& c_lo)
	{
		dd_real a, b, c, d;
		a.x[0] = a_hi; a.x[1] = a_lo;
		b.x[0] = b_hi; b.x[1] = b_lo;
		c.x[0] = c_hi; c.x[1] = c_lo;
		d.x[0] = d_hi; d.x[1] = d_lo;
		d = a + b * c;

		d_hi = a.x[0], d_lo = a.x[1];
	}
#endif

