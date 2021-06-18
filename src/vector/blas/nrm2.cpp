#include <DD-AVX_internal.hpp>
using namespace ddavx_core;

namespace dd_avx {

dd_real nrm2(const dd_real_vector &x) {
  dd_real tmp = dot(x, x);
  return sqrt(tmp);
}

dd_real nrm2(const d_real_vector &x) {
  dd_real tmp = dot(x, x);
  return sqrt(tmp);
}
} // namespace dd_avx
