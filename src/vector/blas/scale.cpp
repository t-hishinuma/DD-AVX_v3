#include<DD-AVX_internal.hpp>
using namespace ddavx_core;

namespace dd_avx{
	void scale(const dd_real& alpha, dd_real_vector& x){
 		registers regs;

#pragma omp parallel private(regs)
		{
			int i=0, is=0, ie=0;
			get_isie(x.size(), is, ie);
			reg alpha_hi = broadcast(alpha.x[0]);
			reg alpha_lo = broadcast(alpha.x[1]);
			for(i = is; i < (ie-SIMD_Length+1); i += SIMD_Length){

				reg x_hi = load(x.hi[i]);
				reg x_lo = load(x.lo[i]);

				Mul(x_hi, x_lo, alpha_hi, alpha_lo, x_hi, x_lo, regs);

				store(x.hi[i], x_hi);
				store(x.lo[i], x_lo);
			}
			for(;i<ie;i++){
				Mul(x.hi[i], x.lo[i], alpha.x[0], alpha.x[1], x.hi[i], x.lo[i]);
			}
		}
	}

	void scale(const d_real& alpha, dd_real_vector& x){
 		registers regs;

#pragma omp parallel private(regs)
		{
			int i=0, is=0, ie=0;
			get_isie(x.size(), is, ie);
			reg alpha_hi = broadcast(alpha);
			reg alpha_lo = regs.zeros;
			for(i = is; i < (ie-SIMD_Length+1); i += SIMD_Length){

				reg x_hi = load(x.hi[i]);
				reg x_lo = load(x.lo[i]);

				Mul(x_hi, x_lo, alpha_hi, alpha_lo, x_hi, x_lo, regs);

				store(x.hi[i], x_hi);
				store(x.lo[i], x_lo);
			}
			for(;i<ie;i++){
				Mul(x.hi[i], x.lo[i], alpha, 0.0, x.hi[i], x.lo[i]);
			}
		}
	}

	void scale(const dd_real& alpha, d_real_vector& x){
 		registers regs;

#pragma omp parallel private(regs)
		{
			int i=0, is=0, ie=0;
			get_isie(x.size(), is, ie);
			reg alpha_hi = broadcast(alpha.x[0]);
			reg alpha_lo = broadcast(alpha.x[1]);
			for(i = is; i < (ie-SIMD_Length+1); i += SIMD_Length){

				reg x_hi = load(x.data()[i]);
				reg x_lo = regs.zeros;

				Mul(x_hi, x_lo, alpha_hi, alpha_lo, x_hi, x_lo, regs);

				store(x.data()[i], x_hi);
			}
			for(;i<ie;i++){
				Mul(x.data()[i],  alpha.x[0], alpha.x[1], x.data()[i], 0.0);
			}
		}
	}

	void scale(const d_real& alpha, d_real_vector& x){
 		registers regs;

#pragma omp parallel private(regs)
		{
			int i=0, is=0, ie=0;
			get_isie(x.size(), is, ie);
			reg alpha_hi = broadcast(alpha);
			reg alpha_lo = regs.zeros;
			for(i = is; i < (ie-SIMD_Length+1); i += SIMD_Length){

				reg x_hi = load(x.data()[i]);
				reg x_lo = regs.zeros;

				Mul(x_hi, x_lo, alpha_hi, alpha_lo, x_hi, x_lo, regs);

				store(x.data()[i], x_hi);
			}
			for(;i<ie;i++){
				Mul(x.data()[i],  alpha, 0.0, x.data()[i], 0.0);
			}
		}
	}
}
