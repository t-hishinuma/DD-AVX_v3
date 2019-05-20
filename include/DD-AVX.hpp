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
#include"./scalar.hpp"
#include"./dd_vector.hpp"
#include"./d_vector.hpp"

#if USE_AVX2==1
	#include"./AVX2_core/AVX2_core.hpp"
	#include"./AVX2_core/AVX2_core_add.hpp"
	#include"./AVX2_core/AVX2_core_mul.hpp"
	#include"./AVX2_core/AVX2_core_fma.hpp"
#endif

using d_real = double;

inline dd_real dd_rand(){
	dd_real tmp;
	tmp.x[0] = rand();
	tmp.x[1] = tmp.x[0] * powf(2.0, -52);
	return tmp;
}

namespace dd_avx{
	void axpy(const dd_real& alpha, const dd_real_vector& x, dd_real_vector& y);
	void axpy(const dd_real& alpha, const d_real_vector& x, dd_real_vector& y);
	void axpy(const dd_real& alpha, const dd_real_vector& x, d_real_vector& y);
	void axpy(const dd_real& alpha, const d_real_vector& x, d_real_vector& y);

	void axpy(const dd_real& alpha, const dd_real_vector& x, dd_real_vector& y);
	void axpy(const dd_real& alpha, const d_real_vector& x, dd_real_vector& y);
	void axpy(const dd_real& alpha, const dd_real_vector& x, d_real_vector& y);
	void axpy(const dd_real& alpha, const d_real_vector& x, d_real_vector& y);
}

#if 0
void DD_AVX_version();
//axpy
extern void DD_AVX_axpy(D_Scalar alpha, D_Vector vx, D_Vector vy);
extern void DD_AVX_axpy(D_Scalar alpha, DD_Vector vx, D_Vector vy);
extern void DD_AVX_axpy(D_Scalar alpha, D_Vector vx, DD_Vector vy);
extern void DD_AVX_axpy(D_Scalar alpha, DD_Vector vx, DD_Vector vy);

extern void DD_AVX_axpy(DD_Scalar alpha, D_Vector vx, D_Vector vy);
extern void DD_AVX_axpy(DD_Scalar alpha, DD_Vector vx, D_Vector vy);
extern void DD_AVX_axpy(DD_Scalar alpha, D_Vector vx, DD_Vector vy);
extern void DD_AVX_axpy(DD_Scalar alpha, DD_Vector vx, DD_Vector vy);

extern void DD_AVX_axpy_D(D_Scalar alpha, D_Vector vx, D_Vector vy);
extern void DD_AVX_axpy_DD(DD_Scalar alpha, DD_Vector vx, DD_Vector vy);

//axpyz
extern void DD_AVX_axpyz(D_Scalar alpha, D_Vector vx, D_Vector vy, D_Vector vz);
extern void DD_AVX_axpyz(D_Scalar alpha, DD_Vector vx, D_Vector vy, D_Vector vz);
extern void DD_AVX_axpyz(D_Scalar alpha, D_Vector vx, DD_Vector vy, D_Vector vz);
extern void DD_AVX_axpyz(D_Scalar alpha, DD_Vector vx, DD_Vector vy, D_Vector vz);
extern void DD_AVX_axpyz(DD_Scalar alpha, D_Vector vx, D_Vector vy, D_Vector vz);
extern void DD_AVX_axpyz(DD_Scalar alpha, DD_Vector vx, D_Vector vy, D_Vector vz);
extern void DD_AVX_axpyz(DD_Scalar alpha, D_Vector vx, DD_Vector vy, D_Vector vz);
extern void DD_AVX_axpyz(DD_Scalar alpha, DD_Vector vx, DD_Vector vy, D_Vector vz);

extern void DD_AVX_axpyz(D_Scalar alpha, D_Vector vx, D_Vector vy, DD_Vector vz);
extern void DD_AVX_axpyz(D_Scalar alpha, DD_Vector vx, D_Vector vy, DD_Vector vz);
extern void DD_AVX_axpyz(D_Scalar alpha, D_Vector vx, DD_Vector vy, DD_Vector vz);
extern void DD_AVX_axpyz(D_Scalar alpha, DD_Vector vx, DD_Vector vy, DD_Vector vz);
extern void DD_AVX_axpyz(DD_Scalar alpha, D_Vector vx, D_Vector vy, DD_Vector vz);
extern void DD_AVX_axpyz(DD_Scalar alpha, DD_Vector vx, D_Vector vy, DD_Vector vz);
extern void DD_AVX_axpyz(DD_Scalar alpha, D_Vector vx, DD_Vector vy, DD_Vector vz);
extern void DD_AVX_axpyz(DD_Scalar alpha, DD_Vector vx, DD_Vector vy, DD_Vector vz);

extern void DD_AVX_axpyz_D(D_Scalar alpha, D_Vector vx, D_Vector vy, D_Vector vz);
extern void DD_AVX_axpyz_DD(DD_Scalar alpha, DD_Vector vx, DD_Vector vy, DD_Vector vz);

//dot
extern void DD_AVX_dot(D_Vector vx, D_Vector vy, D_Scalar* val);
extern void DD_AVX_dot(DD_Vector vx, D_Vector vy, D_Scalar* val);
extern void DD_AVX_dot(D_Vector vx, DD_Vector vy, D_Scalar* val);
extern void DD_AVX_dot(DD_Vector vx, DD_Vector vy, D_Scalar* val);

extern void DD_AVX_dot(D_Vector vx, D_Vector vy, DD_Scalar* val);
extern void DD_AVX_dot(DD_Vector vx, D_Vector vy, DD_Scalar* val);
extern void DD_AVX_dot(D_Vector vx, DD_Vector vy, DD_Scalar* val);
extern void DD_AVX_dot(DD_Vector vx, DD_Vector vy, DD_Scalar* val);

extern void DD_AVX_dot_D(D_Vector vx, D_Vector vy, D_Scalar* val);
extern void DD_AVX_dot_DD(DD_Vector vx, DD_Vector vy, DD_Scalar* val);

//nrm2
extern void DD_AVX_nrm2(D_Vector vx, D_Scalar* val);
extern void DD_AVX_nrm2(DD_Vector vx, D_Scalar* val);
extern void DD_AVX_nrm2(D_Vector vx, DD_Scalar* val);
extern void DD_AVX_nrm2(DD_Vector vx, DD_Scalar* val);

extern void DD_AVX_nrm2_D(D_Vector vx, D_Scalar* val);
extern void DD_AVX_nrm2_DD(DD_Vector vx, DD_Scalar* val);

//xpay(x,a,y) //y=x+ay
extern void DD_AVX_xpay(D_Vector vx, D_Scalar alpha, D_Vector vy);
extern void DD_AVX_xpay(DD_Vector vx, D_Scalar alpha, D_Vector vy);
extern void DD_AVX_xpay(D_Vector vx, D_Scalar alpha, DD_Vector vy);
extern void DD_AVX_xpay(DD_Vector vx, D_Scalar alpha, DD_Vector vy);

extern void DD_AVX_xpay(D_Vector vx, DD_Scalar alpha, D_Vector vy);
extern void DD_AVX_xpay(DD_Vector vx, DD_Scalar alpha, D_Vector vy);
extern void DD_AVX_xpay(D_Vector vx, DD_Scalar alpha, DD_Vector vy);
extern void DD_AVX_xpay(DD_Vector vx, DD_Scalar alpha, DD_Vector vy);

void DD_AVX_xpay_D(D_Vector vx, D_Scalar alpha, D_Vector vy);
void DD_AVX_xpay_DD(DD_Vector vx, DD_Scalar alpha, DD_Vector vy);

//scale(a,x) //x = ax;
extern void DD_AVX_scale(D_Scalar alpha, D_Vector vx);
extern void DD_AVX_scale(DD_Scalar alpha, D_Vector vx);
extern void DD_AVX_scale(D_Scalar alpha, DD_Vector vx);
extern void DD_AVX_scale(DD_Scalar alpha, DD_Vector vx);

extern void DD_AVX_scale_D(D_Scalar alpha, D_Vector vx);
extern void DD_AVX_scale_DD(DD_Scalar alpha, DD_Vector vx);

/////////////////////////////////////////////////////////////////////////

//SpMV
extern void DD_AVX_SpMV(D_Matrix A, D_Vector vx, D_Vector vy);
extern void DD_AVX_SpMV(D_Matrix A, DD_Vector vx, D_Vector vy);
extern void DD_AVX_SpMV(D_Matrix A, D_Vector vx, DD_Vector vy);
extern void DD_AVX_SpMV(D_Matrix A, DD_Vector vx, DD_Vector vy);

//CRS
extern void DD_AVX_SpMV_CRS_D(D_Matrix A, D_Vector vx, D_Vector vy);
extern void DD_AVX_SpMV_CRS_DD(D_Matrix A, DD_Vector vx, DD_Vector vy);

//TSpMV
extern void DD_AVX_TSpMV(D_Matrix A, D_Vector vx, D_Vector vy);
extern void DD_AVX_TSpMV(D_Matrix A, DD_Vector vx, D_Vector vy);
extern void DD_AVX_TSpMV(D_Matrix A, D_Vector vx, DD_Vector vy);
extern void DD_AVX_TSpMV(D_Matrix A, DD_Vector vx, DD_Vector vy);

//T_CRS
extern void DD_AVX_TSpMV_CRS_D(D_Matrix A, D_Vector vx, D_Vector vy);
extern void DD_AVX_TSpMV_CRS_DD(D_Matrix A, DD_Vector vx, DD_Vector vy);

#endif
#endif
