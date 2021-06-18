#include <DD-AVX_internal.hpp>
using namespace ddavx_core;

namespace dd_avx {
// alpha = DD, z = DD ///////////////////////////////////////////
void axpyz(const dd_real &alpha, const dd_real_vector &x,
           const dd_real_vector &y, dd_real_vector &z) {
  if (x.size() != y.size() && x.size() != z.size()) {
    std::cerr << "error bad vector size" << std::endl;
    assert(1);
  }
  registers regs;

#pragma omp parallel private(regs)
  {
    int i = 0, is = 0, ie = 0;
    get_isie(y.size(), is, ie);
    reg alpha_hi = broadcast(alpha.x[0]);
    reg alpha_lo = broadcast(alpha.x[1]);
    for (i = is; i < (ie - SIMD_Length + 1); i += SIMD_Length) {

      reg x_hi = load(x.hi[i]);
      reg x_lo = load(x.lo[i]);

      reg y_hi = load(y.hi[i]);
      reg y_lo = load(y.lo[i]);

      reg z_hi = load(z.hi[i]);
      reg z_lo = load(z.lo[i]);

      Fma(z_hi, z_lo, y_hi, y_lo, alpha_hi, alpha_lo, x_hi, x_lo, regs);

      store(z.hi[i], z_hi);
      store(z.lo[i], z_lo);
    }
    for (; i < ie; i++) {
      Fma(z.hi[i], z.lo[i], y.hi[i], y.lo[i], alpha.x[0], alpha.x[1], x.hi[i],
          x.lo[i]);
    }
  }
}

void axpyz(const dd_real &alpha, const d_real_vector &x,
           const dd_real_vector &y, dd_real_vector &z) {
  if (x.size() != y.size() && x.size() != z.size()) {
    std::cerr << "error bad vector size" << std::endl;
    assert(1);
  }
  registers regs;

#pragma omp parallel private(regs)
  {
    int i = 0, is = 0, ie = 0;
    get_isie(y.size(), is, ie);
    reg alpha_hi = broadcast(alpha.x[0]);
    reg alpha_lo = broadcast(alpha.x[1]);
    for (i = is; i < (ie - SIMD_Length + 1); i += SIMD_Length) {

      reg x_hi = load(x.data()[i]);
      reg x_lo = regs.zeros;

      reg y_hi = load(y.hi[i]);
      reg y_lo = load(y.lo[i]);

      reg z_hi = load(z.hi[i]);
      reg z_lo = load(z.lo[i]);

      Fma(z_hi, z_lo, y_hi, y_lo, alpha_hi, alpha_lo, x_hi, x_lo, regs);

      store(z.hi[i], z_hi);
      store(z.lo[i], z_lo);
    }
    for (; i < ie; i++) {
      Fma(z.hi[i], z.lo[i], y.hi[i], y.lo[i], alpha.x[0], alpha.x[1],
          x.data()[i], 0.0);
    }
  }
}

void axpyz(const dd_real &alpha, const dd_real_vector &x,
           const d_real_vector &y, dd_real_vector &z) {
  if (x.size() != y.size() && x.size() != z.size()) {
    std::cerr << "error bad vector size" << std::endl;
    assert(1);
  }
  registers regs;

#pragma omp parallel private(regs)
  {
    int i = 0, is = 0, ie = 0;
    get_isie(y.size(), is, ie);
    reg alpha_hi = broadcast(alpha.x[0]);
    reg alpha_lo = broadcast(alpha.x[1]);
    for (i = is; i < (ie - SIMD_Length + 1); i += SIMD_Length) {

      reg x_hi = load(x.hi[i]);
      reg x_lo = load(x.lo[i]);

      reg y_hi = load(y.data()[i]);
      reg y_lo = regs.zeros;

      reg z_hi = load(z.hi[i]);
      reg z_lo = load(z.lo[i]);

      Fma(z_hi, z_lo, y_hi, y_lo, alpha_hi, alpha_lo, x_hi, x_lo, regs);

      store(z.hi[i], z_hi);
      store(z.lo[i], z_lo);
    }
    for (; i < ie; i++) {
      Fma(z.hi[i], z.lo[i], y.data()[i], 0.0, alpha.x[0], alpha.x[1], x.hi[i],
          x.lo[i]);
    }
  }
}

void axpyz(const dd_real &alpha, const d_real_vector &x, const d_real_vector &y,
           dd_real_vector &z) {
  if (x.size() != y.size() && x.size() != z.size()) {
    std::cerr << "error bad vector size" << std::endl;
    assert(1);
  }
  registers regs;

#pragma omp parallel private(regs)
  {
    int i = 0, is = 0, ie = 0;
    get_isie(y.size(), is, ie);
    reg alpha_hi = broadcast(alpha.x[0]);
    reg alpha_lo = broadcast(alpha.x[1]);
    for (i = is; i < (ie - SIMD_Length + 1); i += SIMD_Length) {

      reg x_hi = load(x.data()[i]);
      reg x_lo = regs.zeros;

      reg y_hi = load(y.data()[i]);
      reg y_lo = regs.zeros;

      reg z_hi = load(z.hi[i]);
      reg z_lo = load(z.lo[i]);

      Fma(z_hi, z_lo, y_hi, y_lo, alpha_hi, alpha_lo, x_hi, x_hi, regs);

      store(z.hi[i], z_hi);
      store(z.lo[i], z_lo);
    }
    for (; i < ie; i++) {
      Fma(z.hi[i], z.lo[i], y.data()[i], 0.0, alpha.x[0], alpha.x[1],
          x.data()[i], 0.0);
    }
  }
}
// alpha = D, z = DD ///////////////////////////////////////////
void axpyz(const d_real &alpha, const dd_real_vector &x,
           const dd_real_vector &y, dd_real_vector &z) {
  if (x.size() != y.size() && x.size() != z.size()) {
    std::cerr << "error bad vector size" << std::endl;
    assert(1);
  }
  registers regs;

#pragma omp parallel private(regs)
  {
    int i = 0, is = 0, ie = 0;
    get_isie(y.size(), is, ie);
    reg alpha_hi = broadcast(alpha);
    reg alpha_lo = regs.zeros;
    for (i = is; i < (ie - SIMD_Length + 1); i += SIMD_Length) {

      reg x_hi = load(x.hi[i]);
      reg x_lo = load(x.lo[i]);

      reg y_hi = load(y.hi[i]);
      reg y_lo = load(y.lo[i]);

      reg z_hi = load(z.hi[i]);
      reg z_lo = load(z.lo[i]);

      Fma(z_hi, z_lo, y_hi, y_lo, alpha_hi, alpha_lo, x_hi, x_lo, regs);

      store(z.hi[i], z_hi);
      store(z.lo[i], z_lo);
    }
    for (; i < ie; i++) {
      Fma(z.hi[i], z.lo[i], y.hi[i], y.lo[i], alpha, 0.0, x.hi[i], x.lo[i]);
    }
  }
}

void axpyz(const d_real &alpha, const d_real_vector &x, const dd_real_vector &y,
           dd_real_vector &z) {
  if (x.size() != y.size() && x.size() != z.size()) {
    std::cerr << "error bad vector size" << std::endl;
    assert(1);
  }
  registers regs;

#pragma omp parallel private(regs)
  {
    int i = 0, is = 0, ie = 0;
    get_isie(y.size(), is, ie);
    reg alpha_hi = broadcast(alpha);
    reg alpha_lo = regs.zeros;
    for (i = is; i < (ie - SIMD_Length + 1); i += SIMD_Length) {

      reg x_hi = load(x.data()[i]);
      reg x_lo = regs.zeros;

      reg y_hi = load(y.hi[i]);
      reg y_lo = load(y.lo[i]);

      reg z_hi = load(z.hi[i]);
      reg z_lo = load(z.lo[i]);

      Fma(z_hi, z_lo, y_hi, y_lo, alpha_hi, alpha_lo, x_hi, x_lo, regs);

      store(z.hi[i], z_hi);
      store(z.lo[i], z_lo);
    }
    for (; i < ie; i++) {
      Fma(z.hi[i], z.lo[i], y.hi[i], y.lo[i], alpha, 0.0, x.data()[i], 0.0);
    }
  }
}

void axpyz(const d_real &alpha, const dd_real_vector &x, const d_real_vector &y,
           dd_real_vector &z) {
  if (x.size() != y.size() && x.size() != z.size()) {
    std::cerr << "error bad vector size" << std::endl;
    assert(1);
  }
  registers regs;

#pragma omp parallel private(regs)
  {
    int i = 0, is = 0, ie = 0;
    get_isie(y.size(), is, ie);
    reg alpha_hi = broadcast(alpha);
    reg alpha_lo = regs.zeros;
    for (i = is; i < (ie - SIMD_Length + 1); i += SIMD_Length) {

      reg x_hi = load(x.hi[i]);
      reg x_lo = load(x.lo[i]);

      reg y_hi = load(y.data()[i]);
      reg y_lo = regs.zeros;

      reg z_hi = load(z.hi[i]);
      reg z_lo = load(z.lo[i]);

      Fma(z_hi, z_lo, y_hi, y_lo, alpha_hi, alpha_lo, x_hi, x_lo, regs);

      store(z.hi[i], z_hi);
      store(z.lo[i], z_lo);
    }
    for (; i < ie; i++) {
      Fma(z.hi[i], z.lo[i], y.data()[i], 0.0, alpha, 0.0, x.hi[i], x.lo[i]);
    }
  }
}

void axpyz(const d_real &alpha, const d_real_vector &x, const d_real_vector &y,
           dd_real_vector &z) {
  if (x.size() != y.size() && x.size() != z.size()) {
    std::cerr << "error bad vector size" << std::endl;
    assert(1);
  }
  registers regs;

#pragma omp parallel private(regs)
  {
    int i = 0, is = 0, ie = 0;
    get_isie(y.size(), is, ie);
    reg alpha_hi = broadcast(alpha);
    reg alpha_lo = regs.zeros;
    for (i = is; i < (ie - SIMD_Length + 1); i += SIMD_Length) {

      reg x_hi = load(x.data()[i]);
      reg x_lo = regs.zeros;

      reg y_hi = load(y.data()[i]);
      reg y_lo = regs.zeros;

      reg z_hi = load(z.hi[i]);
      reg z_lo = load(z.lo[i]);

      Fma(z_hi, z_lo, y_hi, y_lo, alpha_hi, alpha_lo, x_hi, x_hi, regs);

      store(z.hi[i], z_hi);
      store(z.lo[i], z_lo);
    }
    for (; i < ie; i++) {
      Fma(z.hi[i], z.lo[i], y.data()[i], 0.0, alpha, 0.0, x.data()[i], 0.0);
    }
  }
}

// alpha = DD, z = D ///////////////////////////////////////////
void axpyz(const dd_real &alpha, const dd_real_vector &x,
           const dd_real_vector &y, d_real_vector &z) {
  if (x.size() != y.size() && x.size() != z.size()) {
    std::cerr << "error bad vector size" << std::endl;
    assert(1);
  }
  registers regs;

#pragma omp parallel private(regs)
  {
    int i = 0, is = 0, ie = 0;
    get_isie(y.size(), is, ie);
    reg alpha_hi = broadcast(alpha.x[0]);
    reg alpha_lo = broadcast(alpha.x[1]);
    for (i = is; i < (ie - SIMD_Length + 1); i += SIMD_Length) {

      reg x_hi = load(x.hi[i]);
      reg x_lo = load(x.lo[i]);

      reg y_hi = load(y.hi[i]);
      reg y_lo = load(y.lo[i]);

      reg z_hi = load(z.data()[i]);
      reg z_lo = regs.zeros;

      Fma(z_hi, z_lo, y_hi, y_lo, alpha_hi, alpha_lo, x_hi, x_lo, regs);

      store(z.data()[i], z_hi);
    }
    for (; i < ie; i++) {
      Fma(z.data()[i], y.hi[i], y.lo[i], alpha.x[0], alpha.x[1], x.hi[i],
          x.lo[i]);
    }
  }
}

void axpyz(const dd_real &alpha, const d_real_vector &x,
           const dd_real_vector &y, d_real_vector &z) {
  if (x.size() != y.size() && x.size() != z.size()) {
    std::cerr << "error bad vector size" << std::endl;
    assert(1);
  }
  registers regs;

#pragma omp parallel private(regs)
  {
    int i = 0, is = 0, ie = 0;
    get_isie(y.size(), is, ie);
    reg alpha_hi = broadcast(alpha.x[0]);
    reg alpha_lo = broadcast(alpha.x[1]);
    for (i = is; i < (ie - SIMD_Length + 1); i += SIMD_Length) {

      reg x_hi = load(x.data()[i]);
      reg x_lo = regs.zeros;

      reg y_hi = load(y.hi[i]);
      reg y_lo = load(y.lo[i]);

      reg z_hi = load(z.data()[i]);
      reg z_lo = regs.zeros;

      Fma(z_hi, z_lo, y_hi, y_lo, alpha_hi, alpha_lo, x_hi, x_lo, regs);

      store(z.data()[i], z_hi);
    }
    for (; i < ie; i++) {
      Fma(z.data()[i], y.hi[i], y.lo[i], alpha.x[0], alpha.x[1], x.data()[i],
          0.0);
    }
  }
}

void axpyz(const dd_real &alpha, const dd_real_vector &x,
           const d_real_vector &y, d_real_vector &z) {
  if (x.size() != y.size() && x.size() != z.size()) {
    std::cerr << "error bad vector size" << std::endl;
    assert(1);
  }
  registers regs;

#pragma omp parallel private(regs)
  {
    int i = 0, is = 0, ie = 0;
    get_isie(y.size(), is, ie);
    reg alpha_hi = broadcast(alpha.x[0]);
    reg alpha_lo = broadcast(alpha.x[1]);
    for (i = is; i < (ie - SIMD_Length + 1); i += SIMD_Length) {

      reg x_hi = load(x.hi[i]);
      reg x_lo = load(x.lo[i]);

      reg y_hi = load(y.data()[i]);
      reg y_lo = regs.zeros;

      reg z_hi = load(z.data()[i]);
      reg z_lo = regs.zeros;

      Fma(z_hi, z_lo, y_hi, y_lo, alpha_hi, alpha_lo, x_hi, x_lo, regs);

      store(z.data()[i], z_hi);
    }
    for (; i < ie; i++) {
      Fma(z.data()[i], y.data()[i], 0.0, alpha.x[0], alpha.x[1], x.hi[i],
          x.lo[i]);
    }
  }
}

void axpyz(const dd_real &alpha, const d_real_vector &x, const d_real_vector &y,
           d_real_vector &z) {
  if (x.size() != y.size() && x.size() != z.size()) {
    std::cerr << "error bad vector size" << std::endl;
    assert(1);
  }
  registers regs;

#pragma omp parallel private(regs)
  {
    int i = 0, is = 0, ie = 0;
    get_isie(y.size(), is, ie);
    reg alpha_hi = broadcast(alpha.x[0]);
    reg alpha_lo = broadcast(alpha.x[1]);
    for (i = is; i < (ie - SIMD_Length + 1); i += SIMD_Length) {

      reg x_hi = load(x.data()[i]);
      reg x_lo = regs.zeros;

      reg y_hi = load(y.data()[i]);
      reg y_lo = regs.zeros;

      reg z_hi = load(z.data()[i]);
      reg z_lo = regs.zeros;

      Fma(z_hi, z_lo, y_hi, y_lo, alpha_hi, alpha_lo, x_hi, x_hi, regs);

      store(z.data()[i], z_hi);
    }
    for (; i < ie; i++) {
      Fma(z.data()[i], y.data()[i], 0.0, alpha.x[0], alpha.x[1], x.data()[i],
          0.0);
    }
  }
}
// alpha = D ///////////////////////////////////////////
void axpyz(const d_real &alpha, const dd_real_vector &x,
           const dd_real_vector &y, d_real_vector &z) {
  if (x.size() != y.size() && x.size() != z.size()) {
    std::cerr << "error bad vector size" << std::endl;
    assert(1);
  }
  registers regs;

#pragma omp parallel private(regs)
  {
    int i = 0, is = 0, ie = 0;
    get_isie(y.size(), is, ie);
    reg alpha_hi = broadcast(alpha);
    reg alpha_lo = regs.zeros;
    for (i = is; i < (ie - SIMD_Length + 1); i += SIMD_Length) {

      reg x_hi = load(x.hi[i]);
      reg x_lo = load(x.lo[i]);

      reg y_hi = load(y.hi[i]);
      reg y_lo = load(y.lo[i]);

      reg z_hi = load(z.data()[i]);
      reg z_lo = regs.zeros;

      Fma(z_hi, z_lo, y_hi, y_lo, alpha_hi, alpha_lo, x_hi, x_lo, regs);

      store(z.data()[i], z_hi);
    }
    for (; i < ie; i++) {
      Fma(z.data()[i], y.hi[i], y.lo[i], alpha, 0.0, x.hi[i], x.lo[i]);
    }
  }
}

void axpyz(const d_real &alpha, const d_real_vector &x, const dd_real_vector &y,
           d_real_vector &z) {
  if (x.size() != y.size() && x.size() != z.size()) {
    std::cerr << "error bad vector size" << std::endl;
    assert(1);
  }
  registers regs;

#pragma omp parallel private(regs)
  {
    int i = 0, is = 0, ie = 0;
    get_isie(y.size(), is, ie);
    reg alpha_hi = broadcast(alpha);
    reg alpha_lo = regs.zeros;
    for (i = is; i < (ie - SIMD_Length + 1); i += SIMD_Length) {

      reg x_hi = load(x.data()[i]);
      reg x_lo = regs.zeros;

      reg y_hi = load(y.hi[i]);
      reg y_lo = load(y.lo[i]);

      reg z_hi = load(z.data()[i]);
      reg z_lo = regs.zeros;

      Fma(z_hi, z_lo, y_hi, y_lo, alpha_hi, alpha_lo, x_hi, x_lo, regs);

      store(z.data()[i], z_hi);
    }
    for (; i < ie; i++) {
      Fma(z.data()[i], y.hi[i], y.lo[i], alpha, 0.0, x.data()[i], 0.0);
    }
  }
}

void axpyz(const d_real &alpha, const dd_real_vector &x, const d_real_vector &y,
           d_real_vector &z) {
  if (x.size() != y.size() && x.size() != z.size()) {
    std::cerr << "error bad vector size" << std::endl;
    assert(1);
  }
  registers regs;

#pragma omp parallel private(regs)
  {
    int i = 0, is = 0, ie = 0;
    get_isie(y.size(), is, ie);
    reg alpha_hi = broadcast(alpha);
    reg alpha_lo = regs.zeros;
    for (i = is; i < (ie - SIMD_Length + 1); i += SIMD_Length) {

      reg x_hi = load(x.hi[i]);
      reg x_lo = load(x.lo[i]);

      reg y_hi = load(y.data()[i]);
      reg y_lo = regs.zeros;

      reg z_hi = load(z.data()[i]);
      reg z_lo = regs.zeros;

      Fma(z_hi, z_lo, y_hi, y_lo, alpha_hi, alpha_lo, x_hi, x_lo, regs);

      store(z.data()[i], z_hi);
    }
    for (; i < ie; i++) {
      Fma(z.data()[i], y.data()[i], 0.0, alpha, 0.0, x.hi[i], x.lo[i]);
    }
  }
}

void axpyz(const d_real &alpha, const d_real_vector &x, const d_real_vector &y,
           d_real_vector &z) {
  if (x.size() != y.size() && x.size() != z.size()) {
    std::cerr << "error bad vector size" << std::endl;
    assert(1);
  }
  registers regs;

#pragma omp parallel private(regs)
  {
    int i = 0, is = 0, ie = 0;
    get_isie(y.size(), is, ie);
    reg alpha_hi = broadcast(alpha);
    reg alpha_lo = regs.zeros;
    for (i = is; i < (ie - SIMD_Length + 1); i += SIMD_Length) {

      reg x_hi = load(x.data()[i]);
      reg x_lo = regs.zeros;

      reg y_hi = load(y.data()[i]);
      reg y_lo = regs.zeros;

      reg z_hi = load(z.data()[i]);
      reg z_lo = regs.zeros;

      Fma(z_hi, z_lo, y_hi, y_lo, alpha_hi, alpha_lo, x_hi, x_hi, regs);

      store(z.data()[i], z_hi);
    }
    for (; i < ie; i++) {
      Fma(z.data()[i], y.data()[i], 0.0, alpha, 0.0, x.data()[i], 0.0);
    }
  }
}
} // namespace dd_avx
