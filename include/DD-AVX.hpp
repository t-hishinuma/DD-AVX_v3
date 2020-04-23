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

#include"qd/dd_real.h"
#include"./DD-AVX_dd_vector.hpp"
#include"./DD-AVX_d_vector.hpp"
#include"./DD-AVX_d_spmat.hpp"

#if USE_AVX2==1
	#include"./DD-AVX_AVX2_core/AVX2_core.hpp"
	#include"./DD-AVX_AVX2_core/AVX2_core_add.hpp"
	#include"./DD-AVX_AVX2_core/AVX2_core_mul.hpp"
	#include"./DD-AVX_AVX2_core/AVX2_core_fma.hpp"
#endif

using d_real = double;

inline dd_real dd_rand(){
	dd_real tmp;
	tmp.x[0] = rand();
	tmp.x[1] = tmp.x[0] * powf(2.0, -52);
	return tmp;
}

namespace dd_avx{
	//axpy
#if 0
	template <typename A, typename X, typename Y>
	extern void axpy(A alpha, X vx, Y vy);
#else
	void axpy(const dd_real& alpha, const dd_real_vector& x, dd_real_vector& y);
	void axpy(const dd_real& alpha, const d_real_vector& x, dd_real_vector& y);
	void axpy(const dd_real& alpha, const dd_real_vector& x, d_real_vector& y);
	void axpy(const dd_real& alpha, const d_real_vector& x, d_real_vector& y);

	void axpy(const d_real& alpha, const dd_real_vector& x, dd_real_vector& y);
	void axpy(const d_real& alpha, const d_real_vector& x, dd_real_vector& y);
	void axpy(const d_real& alpha, const dd_real_vector& x, d_real_vector& y);
	void axpy(const d_real& alpha, const d_real_vector& x, d_real_vector& y);
#endif

	//axpyz
#if 0
	template <typename A, typename X, typename Y, typename Z>
	extern void axpyz(A alpha, X vx, Y vy, Z vz);
#else
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
#endif

	//xpay
#if 0
	template <typename A, typename X, typename Y>
	extern void xpay(A alpha, X vx, Y vy);
#else
	void xpay(const dd_real& alpha, const dd_real_vector& x, dd_real_vector& y);
	void xpay(const dd_real& alpha, const d_real_vector& x, dd_real_vector& y);
	void xpay(const dd_real& alpha, const dd_real_vector& x, d_real_vector& y);
	void xpay(const dd_real& alpha, const d_real_vector& x, d_real_vector& y);

	void xpay(const d_real& alpha, const dd_real_vector& x, dd_real_vector& y);
	void xpay(const d_real& alpha, const d_real_vector& x, dd_real_vector& y);
	void xpay(const d_real& alpha, const dd_real_vector& x, d_real_vector& y);
	void xpay(const d_real& alpha, const d_real_vector& x, d_real_vector& y);
#endif

	//scale
#if 0
	template <typename A, typename X>
	extern void scale(A alpha, X vx);
#else
	void scale(const dd_real& alpha, dd_real_vector& x);
	void scale(const d_real& alpha, dd_real_vector& x);
	void scale(const dd_real& alpha, d_real_vector& x);
	void scale(const d_real& alpha, d_real_vector& x);
#endif

	//dot
#if 0
	template <typename X>
	extern void nrm2(X vx);
#else
	dd_real nrm2(const dd_real_vector& x);
	dd_real nrm2(const d_real_vector& x);
#endif

	//nrm2
#if 0
	template <typename X, typename Y>
	extern void dot(X vx, Y vy);
#else
	dd_real dot(const dd_real_vector& x, const dd_real_vector& y);
	dd_real dot(const d_real_vector& x, const dd_real_vector& y);
	dd_real dot(const dd_real_vector& x, const d_real_vector& y);
	dd_real dot(const d_real_vector& x, const d_real_vector& y);
#endif

	//SpMV
#if 0
	template <typename M, typename X, typename Y>
	extern void matvec(M A, X vx, Y vy);
#else
	void matvec(const d_real_SpMat& A, const dd_real_vector& x, dd_real_vector& y);
	void matvec(const d_real_SpMat& A, const d_real_vector& x, dd_real_vector& y);
	void matvec(const d_real_SpMat& A, const dd_real_vector& x, d_real_vector& y);
	void matvec(const d_real_SpMat& A, const d_real_vector& x, d_real_vector& y);
#endif

#if 0
	template <typename M, typename X, typename Y>
	extern void tmatvec(M A, X vx, Y vy);
	void tmatvec(const d_real_SpMat& A, const dd_real_vector& x, dd_real_vector& y);
	void tmatvec(const d_real_SpMat& A, const d_real_vector& x, dd_real_vector& y);
	void tmatvec(const d_real_SpMat& A, const dd_real_vector& x, d_real_vector& y);
	void tmatvec(const d_real_SpMat& A, const d_real_vector& x, d_real_vector& y);
#else
#endif
}

#endif
