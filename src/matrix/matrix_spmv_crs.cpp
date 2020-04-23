#include<DD-AVX.hpp>
using namespace ddavx_core;

namespace dd_avx{
	// D, DD, DD
	void matvec(const d_real_SpMat& A, const dd_real_vector& x, dd_real_vector& y){
		if((size_t)x.size() != (size_t)y.size()){
			std::cerr << "error bad vector size" << std::endl;
			assert(1);
		}
		if((size_t)x.size() != (size_t)A.get_row()){
			std::cerr << "error bad matrix size" << std::endl;
			assert(1);
		}

		registers regs;

#pragma omp parallel for schedule(guided) private(regs)
		for(size_t i=0; i<A.get_row(); i++){
			AVXreg y_hi = regs.zeros;
			AVXreg y_lo = regs.zeros;
			size_t j = 0;

			for(j = A.row_ptr[i]; j < A.row_ptr[i+1] - (SIMD_Length-1); j+=SIMD_Length){

				AVXreg x_hi = set(x.hi[A.col_ind[j+0]], x.hi[A.col_ind[j+1]], x.hi[A.col_ind[j+2]], x.hi[A.col_ind[j+3]]);
				AVXreg x_lo = set(x.lo[A.col_ind[j+0]], x.lo[A.col_ind[j+1]], x.lo[A.col_ind[j+2]], x.lo[A.col_ind[j+3]]);

				AVXreg Areg = load(A.val[j]);

				Fmad(y_hi, y_lo, y_hi, y_lo, x_hi, x_lo, Areg, regs);
			}

			// Fraction Processing (SIMD_Length=4)
			// ここは関数化したいな．．
			if(j == A.row_ptr[i+1]-3){
				AVXreg x_hi = set(0.0, x.hi[A.col_ind[j+2]], x.hi[A.col_ind[j+1]], x.hi[A.col_ind[j+0]]);
				AVXreg x_lo = set(0.0, x.lo[A.col_ind[j+2]], x.lo[A.col_ind[j+1]], x.lo[A.col_ind[j+0]]);

				AVXreg Areg = load(A.val[j]);

				Fmad(y_hi, y_lo, y_hi, y_lo, x_hi, x_lo, Areg, regs);
				j+=3;
			}

			if(j == A.row_ptr[i+1]-2){
				AVXreg x_hi = set(0.0, 0.0, x.hi[A.col_ind[j+1]], x.hi[A.col_ind[j+0]]);
				AVXreg x_lo = set(0.0, 0.0, x.lo[A.col_ind[j+1]], x.lo[A.col_ind[j+0]]);

				AVXreg Areg = load(A.val[j]);
				Fmad(y_hi, y_lo, y_hi, y_lo, x_hi, x_lo, Areg, regs);
				j+=2;
			}

			if(j == A.row_ptr[i+1]-1){
				AVXreg x_hi = set(0.0, 0.0, 0.0, x.hi[A.col_ind[j+0]]);
				AVXreg x_lo = set(0.0, 0.0, 0.0, x.lo[A.col_ind[j+0]]);

				AVXreg Areg = load(A.val[j]);
				Fmad(y_hi, y_lo, y_hi, y_lo, x_hi, x_lo, Areg, regs);
				j+=1;
			}

			y[i] = reduction(y_hi, y_lo);
		}
	}

	// D, D, DD
	void matvec(const d_real_SpMat& A, const d_real_vector& x, dd_real_vector& y){
		if((size_t)x.size() != (size_t)y.size()){
			std::cerr << "error bad vector size" << std::endl;
			assert(1);
		}
		if((size_t)x.size() != (size_t)A.get_row()){
			std::cerr << "error bad matrix size" << std::endl;
			assert(1);
		}

		registers regs;

#pragma omp parallel for schedule(guided) private(regs)
		for(size_t i=0; i<A.get_row(); i++){
			AVXreg y_hi = regs.zeros;
			AVXreg y_lo = regs.zeros;
			size_t j = 0;

			for(j = A.row_ptr[i]; j < A.row_ptr[i+1] - (SIMD_Length-1); j+=SIMD_Length){

				AVXreg x_hi = set(x[A.col_ind[j+0]], x[A.col_ind[j+1]], x[A.col_ind[j+2]], x[A.col_ind[j+3]]);
				AVXreg x_lo = regs.zeros;

				AVXreg Areg = load(A.val[j]);

				Fmad(y_hi, y_lo, y_hi, y_lo, x_hi, x_lo, Areg, regs);
			}

			//Fraction Processing
			if(j == A.row_ptr[i+1]-3){
				AVXreg x_hi = set(0.0, x[A.col_ind[j+2]], x[A.col_ind[j+1]], x[A.col_ind[j+0]]);
				AVXreg x_lo = regs.zeros;

				AVXreg Areg = load(A.val[j]);

				Fmad(y_hi, y_lo, y_hi, y_lo, x_hi, x_lo, Areg, regs);
				j+=3;
			}

			if(j == A.row_ptr[i+1]-2){
				AVXreg x_hi = set(0.0, 0.0, x[A.col_ind[j+1]], x[A.col_ind[j+0]]);
				AVXreg x_lo = regs.zeros;

				AVXreg Areg = load(A.val[j]);
				Fmad(y_hi, y_lo, y_hi, y_lo, x_hi, x_lo, Areg, regs);
				j+=2;
			}

			if(j == A.row_ptr[i+1]-1){
				AVXreg x_hi = set(0.0, 0.0, 0.0, x[A.col_ind[j+0]]);
				AVXreg x_lo = regs.zeros;

				AVXreg Areg = load(A.val[j]);
				Fmad(y_hi, y_lo, y_hi, y_lo, x_hi, x_lo, Areg, regs);
				j+=1;
			}

			y[i] = reduction(y_hi, y_lo);
		}
	}

	// D, DD, D
	void matvec(const d_real_SpMat& A, const dd_real_vector& x, d_real_vector& y){
		if((size_t)x.size() != (size_t)y.size()){
			std::cerr << "error bad vector size" << std::endl;
			assert(1);
		}
		if((size_t)x.size() != (size_t)A.get_row()){
			std::cerr << "error bad matrix size" << std::endl;
			assert(1);
		}

		registers regs;

#pragma omp parallel for schedule(guided) private(regs)
		for(size_t i=0; i<A.get_row(); i++){
			AVXreg y_hi = regs.zeros;
			AVXreg y_lo = regs.zeros;
			size_t j = 0;

			for(j = A.row_ptr[i]; j < A.row_ptr[i+1] - (SIMD_Length-1); j+=SIMD_Length){

				AVXreg x_hi = set(x.hi[A.col_ind[j+0]], x.hi[A.col_ind[j+1]], x.hi[A.col_ind[j+2]], x.hi[A.col_ind[j+3]]);
				AVXreg x_lo = set(x.lo[A.col_ind[j+0]], x.lo[A.col_ind[j+1]], x.lo[A.col_ind[j+2]], x.lo[A.col_ind[j+3]]);

				AVXreg Areg = load(A.val[j]);

				Fmad(y_hi, y_lo, y_hi, y_lo, x_hi, x_lo, Areg, regs);
			}

			//Fraction Processing
			if(j == A.row_ptr[i+1]-3){
				AVXreg x_hi = set(0.0, x.hi[A.col_ind[j+2]], x.hi[A.col_ind[j+1]], x.hi[A.col_ind[j+0]]);
				AVXreg x_lo = set(0.0, x.lo[A.col_ind[j+2]], x.lo[A.col_ind[j+1]], x.lo[A.col_ind[j+0]]);

				AVXreg Areg = load(A.val[j]);

				Fmad(y_hi, y_lo, y_hi, y_lo, x_hi, x_lo, Areg, regs);
				j+=3;
			}

			if(j == A.row_ptr[i+1]-2){
				AVXreg x_hi = set(0.0, 0.0, x.hi[A.col_ind[j+1]], x.hi[A.col_ind[j+0]]);
				AVXreg x_lo = set(0.0, 0.0, x.lo[A.col_ind[j+1]], x.lo[A.col_ind[j+0]]);

				AVXreg Areg = load(A.val[j]);
				Fmad(y_hi, y_lo, y_hi, y_lo, x_hi, x_lo, Areg, regs);
				j+=2;
			}

			if(j == A.row_ptr[i+1]-1){
				AVXreg x_hi = set(0.0, 0.0, 0.0, x.hi[A.col_ind[j+0]]);
				AVXreg x_lo = set(0.0, 0.0, 0.0, x.lo[A.col_ind[j+0]]);

				AVXreg Areg = load(A.val[j]);
				Fmad(y_hi, y_lo, y_hi, y_lo, x_hi, x_lo, Areg, regs);
				j+=1;
			}

			y.data()[i] = reduction(y_hi, y_lo);
		}
	}

	// D, D, D
	void matvec(const d_real_SpMat& A, const d_real_vector& x, d_real_vector& y){
		if((size_t)x.size() != (size_t)y.size()){
			std::cerr << "error bad vector size" << std::endl;
			assert(1);
		}
		if((size_t)x.size() != (size_t)A.get_row()){
			std::cerr << "error bad matrix size" << std::endl;
			assert(1);
		}

#pragma omp parallel for schedule(guided) 
		for(size_t i=0; i<A.get_row(); i++){
			for(size_t j = A.row_ptr[i]; j < A.row_ptr[i+1]; j++){
				y.data()[i] += A.val[j] * x[A.col_ind[j]];
			}
		}
	}


}
