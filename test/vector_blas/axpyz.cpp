#include <DD-AVX.hpp>
#include <chrono>
#include <iostream>
#include <vector>
#define TOL 1.0e-6

std::vector<double> make_ans(const double alpha, const std::vector<double> &x,
                             const std::vector<double> &y) {
  std::vector<double> z(x.size(), 0.0);
#pragma omp parallel for
  for (int i = 0; i < z.size(); i++) {
    z[i] = alpha * x[i] + y[i];
  }
  return z;
}

bool err_check(const std::vector<double> &ans, const std::vector<double> &val,
               const double tol) {
  for (int i = 0; i < ans.size(); i++) {
    double err = fabs((val[i] - ans[i])) / fabs(ans[i]);
    if (err > tol) {
      printf("ans[%d] = %e, data[%d] = %e, err = %e\n", i, ans[i], i, val[i],
             err);
      return false;
    }
  }
  return true;
}

template <typename ALPHA, typename X, typename Y, typename Z> int test(long N) {
  ALPHA alpha = rand();
  X x;
  Y y;
  Z z;

  for (int i = 0; i < N; i++) {
    x.push_back(rand());
    y.push_back(rand());
    z.push_back(rand());
  }

  dd_avx::axpyz(alpha, x, y, z);

  auto ref = make_ans(alpha, x.HI(), y.HI());

  if (!err_check(ref, z.HI(), TOL)) {
    std::cout << "...fail" << std::endl;
    return false;
  }

  auto start = std::chrono::system_clock::now();
  for (int i = 0; i < 100; i++)
    dd_avx::axpyz(alpha, x, y, z);
  auto end = std::chrono::system_clock::now();
  double sec = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)
                   .count() /
               1.0e+9 / 100;

  std::cout << "...pass\t" << sec << std::endl;

  return true;
}

int main(int argc, char **argv) {
  bool ret = 0;

  if (argc != 2) {
    std::cout << "error, $1 = size" << std::endl;
    return 1;
  }

  long N = atoi(argv[1]);
  std::cout << "axpyz, size = " << N << std::endl;

  std::cout << "DD, DD, DD, DD" << std::flush;
  ret = test<dd_real, dd_real_vector, dd_real_vector, dd_real_vector>(N);
  if (!ret)
    return 1;

  std::cout << "DD, D, DD, DD" << std::flush;
  ret = test<dd_real, dd_real_vector, dd_real_vector, dd_real_vector>(N);
  if (!ret)
    return 1;

  std::cout << "DD, DD, D, DD" << std::flush;
  ret = test<dd_real, dd_real_vector, dd_real_vector, dd_real_vector>(N);
  if (!ret)
    return 1;

  std::cout << "DD, D, D, DD" << std::flush;
  ret = test<dd_real, dd_real_vector, dd_real_vector, dd_real_vector>(N);
  if (!ret)
    return 1;

  std::cout << "D, DD, DD, DD" << std::flush;
  ret = test<dd_real, dd_real_vector, dd_real_vector, dd_real_vector>(N);
  if (!ret)
    return 1;

  std::cout << "D, D, DD, DD" << std::flush;
  ret = test<dd_real, dd_real_vector, dd_real_vector, dd_real_vector>(N);
  if (!ret)
    return 1;

  std::cout << "D, DD, D, DD" << std::flush;
  ret = test<dd_real, dd_real_vector, dd_real_vector, dd_real_vector>(N);
  if (!ret)
    return 1;

  std::cout << "D, D, D, DD" << std::flush;
  ret = test<dd_real, dd_real_vector, dd_real_vector, dd_real_vector>(N);
  if (!ret)
    return 1;

  std::cout << "DD, DD, DD, D" << std::flush;
  ret = test<dd_real, dd_real_vector, dd_real_vector, d_real_vector>(N);
  if (!ret)
    return 1;

  std::cout << "DD, D, DD, D" << std::flush;
  ret = test<dd_real, dd_real_vector, dd_real_vector, d_real_vector>(N);
  if (!ret)
    return 1;

  std::cout << "DD, DD, D, D" << std::flush;
  ret = test<dd_real, dd_real_vector, dd_real_vector, d_real_vector>(N);
  if (!ret)
    return 1;

  std::cout << "DD, D, D, D" << std::flush;
  ret = test<dd_real, dd_real_vector, dd_real_vector, d_real_vector>(N);
  if (!ret)
    return 1;

  std::cout << "D, DD, DD, D" << std::flush;
  ret = test<dd_real, dd_real_vector, dd_real_vector, d_real_vector>(N);
  if (!ret)
    return 1;

  std::cout << "D, D, DD, D" << std::flush;
  ret = test<dd_real, dd_real_vector, dd_real_vector, d_real_vector>(N);
  if (!ret)
    return 1;

  std::cout << "D, DD, D, D" << std::flush;
  ret = test<dd_real, dd_real_vector, dd_real_vector, d_real_vector>(N);
  if (!ret)
    return 1;

  std::cout << "D, D, D, D" << std::flush;
  ret = test<dd_real, dd_real_vector, dd_real_vector, d_real_vector>(N);
  if (!ret)
    return 1;

  return 0;
}
