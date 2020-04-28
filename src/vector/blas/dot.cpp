#include<DD-AVX.hpp>
using namespace ddavx_core;

namespace dd_avx{

	dd_real dot(const dd_real_vector& x, const dd_real_vector& y){
		if(x.size() != y.size()){
			std::cerr << "error bad vector size" << std::endl;
			assert(1);
		}
		registers regs;

		dd_real dot[omp_get_max_threads()];

#pragma omp parallel private(regs)
		{
			int thN = omp_get_thread_num();
			size_t i=0, is=0, ie=0;
			get_isie((int)y.size(), is, ie);
			printf("%ld, %ld\n", is, ie);

			AVXreg r_hi = regs.zeros;
			AVXreg r_lo = regs.zeros;

			for(i = is; (int)i < (int)(ie-SIMD_Length+1); i += SIMD_Length){
				printf("a");

				AVXreg x_hi = load(x.hi[i]);
				AVXreg x_lo = load(x.lo[i]);

				AVXreg y_hi = load(y.hi[i]);
				AVXreg y_lo = load(y.lo[i]);

				Fma(r_hi, r_lo, r_hi, r_lo, x_hi, x_lo, y_hi, y_lo, regs);
			}

			dot[thN] = reduction(r_hi, r_lo);

			for(;i<ie;i++){
				Fma(dot[thN].x[0], dot[thN].x[1], dot[thN].x[0], dot[thN].x[1], x.hi[i], x.lo[i], y.hi[i], y.lo[i]);
			}
		}

		dd_real tmp = 0;
		for(int i=0; i < omp_get_max_threads() + 1; i++){
			tmp += dot[i];
		}

		return tmp;
		
	}


	dd_real dot(const d_real_vector& x, const dd_real_vector& y){
		if(x.size() != y.size()){
			std::cerr << "error bad vector size" << std::endl;
			assert(1);
		}
		registers regs;

		dd_real dot[omp_get_max_threads()];

#pragma omp parallel private(regs)
		{
			int thN = omp_get_thread_num();
			size_t i=0, is=0, ie=0;
			get_isie(y.size(), is, ie);

			AVXreg r_hi = regs.zeros;
			AVXreg r_lo = regs.zeros;

			for(i = is; (int)i < (int)(ie-SIMD_Length+1); i += SIMD_Length){

				AVXreg x_hi = load(x.data()[i]);

				AVXreg y_hi = load(y.hi[i]);
				AVXreg y_lo = load(y.lo[i]);

				Fmad(r_hi, r_lo, r_hi, r_lo, y_hi, y_lo, x_hi, regs);
			}

			dot[thN] = reduction(r_hi, r_lo);

			for(;i<ie;i++){
				Fmad(dot[thN].x[0], dot[thN].x[1], dot[thN].x[0], dot[thN].x[1], y.hi[i], y.lo[i], x.data()[i]);
			}
		}

		dd_real tmp = 0;
		for(int i=0; i < omp_get_max_threads() + 1; i++){
			tmp += dot[i];
		}

		return tmp;
		
	}

	dd_real dot(const dd_real_vector& x, const d_real_vector& y){
		if(x.size() != y.size()){
			std::cerr << "error bad vector size" << std::endl;
			assert(1);
		}
		registers regs;

		dd_real dot[omp_get_max_threads()];

#pragma omp parallel private(regs)
		{
			int thN = omp_get_thread_num();
			size_t i=0, is=0, ie=0;
			get_isie(y.size(), is, ie);

			AVXreg r_hi = regs.zeros;
			AVXreg r_lo = regs.zeros;

			for(i = is; (int)i < (int)(ie-SIMD_Length+1); i += SIMD_Length){

				AVXreg x_hi = load(x.hi[i]);
				AVXreg x_lo = load(x.lo[i]);

				AVXreg y_hi = load(y.data()[i]);


				Fmad(r_hi, r_lo, r_hi, r_lo, x_hi, x_lo, y_hi, regs);
			}

			dot[thN] = reduction(r_hi, r_lo);

			for(;i<ie;i++){
				Fmad(dot[thN].x[0], dot[thN].x[1], dot[thN].x[0], dot[thN].x[1], x.hi[i], x.lo[i], y.data()[i]);
			}
		}

		dd_real tmp = 0;
		for(int i=0; i < omp_get_max_threads() + 1; i++){
			tmp += dot[i];
		}

		return tmp;
	}

	dd_real dot(const d_real_vector& x, const d_real_vector& y){
		if(x.size() != y.size()){
			std::cerr << "error bad vector size" << std::endl;
			assert(1);
		}
		registers regs;

		dd_real dot[omp_get_max_threads()];

#pragma omp parallel private(regs)
		{
			int thN = omp_get_thread_num();
			size_t i=0, is=0, ie=0;
			get_isie(y.size(), is, ie);

			AVXreg r_hi = regs.zeros;
			AVXreg r_lo = regs.zeros;

			for(i = is; (int)i < (int)(ie-SIMD_Length+1); i += SIMD_Length){

				AVXreg x_hi = load(x.data()[i]);
				AVXreg x_lo = regs.zeros;

				AVXreg y_hi = load(y.data()[i]);


				Fmad(r_hi, r_lo, r_hi, r_lo, x_hi, x_lo, y_hi, regs);
			}

			dot[thN] = reduction(r_hi, r_lo);

			for(;i<ie;i++){
				Fmad(dot[thN].x[0], dot[thN].x[1], dot[thN].x[0], dot[thN].x[1], x.data()[i], 0.0, y.data()[i]);
			}
		}

		dd_real tmp = 0;
		for(int i=0; i < omp_get_max_threads() + 1; i++){
			tmp += dot[i];
		}

		return tmp;
	}
}
