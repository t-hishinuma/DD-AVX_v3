#pragma once
#ifndef DD_AVX_CORE_HPP_
#define DD_AVX_CORE_HPP_

#include <immintrin.h>
#define DD_AVX_FUNC(NAME) _mm256_##NAME
using SIMDreg = __m256d;
struct dd_real;

namespace ddavx_core{
	const size_t SIMD_Length=4;
	class registers{
		public:
			double splitter = 134217729.0;
			SIMDreg sp = DD_AVX_FUNC(broadcast_sd)(&splitter); 
			SIMDreg minus = DD_AVX_FUNC(set_pd)(-1.0,-1.0,-1.0,-1.0);
			SIMDreg zeros = DD_AVX_FUNC(set_pd)(0,0,0,0);
			SIMDreg one,bh,bl,ch,cl,sh,sl,wh,wl,th,tl,p1,p2,t0,t1,t2,eh,t3; 
	};


	//load
	inline SIMDreg load(const double& val){
		return DD_AVX_FUNC(loadu_pd)((double*)&(val)); 
	}

	//set
	inline SIMDreg set(const double a, const double b, const double c, const double d){
		SIMDreg ret = DD_AVX_FUNC(set_pd)(a, b, c, d);
		return ret;
	}

	//broadcast
	inline SIMDreg broadcast(const double a){
		SIMDreg ret = DD_AVX_FUNC(broadcast_sd)(&a); 
		return ret;
	}

	//store
	inline void store(double& ret, const SIMDreg val){
		DD_AVX_FUNC(storeu_pd)((double*)&(ret), val);
	}

	inline dd_real reduction(SIMDreg a_hi, SIMDreg a_lo){
		double hi[4];
		double lo[4];
		DD_AVX_FUNC(storeu_pd)((double*)&(hi), a_hi); 
		DD_AVX_FUNC(storeu_pd)((double*)&(lo), a_lo); 
		dd_real a; a.x[0] = hi[0]; a.x[1] = lo[0];
		dd_real b; b.x[0] = hi[1]; b.x[1] = lo[1];
		dd_real c; c.x[0] = hi[2]; c.x[1] = lo[2];
		dd_real d; d.x[0] = hi[3]; d.x[1] = lo[3];

		return d + a + b + c;
	}

	inline void store(double& ret1, double& ret2, double& ret3, double& ret4, const SIMDreg val){
		double tmp[4];
		DD_AVX_FUNC(storeu_pd)((double*)&(tmp), val); 
		ret1 = tmp[0];
		ret2 = tmp[1];
		ret3 = tmp[2];
		ret4 = tmp[3];
	}

	inline void print(SIMDreg a){
		double tmp[4];
		DD_AVX_FUNC(storeu_pd)((double*)&(tmp), a); 
		printf("%f, %f, %f, %f\n", tmp[0], tmp[1], tmp[2], tmp[3]);
	
	}

	//isie
	inline void get_isie(size_t size, size_t& is, size_t& ie){
		size_t maxid = omp_get_max_threads();
		size_t tid = omp_get_thread_num();

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
	inline void to_minus(double& val, registers& regs){
		SIMDreg reg = load(val);
 		reg = DD_AVX_FUNC(mul_pd)(reg, regs.minus);
 		store(val, reg);
	}

	inline void to_minus(SIMDreg& reg, registers& regs){
 		reg = DD_AVX_FUNC(mul_pd)(reg, regs.minus);
	}
}
#endif
