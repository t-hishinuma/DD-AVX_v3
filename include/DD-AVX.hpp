#ifndef DD_AVX_HPP
#define DD_AVX_HPP

#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>
#include <vector>

#include <omp.h>

#include "./DD-AVX_d_spmat.hpp"
#include "./DD-AVX_d_vector.hpp"
#include "./DD-AVX_dd_vector.hpp"
#include "./qd/dd_real.h"

using d_real = double;

inline dd_real dd_rand() {
  dd_real tmp;
  tmp.x[0] = rand();
  tmp.x[1] = tmp.x[0] * powf(2.0, -52);
  return tmp;
}

namespace dd_avx {

/** @brief axpy: y = ax+y **/
void axpy(const dd_real &alpha, const dd_real_vector &x, dd_real_vector &y);
/** @brief axpy: y = ax+y **/
void axpy(const dd_real &alpha, const d_real_vector &x, dd_real_vector &y);
/** @brief axpy: y = ax+y **/
void axpy(const dd_real &alpha, const dd_real_vector &x, d_real_vector &y);
/** @brief axpy: y = ax+y **/
void axpy(const dd_real &alpha, const d_real_vector &x, d_real_vector &y);

/** @brief axpy: y = ax+y **/
void axpy(const d_real &alpha, const dd_real_vector &x, dd_real_vector &y);
/** @brief axpy: y = ax+y **/
void axpy(const d_real &alpha, const d_real_vector &x, dd_real_vector &y);
/** @brief axpy: y = ax+y **/
void axpy(const d_real &alpha, const dd_real_vector &x, d_real_vector &y);
/** @brief axpy: y = ax+y **/
void axpy(const d_real &alpha, const d_real_vector &x, d_real_vector &y);

/** @brief axpyz: z = ax+y **/
void axpyz(const dd_real &alpha, const dd_real_vector &x,
           const dd_real_vector &y, dd_real_vector &z);
/** @brief axpyz: z = ax+y **/
void axpyz(const dd_real &alpha, const d_real_vector &x,
           const dd_real_vector &y, dd_real_vector &z);
/** @brief axpyz: z = ax+y **/
void axpyz(const dd_real &alpha, const dd_real_vector &x,
           const d_real_vector &y, dd_real_vector &z);
/** @brief axpyz: z = ax+y **/
void axpyz(const dd_real &alpha, const d_real_vector &x, const d_real_vector &y,
           dd_real_vector &z);

/** @brief axpyz: z = ax+y **/
void axpyz(const d_real &alpha, const dd_real_vector &x,
           const dd_real_vector &y, dd_real_vector &z);
/** @brief axpyz: z = ax+y **/
void axpyz(const d_real &alpha, const d_real_vector &x, const dd_real_vector &y,
           dd_real_vector &z);
/** @brief axpyz: z = ax+y **/
void axpyz(const d_real &alpha, const dd_real_vector &x, const d_real_vector &y,
           dd_real_vector &z);
/** @brief axpyz: z = ax+y **/
void axpyz(const d_real &alpha, const d_real_vector &x, const d_real_vector &y,
           dd_real_vector &z);

/** @brief axpyz: z = ax+y **/
void axpyz(const dd_real &alpha, const dd_real_vector &x,
           const dd_real_vector &y, d_real_vector &z);
/** @brief axpyz: z = ax+y **/
void axpyz(const dd_real &alpha, const d_real_vector &x,
           const dd_real_vector &y, d_real_vector &z);
/** @brief axpyz: z = ax+y **/
void axpyz(const dd_real &alpha, const dd_real_vector &x,
           const d_real_vector &y, d_real_vector &z);
/** @brief axpyz: z = ax+y **/
void axpyz(const dd_real &alpha, const d_real_vector &x, const d_real_vector &y,
           d_real_vector &z);

/** @brief axpyz: z = ax+y **/
void axpyz(const dd_real &alpha, const dd_real_vector &x,
           const dd_real_vector &y, d_real_vector &z);
/** @brief axpyz: z = ax+y **/
void axpyz(const dd_real &alpha, const d_real_vector &x,
           const dd_real_vector &y, d_real_vector &z);
/** @brief axpyz: z = ax+y **/
void axpyz(const dd_real &alpha, const dd_real_vector &x,
           const d_real_vector &y, d_real_vector &z);
/** @brief axpyz: z = ax+y **/
void axpyz(const dd_real &alpha, const d_real_vector &x, const d_real_vector &y,
           d_real_vector &z);

/** @brief xpay: y = x+ay **/
void xpay(const dd_real &alpha, const dd_real_vector &x, dd_real_vector &y);
/** @brief xpay: y = x+ay **/
void xpay(const dd_real &alpha, const d_real_vector &x, dd_real_vector &y);
/** @brief xpay: y = x+ay **/
void xpay(const dd_real &alpha, const dd_real_vector &x, d_real_vector &y);
/** @brief xpay: y = x+ay **/
void xpay(const dd_real &alpha, const d_real_vector &x, d_real_vector &y);

/** @brief xpay: y = x+ay **/
void xpay(const d_real &alpha, const dd_real_vector &x, dd_real_vector &y);
/** @brief xpay: y = x+ay **/
void xpay(const d_real &alpha, const d_real_vector &x, dd_real_vector &y);
/** @brief xpay: y = x+ay **/
void xpay(const d_real &alpha, const dd_real_vector &x, d_real_vector &y);
/** @brief xpay: y = x+ay **/
void xpay(const d_real &alpha, const d_real_vector &x, d_real_vector &y);

/** @brief scale: x = ax **/
void scale(const dd_real &alpha, dd_real_vector &x);
/** @brief scale: x = ax **/
void scale(const d_real &alpha, dd_real_vector &x);
/** @brief scale: x = ax **/
void scale(const dd_real &alpha, d_real_vector &x);
/** @brief scale: x = ax **/
void scale(const d_real &alpha, d_real_vector &x);

/** @brief nrm2: ans = ||x|| **/
dd_real nrm2(const dd_real_vector &x);
/** @brief nrm2: ans = ||x|| **/
dd_real nrm2(const d_real_vector &x);

/** @brief dot: ans = (x,y) **/
dd_real dot(const dd_real_vector &x, const dd_real_vector &y);
/** @brief dot: ans = (x,y) **/
dd_real dot(const d_real_vector &x, const dd_real_vector &y);
/** @brief dot: ans = (x,y) **/
dd_real dot(const dd_real_vector &x, const d_real_vector &y);
/** @brief dot: ans = (x,y) **/
dd_real dot(const d_real_vector &x, const d_real_vector &y);

/** @brief matvec: y = Ax **/
void matvec(const d_real_SpMat &A, const dd_real_vector &x, dd_real_vector &y);
/** @brief matvec: y = Ax **/
void matvec(const d_real_SpMat &A, const d_real_vector &x, dd_real_vector &y);
/** @brief matvec: y = Ax **/
void matvec(const d_real_SpMat &A, const dd_real_vector &x, d_real_vector &y);
/** @brief matvec: y = Ax **/
void matvec(const d_real_SpMat &A, const d_real_vector &x, d_real_vector &y);
} // namespace dd_avx

#endif
