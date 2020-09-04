#pragma once
#ifndef DD_AVX_CORE_HPP_
#define DD_AVX_CORE_HPP_

#include <immintrin.h>
#define SIMD_FUNC(NAME) _mm256_##NAME
using SIMDreg = __m256d;
struct dd_real;

namespace ddavx_core{
	const size_t SIMD_Length=4;
	class registers{
		public:
			double splitter = 134217729.0;
			SIMDreg sp = SIMD_FUNC(broadcast_sd)(&splitter); 
			SIMDreg minus = SIMD_FUNC(set_pd)(-1.0,-1.0,-1.0,-1.0);
			SIMDreg zeros = SIMD_FUNC(set_pd)(0,0,0,0);
			SIMDreg one,bh,bl,ch,cl,sh,sl,wh,wl,th,tl,p1,p2,t0,t1,t2,eh,t3; 
	};


	/////////////////////////////////////////////
	//core functions
	////////////////////////////////////////////
	
	//load
	inline SIMDreg load(const double& val){
		return SIMD_FUNC(loadu_pd)((double*)&(val)); 
	}

	//set
	inline SIMDreg set(const double a, const double b, const double c, const double d){
		SIMDreg ret = SIMD_FUNC(set_pd)(a, b, c, d);
		return ret;
	}

	//broadcast
	inline SIMDreg broadcast(const double a){
		SIMDreg ret = SIMD_FUNC(broadcast_sd)(&a); 
		return ret;
	}

	//store
	inline void store(double& ret, const SIMDreg val){
		SIMD_FUNC(storeu_pd)((double*)&(ret), val);
	}

	// add
	inline SIMDreg add(const SIMDreg a, const SIMDreg b){
		return SIMD_FUNC(add_pd)(a, b);
	}

	// mul
	inline SIMDreg mul(const SIMDreg a, const SIMDreg b){
		return SIMD_FUNC(mul_pd)(a, b);
	}

	// sub
	inline SIMDreg sub(const SIMDreg a, const SIMDreg b){
		return SIMD_FUNC(sub_pd)(a, b);
	}

	// div
	inline SIMDreg div(const SIMDreg a, const SIMDreg b){
		return SIMD_FUNC(div_pd)(a, b);
	}

	// fmadd
	inline SIMDreg fmadd(const SIMDreg a, const SIMDreg b, const SIMDreg c){
		return SIMD_FUNC(fmadd_pd)(a, b, c);
	}


	/////////////////////////////////////////////
	// special functions
	////////////////////////////////////////////
	
	// need to change for AVX512
	inline dd_real reduction(SIMDreg a_hi, SIMDreg a_lo){
		double hi[4];
		double lo[4];
		store(*hi, a_hi); 
		store(*lo, a_lo); 

		dd_real a; a.x[0] = hi[0]; a.x[1] = lo[0];
		dd_real b; b.x[0] = hi[1]; b.x[1] = lo[1];
		dd_real c; c.x[0] = hi[2]; c.x[1] = lo[2];
		dd_real d; d.x[0] = hi[3]; d.x[1] = lo[3];

		return a + b + c + d;
	}

	// need to change for AVX512
	inline void store(double& ret1, double& ret2, double& ret3, double& ret4, const SIMDreg val){
		double tmp[4];
		store(*tmp, val); 
		ret1 = tmp[0];
		ret2 = tmp[1];
		ret3 = tmp[2];
		ret4 = tmp[3];
	}

	inline void print(SIMDreg a){
		double tmp[SIMD_Length];
		store(*tmp, a); 
		for(size_t i=0; i<SIMD_Length; i++){
			printf("%f ", tmp[i]);
		}
		printf("\n");
	
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
 		reg = mul(reg, regs.minus);
 		store(val, reg);
	}

	inline void to_minus(SIMDreg& reg, registers& regs){
 		reg = mul(reg, regs.minus);
	}
}
#endif
