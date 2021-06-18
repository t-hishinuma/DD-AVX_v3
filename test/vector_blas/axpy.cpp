#include <DD-AVX.hpp>
#include <chrono>
#include <iostream>
#include <vector>
#define TOL 1.0e-6

std::vector<double> make_ans(const double alpha, const std::vector<double> &x) {
  std::vector<double> y(x.size(), 0.0);
#pragma omp parallel for
  for (int i = 0; i < y.size(); i++) {
    y[i] = alpha * x[i] + y[i];
  }
  return y;
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

template <typename ALPHA, typename X, typename Y> int test(long N) {
  ALPHA alpha = rand();
  X x;
  Y y;

  for (int i = 0; i < N; i++)
    x.push_back(rand());

  for (int i = 0; i < N; i++)
    y.push_back(0);

  dd_avx::axpy(alpha, x, y);

  auto ref = make_ans(alpha, x.HI());

  if (!err_check(ref, y.HI(), TOL)) {
    std::cout << "...fail" << std::endl;
    return false;
  }

  auto start = std::chrono::system_clock::now();
  for (int i = 0; i < 100; i++)
    dd_avx::axpy(alpha, x, y);
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
  std::cout << "axpy, size = " << N << std::endl;

  std::cout << "DD, DD, DD" << std::flush;
  ret = test<dd_real, dd_real_vector, dd_real_vector>(N);
  if (!ret)
    return 1;

  std::cout << "DD, DD, D" << std::flush;
  ret = test<dd_real, dd_real_vector, d_real_vector>(N);
  if (!ret)
    return 1;

  std::cout << "DD, D, DD" << std::flush;
  ret = test<dd_real, d_real_vector, dd_real_vector>(N);
  if (!ret)
    return 1;

  std::cout << "DD, D, D" << std::flush;
  ret = test<dd_real, d_real_vector, d_real_vector>(N);
  if (!ret)
    return 1;

  std::cout << "D, DD, DD" << std::flush;
  ret = test<d_real, dd_real_vector, dd_real_vector>(N);
  if (!ret)
    return 1;

  std::cout << "D, DD, D" << std::flush;
  ret = test<d_real, dd_real_vector, d_real_vector>(N);
  if (!ret)
    return 1;

  std::cout << "D, D, DD" << std::flush;
  ret = test<d_real, d_real_vector, dd_real_vector>(N);
  if (!ret)
    return 1;

  std::cout << "D, D, D" << std::flush;
  ret = test<d_real, d_real_vector, d_real_vector>(N);
  if (!ret)
    return 1;

  return 0;
}
