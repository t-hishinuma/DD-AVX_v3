#include <DD-AVX_internal.hpp>

// Add
dd_real operator+(const dd_real a, const dd_real_vector_ref b) {
  dd_real tmp = b;
  dd_real c = a + tmp;
  return c;
}

dd_real operator+(const double a, const dd_real_vector_ref b) {
  dd_real tmp = b;
  dd_real c = a + tmp;
  return c;
}

// Sub
dd_real operator-(const dd_real a, const dd_real_vector_ref b) {
  dd_real tmp = b;
  dd_real c = a - tmp;
  return c;
}

dd_real operator-(const double a, const dd_real_vector_ref b) {
  dd_real tmp = b;
  dd_real c = a - tmp;
  return c;
}

// Mul
dd_real operator*(const dd_real a, const dd_real_vector_ref b) {
  dd_real tmp = b;
  dd_real c = a * tmp;
  return c;
}

dd_real operator*(const double a, const dd_real_vector_ref b) {
  dd_real tmp = b;
  dd_real c = a * tmp;
  return c;
}

// Div
dd_real operator/(const dd_real a, const dd_real_vector_ref b) {
  dd_real tmp = b;
  dd_real c = a / tmp;
  return c;
}

dd_real operator/(const double a, const dd_real_vector_ref b) {
  dd_real tmp = b;
  dd_real c = a / tmp;
  return c;
}

// Add
dd_real dd_real_vector_ref::operator+(const dd_real a) {
  dd_real tmp;
  tmp.x[0] = *dd_hi_iter;
  tmp.x[1] = *dd_lo_iter;
  tmp = tmp + a;
  return tmp;
}

dd_real dd_real_vector_ref::operator+(const dd_real_vector_ref a) {
  dd_real tmp1;
  tmp1.x[0] = *dd_hi_iter;
  tmp1.x[1] = *dd_lo_iter;

  dd_real tmp2;
  tmp2.x[0] = *a.dd_hi_iter;
  tmp2.x[1] = *a.dd_lo_iter;

  tmp1 = tmp1 + tmp2;
  return tmp1;
}

dd_real dd_real_vector_ref::operator+(const double a) {
  dd_real tmp;
  tmp.x[0] = *dd_hi_iter;
  tmp.x[1] = *dd_lo_iter;
  tmp = tmp + a;
  return tmp;
}

// Sub
dd_real dd_real_vector_ref::operator-(const dd_real a) {
  dd_real tmp;
  tmp.x[0] = *dd_hi_iter;
  tmp.x[1] = *dd_lo_iter;
  tmp = tmp - a;
  return tmp;
}

dd_real dd_real_vector_ref::operator-(const dd_real_vector_ref a) {
  dd_real tmp1;
  tmp1.x[0] = *dd_hi_iter;
  tmp1.x[1] = *dd_lo_iter;

  dd_real tmp2;
  tmp2.x[0] = *a.dd_hi_iter;
  tmp2.x[1] = *a.dd_lo_iter;

  tmp1 = tmp1 - tmp2;
  return tmp1;
}

dd_real dd_real_vector_ref::operator-(const double a) {
  dd_real tmp;
  tmp.x[0] = *dd_hi_iter;
  tmp.x[1] = *dd_lo_iter;
  tmp = tmp - a;
  return tmp;
}

// Mul
dd_real dd_real_vector_ref::operator*(const dd_real a) {
  dd_real tmp;
  tmp.x[0] = *dd_hi_iter;
  tmp.x[1] = *dd_lo_iter;
  tmp = tmp * a;
  return tmp;
}

dd_real dd_real_vector_ref::operator*(const dd_real_vector_ref a) {
  dd_real tmp1;
  tmp1.x[0] = *dd_hi_iter;
  tmp1.x[1] = *dd_lo_iter;

  dd_real tmp2;
  tmp2.x[0] = *a.dd_hi_iter;
  tmp2.x[1] = *a.dd_lo_iter;

  tmp1 = tmp1 * tmp2;
  return tmp1;
}

dd_real dd_real_vector_ref::operator*(const double a) {
  dd_real tmp;
  tmp.x[0] = *dd_hi_iter;
  tmp.x[1] = *dd_lo_iter;
  tmp = tmp * a;
  return tmp;
}

// Div
dd_real dd_real_vector_ref::operator/(const dd_real a) {
  dd_real tmp;
  tmp.x[0] = *dd_hi_iter;
  tmp.x[1] = *dd_lo_iter;
  tmp = tmp / a;
  return tmp;
}

dd_real dd_real_vector_ref::operator/(const dd_real_vector_ref a) {
  dd_real tmp1;
  tmp1.x[0] = *dd_hi_iter;
  tmp1.x[1] = *dd_lo_iter;

  dd_real tmp2;
  tmp2.x[0] = *a.dd_hi_iter;
  tmp2.x[1] = *a.dd_lo_iter;

  tmp1 = tmp1 / tmp2;
  return tmp1;
}

dd_real dd_real_vector_ref::operator/(const double a) {
  dd_real tmp;
  tmp.x[0] = *dd_hi_iter;
  tmp.x[1] = *dd_lo_iter;
  tmp = tmp / a;
  return tmp;
}
