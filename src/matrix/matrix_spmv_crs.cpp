#include<DD-AVX_internal.hpp>
using namespace ddavx_core;

namespace dd_avx{

	// 実験的にsetを関数化して書き直しの箇所を減らしてみます
	inline SIMDreg set_all(const std::vector<double>& x, const std::vector<int>& index, const int i){
		SIMDreg tmp;
		tmp = set(x[index[i+0]], x[index[i+1]], x[index[i+2]], x[index[i+3]]);
		return tmp;
	}

	// D, DD, DD
	void matvec(const d_real_SpMat& A, const dd_real_vector& x, dd_real_vector& y){
		if(x.size() != y.size()){
			std::cerr << "error bad vector size" << std::endl;
			assert(1);
		}
		if(x.size() != A.get_row()){
			std::cerr << "error bad matrix size" << std::endl;
			assert(1);
		}

		registers regs;

#pragma omp parallel for schedule(guided) private(regs)
		for(int i=0; i<A.get_row(); i++){
			SIMDreg y_hi = regs.zeros;
			SIMDreg y_lo = regs.zeros;
			int j = 0;

			int ww =  A.row_ptr[i+1] - (SIMD_Length-1);
			for(j = (int)A.row_ptr[i]; j < ww; j+=(int)SIMD_Length){

 				SIMDreg x_hi = set_all(x.hi, A.col_ind, j);
 				SIMDreg x_lo = set_all(x.lo, A.col_ind, j);

				SIMDreg Areg = load(A.val[j]);

				Fmad(y_hi, y_lo, y_hi, y_lo, x_hi, x_lo, Areg, regs);
			}

			// Fraction Processing (SIMD_Length=4)
			// ここは関数化したいな．．
			if(j == A.row_ptr[i+1]-3){
				SIMDreg x_hi = set(0.0, x.hi[A.col_ind[j+2]], x.hi[A.col_ind[j+1]], x.hi[A.col_ind[j+0]]);
				SIMDreg x_lo = set(0.0, x.lo[A.col_ind[j+2]], x.lo[A.col_ind[j+1]], x.lo[A.col_ind[j+0]]);

				SIMDreg Areg = load(A.val[j]);

				Fmad(y_hi, y_lo, y_hi, y_lo, x_hi, x_lo, Areg, regs);
				j+=3;
			}

			if(j == A.row_ptr[i+1]-2){
				SIMDreg x_hi = set(0.0, 0.0, x.hi[A.col_ind[j+1]], x.hi[A.col_ind[j+0]]);
				SIMDreg x_lo = set(0.0, 0.0, x.lo[A.col_ind[j+1]], x.lo[A.col_ind[j+0]]);

				SIMDreg Areg = load(A.val[j]);
				Fmad(y_hi, y_lo, y_hi, y_lo, x_hi, x_lo, Areg, regs);
				j+=2;
			}

			if(j == A.row_ptr[i+1]-1){
				SIMDreg x_hi = set(0.0, 0.0, 0.0, x.hi[A.col_ind[j+0]]);
				SIMDreg x_lo = set(0.0, 0.0, 0.0, x.lo[A.col_ind[j+0]]);

				SIMDreg Areg = load(A.val[j]);
				Fmad(y_hi, y_lo, y_hi, y_lo, x_hi, x_lo, Areg, regs);
				j+=1;
			}

			y[i] = reduction(y_hi, y_lo);
		}
	}

	// D, D, DD
	void matvec(const d_real_SpMat& A, const d_real_vector& x, dd_real_vector& y){
		if(x.size() != y.size()){
			std::cerr << "error bad vector size" << std::endl;
			assert(1);
		}
		if(x.size() != A.get_row()){
			std::cerr << "error bad matrix size" << std::endl;
			assert(1);
		}

		registers regs;

#pragma omp parallel for schedule(guided) private(regs)
		for(int i=0; i<A.get_row(); i++){
			SIMDreg y_hi = regs.zeros;
			SIMDreg y_lo = regs.zeros;
			int j = 0;

			int ww =  A.row_ptr[i+1] - (SIMD_Length-1);
			for(j = (int)A.row_ptr[i]; j < ww; j+=(int)SIMD_Length){

				SIMDreg x_hi = set_all(x, A.col_ind, j);
				SIMDreg x_lo = regs.zeros;

				SIMDreg Areg = load(A.val[j]);

				Fmad(y_hi, y_lo, y_hi, y_lo, x_hi, x_lo, Areg, regs);
			}

			//Fraction Processing
			if(j == A.row_ptr[i+1]-3){
				SIMDreg x_hi = set(0.0, x[A.col_ind[j+2]], x[A.col_ind[j+1]], x[A.col_ind[j+0]]);
				SIMDreg x_lo = regs.zeros;

				SIMDreg Areg = load(A.val[j]);

				Fmad(y_hi, y_lo, y_hi, y_lo, x_hi, x_lo, Areg, regs);
				j+=3;
			}

			if(j == A.row_ptr[i+1]-2){
				SIMDreg x_hi = set(0.0, 0.0, x[A.col_ind[j+1]], x[A.col_ind[j+0]]);
				SIMDreg x_lo = regs.zeros;

				SIMDreg Areg = load(A.val[j]);
				Fmad(y_hi, y_lo, y_hi, y_lo, x_hi, x_lo, Areg, regs);
				j+=2;
			}

			if(j == A.row_ptr[i+1]-1){
				SIMDreg x_hi = set(0.0, 0.0, 0.0, x[A.col_ind[j+0]]);
				SIMDreg x_lo = regs.zeros;

				SIMDreg Areg = load(A.val[j]);
				Fmad(y_hi, y_lo, y_hi, y_lo, x_hi, x_lo, Areg, regs);
				j+=1;
			}

			y[i] = reduction(y_hi, y_lo);
		}
	}

	// D, DD, D
	void matvec(const d_real_SpMat& A, const dd_real_vector& x, d_real_vector& y){
		if(x.size() != y.size()){
			std::cerr << "error bad vector size" << std::endl;
			assert(1);
		}
		if(x.size() != A.get_row()){
			std::cerr << "error bad matrix size" << std::endl;
			assert(1);
		}

		registers regs;

#pragma omp parallel for schedule(guided) private(regs)
		for(int i=0; i<A.get_row(); i++){
			SIMDreg y_hi = regs.zeros;
			SIMDreg y_lo = regs.zeros;
			int j = 0;

			int ww =  A.row_ptr[i+1] - (SIMD_Length-1);
			for(j = (int)A.row_ptr[i]; j < ww; j+=(int)SIMD_Length){

				SIMDreg x_hi = set_all(x.hi, A.col_ind, j);
				SIMDreg x_lo = set_all(x.lo, A.col_ind, j);

				SIMDreg Areg = load(A.val[j]);

				Fmad(y_hi, y_lo, y_hi, y_lo, x_hi, x_lo, Areg, regs);
			}

			//Fraction Processing
			if(j == A.row_ptr[i+1]-3){
				SIMDreg x_hi = set(0.0, x.hi[A.col_ind[j+2]], x.hi[A.col_ind[j+1]], x.hi[A.col_ind[j+0]]);
				SIMDreg x_lo = set(0.0, x.lo[A.col_ind[j+2]], x.lo[A.col_ind[j+1]], x.lo[A.col_ind[j+0]]);

				SIMDreg Areg = load(A.val[j]);

				Fmad(y_hi, y_lo, y_hi, y_lo, x_hi, x_lo, Areg, regs);
				j+=3;
			}

			if(j == A.row_ptr[i+1]-2){
				SIMDreg x_hi = set(0.0, 0.0, x.hi[A.col_ind[j+1]], x.hi[A.col_ind[j+0]]);
				SIMDreg x_lo = set(0.0, 0.0, x.lo[A.col_ind[j+1]], x.lo[A.col_ind[j+0]]);

				SIMDreg Areg = load(A.val[j]);
				Fmad(y_hi, y_lo, y_hi, y_lo, x_hi, x_lo, Areg, regs);
				j+=2;
			}

			if(j == A.row_ptr[i+1]-1){
				SIMDreg x_hi = set(0.0, 0.0, 0.0, x.hi[A.col_ind[j+0]]);
				SIMDreg x_lo = set(0.0, 0.0, 0.0, x.lo[A.col_ind[j+0]]);

				SIMDreg Areg = load(A.val[j]);
				Fmad(y_hi, y_lo, y_hi, y_lo, x_hi, x_lo, Areg, regs);
				j+=1;
			}

			y.data()[i] = reduction(y_hi, y_lo);
		}
	}

	// D, D, D
	void matvec(const d_real_SpMat& A, const d_real_vector& x, d_real_vector& y){
		if(x.size() != y.size()){
			std::cerr << "error bad vector size" << std::endl;
			assert(1);
		}
		if(x.size() != A.get_row()){
			std::cerr << "error bad matrix size" << std::endl;
			assert(1);
		}

#pragma omp parallel for schedule(guided) 
		for(int i=0; i<A.get_row(); i++){
			for(int j = A.row_ptr[i]; j < A.row_ptr[i+1]; j++){
				y.data()[i] += A.val[j] * x[A.col_ind[j]];
			}
		}
	}
}
