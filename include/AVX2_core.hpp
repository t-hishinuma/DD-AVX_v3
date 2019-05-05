#pragma once
#ifndef DD_AVX_CORE_HPP_
#define DD_AVX_CORE_HPP_

#include <immintrin.h>
#define DD_AVX_FUNC(NAME) _mm256_##NAME
using AVXreg = __m256d;

namespace ddavx_core{
	const long AVX_SIZE=4;
	class registers{
		public:
			double splitter = 134217729.0;
			__m256d sp = DD_AVX_FUNC(broadcast_sd)(&splitter); 
			__m256d mi = DD_AVX_FUNC(set_pd)(-1.0,-1.0,-1.0,-1.0);
			__m256d zeros = DD_AVX_FUNC(set_pd)(0,0,0,0);
			__m256d one,bh,bl,ch,cl,sh,sl,wh,wl,th,tl,p1,p2,t0,t1,t2,eh,t3; 
	};


	//load
	inline __m256d load(const double& val){
		return DD_AVX_FUNC(loadu_pd)((double*)&(val)); 
	}

	//set
	inline __m256d set(const double a, const double b, const double c, const double d){
		__m256d ret = DD_AVX_FUNC(set_pd)(a, b, c, d);
		return ret;
	}

	//broadcast
	inline __m256d broadcast(const double a){
		__m256d ret = DD_AVX_FUNC(broadcast_sd)(&a); 
		return ret;
	}

	//store
	inline void store(double& ret, const __m256d val){
		DD_AVX_FUNC(storeu_pd)((double*)&(ret), val);
	}

	inline void store(double& ret1, double& ret2, double& ret3, double& ret4, const __m256d val){
		double tmp[4];
		DD_AVX_FUNC(storeu_pd)((double*)&(tmp), val); 
		ret1 = tmp[0];
		ret2 = tmp[1];
		ret3 = tmp[2];
		ret4 = tmp[3];
	}

	//isie
	inline void get_isie(long size, long& is, long& ie){
		int maxid = omp_get_max_threads();
		int tid = omp_get_thread_num();

		if( tid < (size % maxid) ) 
		{ 
			ie = size / maxid+1; 
			is = ie * tid; 
		} 
		else 
		{ 
			ie = size / maxid; 
			is = ie * tid + size % maxid; 
		} 
		ie = ie + is;
	}


	//Add
	inline void Add(
			__m256d& a_hi, __m256d& a_lo,
			const __m256d& b_hi, const __m256d& b_lo,
			const __m256d& c_hi, const __m256d& c_lo,
			registers c
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
			registers c
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
