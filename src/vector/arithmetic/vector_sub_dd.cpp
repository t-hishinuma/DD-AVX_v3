#include <DD-AVX_internal.hpp>

using namespace ddavx_core;

//=========================================================
//  function
//=========================================================

void dd_real_vector::sub(dd_real_vector &vec1, dd_real_vector &vec2) {
  if (size() != vec1.size() || size() != vec2.size()) {
    std::cerr << "error bad vector size" << std::endl;
    assert(1);
  }
  registers regs;

#pragma omp parallel private(regs)
  {
    int i = 0, is = 0, ie = 0;
    get_isie(size(), is, ie);
    for (i = is; i < (ie - SIMD_Length + 1); i += SIMD_Length) {
      reg a_hi = load(hi[i]);
      reg a_lo = load(lo[i]);

      reg b_hi = load(vec1.hi[i]);
      reg b_lo = load(vec1.lo[i]);

      reg c_hi = load(vec2.hi[i]);
      reg c_lo = load(vec2.lo[i]);
      to_minus(c_hi, regs);
      to_minus(c_lo, regs);

      Add(a_hi, a_lo, b_hi, b_lo, c_hi, c_lo, regs);

      store(hi[i], a_hi);
      store(lo[i], a_lo);
    }
    for (; i < ie; i++) {
      Add(hi[i], lo[i], vec1.hi[i], vec1.lo[i], -vec2.hi[i], -vec2.lo[i]);
    }
  }
}

void dd_real_vector::sub(d_real_vector &vec1, dd_real_vector &vec2) {
  if (size() != vec1.size() || size() != vec2.size()) {
    std::cerr << "error bad vector size" << std::endl;
    assert(1);
  }
  registers regs;

#pragma omp parallel private(regs)
  {
    int i = 0, is = 0, ie = 0;
    get_isie(size(), is, ie);
    for (i = is; i < (ie - SIMD_Length + 1); i += SIMD_Length) {
      reg a_hi = load(hi[i]);
      reg a_lo = load(lo[i]);

      reg b_hi = load(vec1.data()[i]);
      reg b_lo = regs.zeros;

      reg c_hi = load(vec2.hi[i]);
      reg c_lo = load(vec2.lo[i]);
      to_minus(c_hi, regs);
      to_minus(c_lo, regs);

      Add(a_hi, a_lo, b_hi, b_lo, c_hi, c_lo, regs);

      store(hi[i], a_hi);
      store(lo[i], a_lo);
    }
    for (; i < ie; i++) {
      Add(hi[i], lo[i], vec1.data()[i], 0.0, -vec2.hi[i], -vec2.lo[i]);
    }
  }
}

void dd_real_vector::sub(dd_real_vector &vec1, d_real_vector &vec2) {
  if (size() != vec1.size() || size() != vec2.size()) {
    std::cerr << "error bad vector size" << std::endl;
    assert(1);
  }
  registers regs;

#pragma omp parallel private(regs)
  {
    int i = 0, is = 0, ie = 0;
    get_isie(size(), is, ie);
    for (i = is; i < (ie - SIMD_Length + 1); i += SIMD_Length) {
      reg a_hi = load(hi[i]);
      reg a_lo = load(lo[i]);

      reg b_hi = load(vec1.hi[i]);
      reg b_lo = load(vec1.lo[i]);

      reg c_hi = load(vec2.data()[i]);
      reg c_lo = regs.zeros;

      to_minus(c_hi, regs);
      to_minus(c_lo, regs);

      Add(a_hi, a_lo, b_hi, b_lo, c_hi, c_lo, regs);

      store(hi[i], a_hi);
      store(lo[i], a_lo);
    }
    for (; i < ie; i++) {
      Add(hi[i], lo[i], vec1.hi[i], vec1.lo[i], -1 * vec2.data()[i], -1 * 0.0);
    }
  }
}

void dd_real_vector::sub(d_real_vector &vec1, d_real_vector &vec2) {
  if (size() != vec1.size() || size() != vec2.size()) {
    std::cout << "error vecvor size is" << size() << vec1.size() << vec2.size()
              << std::endl;
    assert(1);
  }

#pragma omp parallel for
  for (int i = 0; i < size(); i++) {
    hi[i] = vec1.data()[i] - vec2.data()[i];
    lo[i] = 0.0;
  }
}

//=========================================================
//  operator
//=========================================================
dd_real_vector dd_real_vector::operator-(dd_real_vector &vec) {
  sub(*this, vec);
  return *this;
}

dd_real_vector dd_real_vector::operator-=(dd_real_vector &vec) {
  sub(*this, vec);
  return *this;
}

dd_real_vector dd_real_vector::operator-(d_real_vector &vec) {
  sub(*this, vec);
  return *this;
}

dd_real_vector dd_real_vector::operator-=(d_real_vector &vec) {
  sub(*this, vec);
  return *this;
}
