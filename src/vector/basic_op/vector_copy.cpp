#include <DD-AVX_internal.hpp>
// Double
void d_real_vector::copy(const dd_real_vector &vec) {
  resize(vec.size());
  std::copy(vec.hi.begin(), vec.hi.end(), begin());
}

void d_real_vector::copy(const d_real_vector &vec) {
  resize(vec.size());
  std::copy(vec.begin(), vec.end(), begin());
}

void d_real_vector::copy(const std::vector<double> &vec) {
  resize(vec.size());
  std::copy(vec.begin(), vec.end(), begin());
}

void d_real_vector::copy(const std::vector<dd_real> &vec) {
  resize(vec.size());

#pragma omp parallel for
  for (int i = 0; i < vec.size(); i++) {
    at(i) = vec[i].x[0];
  }
}

d_real_vector &d_real_vector::operator=(const dd_real_vector &vec) {
  copy(vec);
  return *this;
}

d_real_vector &d_real_vector::operator=(const d_real_vector &vec) {
  copy(vec);
  return *this;
}

d_real_vector &d_real_vector::operator=(const std::vector<double> &vec) {
  copy(vec);
  return *this;
}

d_real_vector &d_real_vector::operator=(const std::vector<dd_real> &vec) {
  copy(vec);
  return *this;
}

// DD
void dd_real_vector::copy(const dd_real_vector &vec) {
  resize(vec.size());
  std::copy(vec.hi.begin(), vec.hi.end(), hi.begin());
  std::copy(vec.lo.begin(), vec.lo.end(), lo.begin());
  N = vec.N;
}

void dd_real_vector::copy(const d_real_vector &vec) {
  resize(vec.size());
  std::copy(vec.begin(), vec.end(), hi.begin());
  std::fill(this->lo.begin(), this->lo.end(), 0.0);
  N = vec.size();
}

void dd_real_vector::copy(const std::vector<double> &vec) {
  resize(vec.size());
  std::copy(vec.begin(), vec.end(), hi.begin());
  std::fill(this->lo.begin(), this->lo.end(), 0.0);
  N = vec.size();
}

void dd_real_vector::copy(const std::vector<dd_real> &vec) {
  hi.resize(vec.size());
  lo.resize(vec.size());

#pragma omp parallel for
  for (int i = 0; i < vec.size(); i++) {
    hi[i] = vec[i].x[0];
    lo[i] = vec[i].x[1];
  }
  N = vec.size();
}

dd_real_vector &dd_real_vector::operator=(const dd_real_vector &vec) {
  this->copy(vec);
  return *this;
}

dd_real_vector &dd_real_vector::operator=(const d_real_vector &vec) {
  this->copy(vec);
  return *this;
}

dd_real_vector &dd_real_vector::operator=(const std::vector<double> &vec) {
  this->copy(vec);
  return *this;
}

dd_real_vector &dd_real_vector::operator=(const std::vector<dd_real> &vec) {
  this->copy(vec);
  return *this;
}
