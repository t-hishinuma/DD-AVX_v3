#include <DD-AVX_internal.hpp>

d_real_vector::operator dd_real_vector() {
  printf("cast dd=>d\n");
  dd_real_vector tmp;
  for (int i = 0; i < size(); i++) {
    tmp.hi[i] = *this[i];
    tmp.lo[i] = 0.0;
  }
  return tmp;
}
