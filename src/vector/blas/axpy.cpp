#include<DD-AVX.hpp>
using namespace ddavx_core;

namespace dd_avx{
	void axpy(const dd_real& alpha, const dd_real_vector& x, dd_real_vector& y){
		printf("gomagoma\n");
// 		if((long)size() != (long)vec1.size() || (long)size() != (long)vec2.size()){
// 			std::cout << "error vecvor size is" << size() << vec1.size() << vec2.size() << std::endl;
// 			assert(1);
// 		};
// 		registers regs;
//
// #pragma omp parallel private(regs)
// 		{
// 			long i=0, is=0, ie=0;
// 			get_isie(size(), is, ie);
// 			for(i = is; i < ie - AVX_SIZE - 1; i += AVX_SIZE){
// 				AVXreg a_hi = load(hi[i]);
// 				AVXreg a_lo = load(lo[i]);
//
// 				AVXreg b_hi = load(vec1.hi[i]);
// 				AVXreg b_lo = load(vec1.lo[i]);
//
// 				AVXreg c_hi = load(vec2.hi[i]);
// 				AVXreg c_lo = load(vec2.lo[i]);
//
// 				Add(a_hi, a_lo, b_hi, b_lo, c_hi, c_lo, regs);
//
// 				store(hi[i], a_hi);
// 				store(lo[i], a_lo);
// 			}
// 			for(;i<ie;i++){
// 				Add(hi[i], lo[i], vec1.hi[i], vec1.lo[i], vec2.hi[i], vec2.lo[i]);
// 			}
// 		}
	}

	void axpy(const dd_real& alpha, const d_real_vector& x, dd_real_vector& y){
		printf("gomagoma\n");
	}

	void axpy(const dd_real& alpha, const dd_real_vector& x, d_real_vector& y){
		printf("gomagoma\n");
	}

	void axpy(const dd_real& alpha, const d_real_vector& x, d_real_vector& y){
		printf("gomagoma\n");
	}

	void axpy(const d_real& alpha, const dd_real_vector& x, dd_real_vector& y){
		printf("gomagoma\n");
	}

	void axpy(const d_real& alpha, const d_real_vector& x, dd_real_vector& y){
		printf("gomagoma\n");
	}

	void axpy(const d_real& alpha, const dd_real_vector& x, d_real_vector& y){
		printf("gomagoma\n");
	}

	void axpy(const d_real& alpha, const d_real_vector& x, d_real_vector& y){
		printf("gomagoma\n");
	}

}
