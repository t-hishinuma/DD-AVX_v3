#include<DD-AVX_internal.hpp>
using namespace ddavx_core;

namespace dd_avx{
//alpha = DD ///////////////////////////////////////////
	void axpy(const dd_real& alpha, const dd_real_vector& x, dd_real_vector& y){
		if(x.size() != y.size()){
			std::cerr << "error bad vector size" << std::endl;
			assert(1);
		}
 		registers regs;

#pragma omp parallel private(regs)
		{
			int i=0, is=0, ie=0;
			get_isie(y.size(), is, ie);
			reg alpha_hi = broadcast(alpha.x[0]);
			reg alpha_lo = broadcast(alpha.x[1]);
			for(i = is; i < (ie-SIMD_Length+1); i += SIMD_Length){

				reg x_hi = load(x.hi[i]);
				reg x_lo = load(x.lo[i]);

				reg y_hi = load(y.hi[i]);
				reg y_lo = load(y.lo[i]);

				Fma(y_hi, y_lo, y_hi, y_lo, alpha_hi, alpha_lo, x_hi, x_lo, regs);

				store(y.hi[i], y_hi);
				store(y.lo[i], y_lo);
			}
			for(;i<ie;i++){
				Fma(y.hi[i], y.lo[i], y.hi[i], y.lo[i], alpha.x[0], alpha.x[1], x.hi[i], x.lo[i]);
			}
		}
	}

	void axpy(const dd_real& alpha, const d_real_vector& x, dd_real_vector& y){
		if(x.size() != y.size()){
			std::cerr << "error bad vector size" << std::endl;
			assert(1);
		}
 		registers regs;

#pragma omp parallel private(regs)
		{
			int i=0, is=0, ie=0;
			get_isie(y.size(), is, ie);
			reg alpha_hi = broadcast(alpha.x[0]);
			reg alpha_lo = broadcast(alpha.x[1]);
			for(i = is; i < (ie-SIMD_Length+1); i += SIMD_Length){

				reg x_hi = load(x.data()[i]);

				reg y_hi = load(y.hi[i]);
				reg y_lo = load(y.lo[i]);

				Fmad(y_hi, y_lo, y_hi, y_lo, alpha_hi, alpha_lo, x_hi, regs);

				store(y.hi[i], y_hi);
				store(y.lo[i], y_lo);
			}
			for(;i<ie;i++){
				Fmad(y.hi[i], y.lo[i], y.hi[i], y.lo[i], alpha.x[0], alpha.x[1], x.data()[i]);
			}
		}
	}

	void axpy(const dd_real& alpha, const dd_real_vector& x, d_real_vector& y){
		if(x.size() != y.size()){
			std::cerr << "error bad vector size" << std::endl;
			assert(1);
		}
 		registers regs;

#pragma omp parallel private(regs)
		{
			int i=0, is=0, ie=0;
			get_isie(y.size(), is, ie);
			reg alpha_hi = broadcast(alpha.x[0]);
			reg alpha_lo = broadcast(alpha.x[1]);
			for(i = is; i < (ie-SIMD_Length+1); i += SIMD_Length){

				reg x_hi = load(x.hi[i]);
				reg x_lo = load(x.lo[i]);

				reg y_hi = load(y.data()[i]);
				reg y_lo = regs.zeros;

				Fma(y_hi, y_hi, y_lo, alpha_hi, alpha_lo, x_hi, x_lo, regs);

				store(y.data()[i], y_hi);
			}
			for(;i<ie;i++){
				Fma(y.data()[i], y.data()[i], 0.0, alpha.x[0], alpha.x[1], x.hi[i], x.lo[i]);
			}
		}
	}

	void axpy(const dd_real& alpha, const d_real_vector& x, d_real_vector& y){
		if(x.size() != y.size()){
			std::cerr << "error bad vector size" << std::endl;
			assert(1);
		}
 		registers regs;

#pragma omp parallel private(regs)
		{
			int i=0, is=0, ie=0;
			get_isie(y.size(), is, ie);
			reg alpha_hi = broadcast(alpha.x[0]);
			reg alpha_lo = broadcast(0.0);
			for(i = is; i < (ie-SIMD_Length+1); i += SIMD_Length){

				reg x_hi = load(x.data()[i]);

				reg y_hi = load(y.data()[i]);
				reg y_lo = regs.zeros;

				Fmad(y_hi, y_lo, y_hi, y_lo, alpha_hi, alpha_lo, x_hi, regs);

				store(y.data()[i], y_hi);
			}
			for(;i<ie;i++){
				Fma(y.data()[i], y.data()[i], 0.0, alpha.x[0], alpha.x[1], x.data()[i], 0.0);
			}
		}
	}

//alpha = D ///////////////////////////////////////////
	void axpy(const d_real& alpha, const dd_real_vector& x, dd_real_vector& y){
		if(x.size() != y.size()){
			std::cerr << "error bad vector size" << std::endl;
			assert(1);
		}
 		registers regs;

#pragma omp parallel private(regs)
		{
			int i=0, is=0, ie=0;
			get_isie(y.size(), is, ie);
			reg alpha_hi = broadcast(alpha);
			reg alpha_lo = broadcast(0.0);
			for(i = is; i < (ie-SIMD_Length+1); i += SIMD_Length){

				reg x_hi = load(x.hi[i]);
				reg x_lo = load(x.lo[i]);

				reg y_hi = load(y.hi[i]);
				reg y_lo = load(y.lo[i]);

				Fmad(y_hi, y_lo, y_hi, y_lo, x_hi, x_lo, alpha_hi, regs);

				store(y.hi[i], y_hi);
				store(y.lo[i], y_lo);
			}
			for(;i<ie;i++){
				Fma(y.hi[i], y.lo[i], y.hi[i], y.lo[i], alpha, 0.0, x.hi[i], x.lo[i]);
			}
		}
	}

	void axpy(const d_real& alpha, const d_real_vector& x, dd_real_vector& y){
		if(x.size() != y.size()){
			std::cerr << "error bad vector size" << std::endl;
			assert(1);
		}
 		registers regs;

#pragma omp parallel private(regs)
		{
			int i=0, is=0, ie=0;
			get_isie(y.size(), is, ie);
			reg alpha_hi = broadcast(alpha);
			reg alpha_lo = broadcast(0.0);
			for(i = is; i < (ie-SIMD_Length+1); i += SIMD_Length){

				reg x_hi = load(x.data()[i]);
				reg x_lo = regs.zeros;

				reg y_hi = load(y.hi[i]);
				reg y_lo = load(y.lo[i]);

				Fmad(y_hi, y_lo, y_hi, y_lo, x_hi, x_lo, alpha_hi, regs);

				store(y.hi[i], y_hi);
				store(y.lo[i], y_lo);
			}
			for(;i<ie;i++){
				Fma(y.hi[i], y.lo[i], y.hi[i], y.lo[i], alpha, 0.0, x.data()[i], 0.0);
			}
		}
	}

	void axpy(const d_real& alpha, const dd_real_vector& x, d_real_vector& y){
		if(x.size() != y.size()){
			std::cerr << "error bad vector size" << std::endl;
			assert(1);
		}
 		registers regs;

#pragma omp parallel private(regs)
		{
			int i=0, is=0, ie=0;
			get_isie(y.size(), is, ie);
			reg alpha_hi = broadcast(alpha);
			reg alpha_lo = broadcast(0.0);
			for(i = is; i < (ie-SIMD_Length+1); i += SIMD_Length){

				reg x_hi = load(x.hi[i]);
				reg x_lo = load(x.lo[i]);

				reg y_hi = load(y.data()[i]);
				reg y_lo = regs.zeros;

				Fmad(y_hi, y_lo, y_hi, y_lo, x_hi, x_lo, alpha_hi, regs);

				store(y.data()[i], y_hi);
			}
			for(;i<ie;i++){
				Fma(y.data()[i], y.data()[i], 0.0, alpha, 0.0, x.hi[i], x.lo[i]);
			}
		}
	}

	void axpy(const d_real& alpha, const d_real_vector& x, d_real_vector& y){
		if(x.size() != y.size()){
			std::cout << "error vecvor size is" << x.size() << y.size() << std::endl;
			assert(1);
		}

#pragma omp parallel for
		for(int i = 0 ; i<y.size();i++){
			y.data()[i] = y.data()[i] + alpha * x.data()[i];
		}
	}
}
