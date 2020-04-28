#include<DD-AVX.hpp>
using namespace ddavx_core;
//y = x + ay

namespace dd_avx{
//alpha = DD ///////////////////////////////////////////
	void xpay(const dd_real& alpha, const dd_real_vector& x, dd_real_vector& y){
		if(x.size() != y.size()){
			std::cerr << "error bad vector size" << std::endl;
			assert(1);
		}
 		registers regs;

#pragma omp parallel private(regs)
		{
			size_t i=0, is=0, ie=0;
			get_isie(y.size(), is, ie);
			AVXreg alpha_hi = broadcast(alpha.x[0]);
			AVXreg alpha_lo = broadcast(alpha.x[1]);
			for(i = is; (int)i < (int)(ie-SIMD_Length+1); i += SIMD_Length){

				AVXreg x_hi = load(x.hi[i]);
				AVXreg x_lo = load(x.lo[i]);

				AVXreg y_hi = load(y.hi[i]);
				AVXreg y_lo = load(y.lo[i]);

				Fma(y_hi, y_lo, x_hi, x_lo, alpha_hi, alpha_lo, y_hi, y_lo, regs);

				store(y.hi[i], y_hi);
				store(y.lo[i], y_lo);
			}
			for(;i<ie;i++){
				Fma(y.hi[i], y.lo[i], x.hi[i], x.lo[i], alpha.x[0], alpha.x[1], y.hi[i], y.lo[i]);
			}
		}
	}

	void xpay(const dd_real& alpha, const d_real_vector& x, dd_real_vector& y){
		if(x.size() != y.size()){
			std::cerr << "error bad vector size" << std::endl;
			assert(1);
		}
 		registers regs;

#pragma omp parallel private(regs)
		{
			size_t i=0, is=0, ie=0;
			get_isie(y.size(), is, ie);
			AVXreg alpha_hi = broadcast(alpha.x[0]);
			AVXreg alpha_lo = broadcast(alpha.x[1]);
			for(i = is; (int)i < (int)(ie-SIMD_Length+1); i += SIMD_Length){

				AVXreg x_hi = load(x.data()[i]);
				AVXreg x_lo = regs.zeros;

				AVXreg y_hi = load(y.hi[i]);
				AVXreg y_lo = load(y.lo[i]);

				Fma(y_hi, y_lo, x_hi, x_lo, alpha_hi, alpha_lo, y_hi, y_lo, regs);

				store(y.hi[i], y_hi);
				store(y.lo[i], y_lo);
			}
			for(;i<ie;i++){
				Fma(y.hi[i], y.lo[i], x.data()[i], 0.0, alpha.x[0], alpha.x[1], y.hi[i], y.lo[i]);
			}
		}
	}

	void xpay(const dd_real& alpha, const dd_real_vector& x, d_real_vector& y){
		if(x.size() != y.size()){
			std::cerr << "error bad vector size" << std::endl;
			assert(1);
		}
 		registers regs;

#pragma omp parallel private(regs)
		{
			size_t i=0, is=0, ie=0;
			get_isie(y.size(), is, ie);
			AVXreg alpha_hi = broadcast(alpha.x[0]);
			AVXreg alpha_lo = broadcast(alpha.x[1]);
			for(i = is; (int)i < (int)(ie-SIMD_Length+1); i += SIMD_Length){

				AVXreg x_hi = load(x.hi[i]);
				AVXreg x_lo = load(x.lo[i]);

				AVXreg y_hi = load(y.data()[i]);
				AVXreg y_lo = regs.zeros;

				Fma(y_hi, y_lo, x_hi, x_lo, alpha_hi, alpha_lo, y_hi, y_lo, regs);

				store(y.data()[i], y_hi);
			}
			for(;i<ie;i++){
				Fma(y.data()[i], x.hi[i], x.lo[i], alpha.x[0], alpha.x[1], y.data()[i], 0.0);
			}
		}
	}

	void xpay(const dd_real& alpha, const d_real_vector& x, d_real_vector& y){
		if(x.size() != y.size()){
			std::cerr << "error bad vector size" << std::endl;
			assert(1);
		}
 		registers regs;

#pragma omp parallel private(regs)
		{
			size_t i=0, is=0, ie=0;
			get_isie(y.size(), is, ie);
			AVXreg alpha_hi = broadcast(alpha.x[0]);
			AVXreg alpha_lo = broadcast(alpha.x[1]);
			for(i = is; (int)i < (int)(ie-SIMD_Length+1); i += SIMD_Length){

				AVXreg x_hi = load(x.data()[i]);
				AVXreg x_lo = regs.zeros;

				AVXreg y_hi = load(y.data()[i]);
				AVXreg y_lo = regs.zeros;

				Fma(y_hi, y_lo, x_hi, x_lo, alpha_hi, alpha_lo, y_hi, y_lo, regs);

				store(y.data()[i], y_hi);
			}
			for(;i<ie;i++){
				Fma(y.data()[i], x.data()[i], 0.0, alpha.x[0], alpha.x[1], y.data()[i], 0.0);
			}
		}
	}

//alpha = D ///////////////////////////////////////////
	void xpay(const d_real& alpha, const dd_real_vector& x, dd_real_vector& y){
		if(x.size() != y.size()){
			std::cerr << "error bad vector size" << std::endl;
			assert(1);
		}
 		registers regs;

#pragma omp parallel private(regs)
		{
			size_t i=0, is=0, ie=0;
			get_isie(y.size(), is, ie);
			AVXreg alpha_hi = broadcast(alpha);
			AVXreg alpha_lo = regs.zeros;
			for(i = is; (int)i < (int)(ie-SIMD_Length+1); i += SIMD_Length){

				AVXreg x_hi = load(x.hi[i]);
				AVXreg x_lo = load(x.lo[i]);

				AVXreg y_hi = load(y.hi[i]);
				AVXreg y_lo = load(y.lo[i]);

				Fma(y_hi, y_lo, x_hi, x_lo, alpha_hi, alpha_lo, y_hi, y_lo, regs);

				store(y.hi[i], y_hi);
				store(y.lo[i], y_lo);
			}
			for(;i<ie;i++){
				Fma(y.hi[i], y.lo[i], x.hi[i], x.lo[i], alpha, 0.0, y.hi[i], y.lo[i]);
			}
		}
	}

	void xpay(const d_real& alpha, const d_real_vector& x, dd_real_vector& y){
		if(x.size() != y.size()){
			std::cerr << "error bad vector size" << std::endl;
			assert(1);
		}
 		registers regs;

#pragma omp parallel private(regs)
		{
			size_t i=0, is=0, ie=0;
			get_isie(y.size(), is, ie);
			AVXreg alpha_hi = broadcast(alpha);
			AVXreg alpha_lo = regs.zeros;
			for(i = is; (int)i < (int)(ie-SIMD_Length+1); i += SIMD_Length){

				AVXreg x_hi = load(x.data()[i]);
				AVXreg x_lo = regs.zeros;

				AVXreg y_hi = load(y.hi[i]);
				AVXreg y_lo = load(y.lo[i]);

				Fma(y_hi, y_lo, x_hi, x_lo, alpha_hi, alpha_lo, y_hi, y_lo, regs);

				store(y.hi[i], y_hi);
				store(y.lo[i], y_lo);
			}
			for(;i<ie;i++){
				Fma(y.hi[i], y.lo[i], x.data()[i], 0.0, alpha, 0.0, y.hi[i], y.lo[i]);
			}
		}
	}

	void xpay(const d_real& alpha, const dd_real_vector& x, d_real_vector& y){
		if(x.size() != y.size()){
			std::cerr << "error bad vector size" << std::endl;
			assert(1);
		}
 		registers regs;

#pragma omp parallel private(regs)
		{
			size_t i=0, is=0, ie=0;
			get_isie(y.size(), is, ie);
			AVXreg alpha_hi = broadcast(alpha);
			AVXreg alpha_lo = regs.zeros;
			for(i = is; (int)i < (int)(ie-SIMD_Length+1); i += SIMD_Length){

				AVXreg x_hi = load(x.hi[i]);
				AVXreg x_lo = load(x.lo[i]);

				AVXreg y_hi = load(y.data()[i]);
				AVXreg y_lo = regs.zeros;

				Fma(y_hi, y_lo, x_hi, x_lo, alpha_hi, alpha_lo, y_hi, y_lo, regs);

				store(y.data()[i], y_hi);
			}
			for(;i<ie;i++){
				Fma(y.data()[i], x.hi[i], x.lo[i], alpha, 0.0, y.data()[i], 0.0);
			}
		}
	}

	void xpay(const d_real& alpha, const d_real_vector& x, d_real_vector& y){
		if(x.size() != y.size()){
			std::cerr << "error bad vector size" << std::endl;
			assert(1);
		}
 		registers regs;

#pragma omp parallel private(regs)
		{
			size_t i=0, is=0, ie=0;
			get_isie(y.size(), is, ie);
			AVXreg alpha_hi = broadcast(alpha);
			AVXreg alpha_lo = regs.zeros;
			for(i = is; (int)i < (int)(ie-SIMD_Length+1); i += SIMD_Length){

				AVXreg x_hi = load(x.data()[i]);
				AVXreg x_lo = regs.zeros;

				AVXreg y_hi = load(y.data()[i]);
				AVXreg y_lo = regs.zeros;

				Fma(y_hi, y_lo, x_hi, x_lo, alpha_hi, alpha_lo, y_hi, y_lo, regs);

				store(y.data()[i], y_hi);
			}
			for(;i<ie;i++){
				Fma(y.data()[i], x.data()[i], 0.0, alpha, 0.0, y.data()[i], 0.0);
			}
		}
	}
}
