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
#include"./dd_vector.hpp"
#include"./d_vector.hpp"

#if USE_AVX2==1
	#include"./AVX2_core.hpp"
#endif

using d_real = double;

inline dd_real dd_rand(){
	dd_real tmp;
	tmp.x[0] = rand();
	tmp.x[1] = tmp.x[0] * powf(2.0, -52);
	return tmp;
}

#if 0
#if USE_AVX==1
	#include <DD-AVX_MACRO_AVX.hpp>
#elif USE_SSE2==1
	#include <DD-AVX_MACRO_SSE2.hpp>
#else
	#define DD_AVX_DECLAR\
		double p1,p2,tq,bhi,blo,chi,clo,sh,eh,sl,el,th,tl,t0,t1,t2,t3
#endif

#define DD_AVX_GET_ISIE(id,nprocs,n,is,ie) \
	if( (id) < (n)%(nprocs) ) \
	{ \
		(ie) = (n)/(nprocs)+1; \
		(is) = (ie)*(id); \
	} \
	else \
	{ \
		(ie) = (n)/(nprocs); \
		(is) = (ie)*(id) + (n)%(nprocs); \
	} \
	(ie) = (ie)+(is);

//#define ddavx_debug

/////////////////Scalar Class/////////////////////////
/////////////////Scalar Class/////////////////////////
/////////////////Scalar Class/////////////////////////
class DD_Scalar;
class D_Vector;
class DD_Vector;

class D_Scalar{
   public:
      double hi;
      double p1,p2,tq,bhi,blo,chi,clo,sh,eh,sl,el,th,tl;

      D_Scalar(double r)
	 : hi(r)
      {}

      D_Scalar()
	 : hi(0.0)
      {}
      void print() const {
	 printf("%1.15e\n", hi);
      }

      //!binary operator (in DD-AVX-Scalar.cpp)
      D_Scalar operator=(double a);
      D_Scalar operator=(const D_Scalar& D);
      D_Scalar operator=(const DD_Scalar& DD);

      D_Scalar operator-(void);

      //arithmetics
      D_Scalar operator+(double rhv);
      D_Scalar operator+(D_Scalar rhv);
      DD_Scalar operator+(DD_Scalar rhv);

      D_Scalar operator-(double rhv);
      D_Scalar operator-(D_Scalar rhv);
      DD_Scalar operator-(DD_Scalar rhv);

      D_Scalar operator*(double rhv);
      D_Scalar operator*(D_Scalar rhv);
      DD_Scalar operator*(DD_Scalar rhv);

      D_Scalar operator/(double rhv);
      D_Scalar operator/(D_Scalar rhv);
      DD_Scalar operator/(DD_Scalar rhv);

      operator double();
      operator DD_Scalar();

      D_Scalar dot(D_Vector vx, D_Vector vy);
      D_Scalar dot(DD_Vector vx, D_Vector vy);
      D_Scalar dot(D_Vector vx, DD_Vector vy);
      D_Scalar dot(DD_Vector vx, DD_Vector vy);

      D_Scalar nrm2(D_Vector vx);
      D_Scalar nrm2(DD_Vector vx);
};

class DD_Scalar{
   public:
      double hi;
      double lo;
      double p1,p2,tq,bhi,blo,chi,clo,sh,eh,sl,el,th,tl;
      DD_Scalar()
	 : hi(0.0), lo(0.0)
      {}

      DD_Scalar(double r)
	 : hi(r), lo(0.0)
      {}

      void print() const {
	 printf("hi = %1.15e lo = %1.15e\n", hi, lo);
      }

      //!binary operator
      DD_Scalar operator=(double a);
      DD_Scalar operator=(const D_Scalar& D);
      DD_Scalar operator=(const DD_Scalar& DD);

      DD_Scalar operator-(void);

      //arithmetics
      DD_Scalar operator+(double rhv);
      DD_Scalar operator+(D_Scalar rhv);
      DD_Scalar operator+(DD_Scalar rhv);

      DD_Scalar operator-(double rhv);
      DD_Scalar operator-(D_Scalar rhv);
      DD_Scalar operator-(DD_Scalar rhv);

      DD_Scalar operator*(double rhv);
      DD_Scalar operator*(D_Scalar rhv);
      DD_Scalar operator*(DD_Scalar rhv);

      DD_Scalar operator/(double rhv);
      DD_Scalar operator/(D_Scalar rhv);
      DD_Scalar operator/(DD_Scalar rhv);

      operator double();
      operator D_Scalar();

      DD_Scalar dot(D_Vector vx, D_Vector vy);
      DD_Scalar dot(DD_Vector vx, D_Vector vy);
      DD_Scalar dot(D_Vector vx, DD_Vector vy);
      DD_Scalar dot(DD_Vector vx, DD_Vector vy);

      DD_Scalar nrm2(D_Vector vx);
      DD_Scalar nrm2(DD_Vector vx);
};
/////////////////Vector Class/////////////////////////
/////////////////Vector Class/////////////////////////
/////////////////Vector Class/////////////////////////

class D_Vector{
   public:
      double *hi;
      int N;

      D_Vector operator=(const D_Vector& D);
      D_Vector operator=(const DD_Vector& DD);
      D_Vector copy(D_Vector D);
      D_Vector copy(DD_Vector DD);

      void malloc(int n);
      void free();

      void print(int n);
      void print_all();

      int getsize();

      void input(const char *filename);
      void input_mm(FILE* file);
      void input_plane(FILE* file);

      void broadcast(double val);
      void broadcast(D_Scalar val);
      void broadcast(DD_Scalar val);

      void output_plane(const char* file);
      void output_mm(const char* file);
};

class DD_Vector{
   public:
      double *hi; double *lo;
      int N;

      DD_Vector operator=(const D_Vector& D);
      DD_Vector operator=(const DD_Vector& DD);
      DD_Vector copy(D_Vector D);
      DD_Vector copy(DD_Vector DD);

      void malloc(int n);
      void free();

      void print(int n);
      void print_all();

      int getsize();

      void input(const char *filename);
      void input_mm(FILE* file);
      void input_plane(FILE* file);

      void broadcast(double val);
      void broadcast(D_Scalar val);
      void broadcast(DD_Scalar val);

      void output_plane(const char* file);
      void output_mm(const char* file);
};


/////////////////Matrix Class/////////////////////////
/////////////////Matrix Class/////////////////////////
/////////////////Matrix Class/////////////////////////
class D_Matrix{
   public:
      int format;//COO=0, CRS=1, BCRS4x1=2, DNS=3

      int N;
      int nnz;

      double* val;

      int* row; //coo
      int* col;

      int* ptr; //crs
      int* index;

      int* bptr;//bcrs4x1
      int* bindex;


      D_Matrix()
	 : format(0)
      {}

      //D_Matrix operator=(const D_Matrix& D);
      //D_Matrix copy(D_Matrix D);

      //void malloc(int n);
      //void free();

      /*
      void print(int row, int col);
      void print_row(int row);
      void print_col(int row);
      void print_all();

      void setsize();
      int getsize();

      void setnnz();
      int getnnz();

      void setformat();
      int getformat();
      */

      void input(const char *filename);
      void input_coo(FILE* file);
      void input_crs(FILE* file);

      //void output_mm(const char* file);
};

/////////////////Functions/////////////////////////
/////////////////Functions/////////////////////////
/////////////////Functions/////////////////////////
void DD_AVX_version();
extern D_Scalar D(double a);
extern D_Scalar D(D_Scalar a);
extern D_Scalar D(DD_Scalar a);

extern DD_Scalar DD(double a);
extern DD_Scalar DD(D_Scalar a);
extern DD_Scalar DD(DD_Scalar a);

extern D_Vector D(D_Vector a);
extern D_Vector D(DD_Vector a);
extern DD_Vector DD(D_Vector a);
extern DD_Vector DD(DD_Vector a);

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
