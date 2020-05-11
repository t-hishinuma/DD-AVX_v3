#ifndef DD_AVX_HPP
#define DD_AVX_HPP

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<float.h>

#include <vector>
#include <algorithm>
#include <iostream>
#include <random>
#include <cassert>

#include<omp.h>

#include"./qd/dd_real.h"
#include"./DD-AVX_dd_vector.hpp"
#include"./DD-AVX_d_vector.hpp"
#include"./DD-AVX_d_spmat.hpp"

#if USE_AVX2==1
	#include "./core/AVX2_core.hpp"
#elif USE_AVX512==1 // for AVX512
	#include "./core/AVX512_core.hpp"
#endif
	#include "./core/add.hpp"
	#include "./core/mul.hpp"
	#include "./core/fma.hpp"

using d_real = double;

inline dd_real dd_rand(){
	dd_real tmp;
	tmp.x[0] = rand();
	tmp.x[1] = tmp.x[0] * powf(2.0, -52);
	return tmp;
}

namespace dd_avx{
	//axpy
	void axpy(const dd_real& alpha, const dd_real_vector& x, dd_real_vector& y);
	void axpy(const dd_real& alpha, const d_real_vector& x, dd_real_vector& y);
	void axpy(const dd_real& alpha, const dd_real_vector& x, d_real_vector& y);
	void axpy(const dd_real& alpha, const d_real_vector& x, d_real_vector& y);

	void axpy(const d_real& alpha, const dd_real_vector& x, dd_real_vector& y);
	void axpy(const d_real& alpha, const d_real_vector& x, dd_real_vector& y);
	void axpy(const d_real& alpha, const dd_real_vector& x, d_real_vector& y);
	void axpy(const d_real& alpha, const d_real_vector& x, d_real_vector& y);

	//axpyz
	void axpyz(const dd_real& alpha, const dd_real_vector& x, const dd_real_vector& y, dd_real_vector& z);
	void axpyz(const dd_real& alpha, const d_real_vector& x, const dd_real_vector& y, dd_real_vector& z);
	void axpyz(const dd_real& alpha, const dd_real_vector& x, const d_real_vector& y, dd_real_vector& z);
	void axpyz(const dd_real& alpha, const d_real_vector& x, const d_real_vector& y, dd_real_vector& z);

	void axpyz(const d_real& alpha, const dd_real_vector& x, const dd_real_vector& y, dd_real_vector& z);
	void axpyz(const d_real& alpha, const d_real_vector& x, const dd_real_vector& y, dd_real_vector& z);
	void axpyz(const d_real& alpha, const dd_real_vector& x, const d_real_vector& y, dd_real_vector& z);
	void axpyz(const d_real& alpha, const d_real_vector& x, const d_real_vector& y, dd_real_vector& z);

	void axpyz(const dd_real& alpha, const dd_real_vector& x, const dd_real_vector& y, d_real_vector& z);
	void axpyz(const dd_real& alpha, const d_real_vector& x, const dd_real_vector& y, d_real_vector& z);
	void axpyz(const dd_real& alpha, const dd_real_vector& x, const d_real_vector& y, d_real_vector& z);
	void axpyz(const dd_real& alpha, const d_real_vector& x, const d_real_vector& y, d_real_vector& z);

	void axpyz(const dd_real& alpha, const dd_real_vector& x, const dd_real_vector& y, d_real_vector& z);
	void axpyz(const dd_real& alpha, const d_real_vector& x, const dd_real_vector& y, d_real_vector& z);
	void axpyz(const dd_real& alpha, const dd_real_vector& x, const d_real_vector& y, d_real_vector& z);
	void axpyz(const dd_real& alpha, const d_real_vector& x, const d_real_vector& y, d_real_vector& z);

	//xpay
	void xpay(const dd_real& alpha, const dd_real_vector& x, dd_real_vector& y);
	void xpay(const dd_real& alpha, const d_real_vector& x, dd_real_vector& y);
	void xpay(const dd_real& alpha, const dd_real_vector& x, d_real_vector& y);
	void xpay(const dd_real& alpha, const d_real_vector& x, d_real_vector& y);

	void xpay(const d_real& alpha, const dd_real_vector& x, dd_real_vector& y);
	void xpay(const d_real& alpha, const d_real_vector& x, dd_real_vector& y);
	void xpay(const d_real& alpha, const dd_real_vector& x, d_real_vector& y);
	void xpay(const d_real& alpha, const d_real_vector& x, d_real_vector& y);

	//scale
	void scale(const dd_real& alpha, dd_real_vector& x);
	void scale(const d_real& alpha, dd_real_vector& x);
	void scale(const dd_real& alpha, d_real_vector& x);
	void scale(const d_real& alpha, d_real_vector& x);

	//dot
	dd_real nrm2(const dd_real_vector& x);
	dd_real nrm2(const d_real_vector& x);

	//nrm2
	dd_real dot(const dd_real_vector& x, const dd_real_vector& y);
	dd_real dot(const d_real_vector& x, const dd_real_vector& y);
	dd_real dot(const dd_real_vector& x, const d_real_vector& y);
	dd_real dot(const d_real_vector& x, const d_real_vector& y);

	//SpMV
	void matvec(const d_real_SpMat& A, const dd_real_vector& x, dd_real_vector& y);
	void matvec(const d_real_SpMat& A, const d_real_vector& x, dd_real_vector& y);
	void matvec(const d_real_SpMat& A, const dd_real_vector& x, d_real_vector& y);
	void matvec(const d_real_SpMat& A, const d_real_vector& x, d_real_vector& y);

// 	void tmatvec(const d_real_SpMat& A, const dd_real_vector& x, dd_real_vector& y);
// 	void tmatvec(const d_real_SpMat& A, const d_real_vector& x, dd_real_vector& y);
// 	void tmatvec(const d_real_SpMat& A, const dd_real_vector& x, d_real_vector& y);
// 	void tmatvec(const d_real_SpMat& A, const d_real_vector& x, d_real_vector& y);
}

#endif
