#include <DD-AVX.hpp>
#include <chrono>
#include <iostream>
#include <math.h>
#include <vector>
#define TOL 1.0e-4

double make_ans(const std::vector<double> x) {

  double dot = 0;
  for (int i = 0; i < x.size(); i++) {
    dot += x[i] * x[i];
  }
  return sqrt(dot);
}

bool err_check(double ans, double val, const double tol) {

  double err = fabs((val - ans)) / fabs(ans);
  if (err > tol) {
    printf("ans[%d] = %e, data[%d] = %e, err = %e\n", 0, ans, 0, val, err);
    return false;
  }
  return true;
}

template <typename ALPHA, typename X> int test(long N) {
  ALPHA alpha = 0;
  X x;

  for (int i = 0; i < N; i++)
    x.push_back(rand());

  alpha = dd_avx::nrm2(x);

  auto ref = make_ans(x.HI());

  if (!err_check(ref, (d_real &)alpha, TOL)) {
    std::cout << "...fail" << std::endl;
    return false;
  }

  auto start = std::chrono::system_clock::now();
  for (int i = 0; i < 100; i++)
    alpha = dd_avx::nrm2(x);
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
  std::cout << "nrm2, size = " << N << std::endl;

  std::cout << "DD, DD" << std::flush;
  ret = test<dd_real, dd_real_vector>(N);
  if (!ret)
    return 1;

  std::cout << "DD, D" << std::flush;
  ret = test<dd_real, d_real_vector>(N);
  if (!ret)
    return 1;

  std::cout << "D, DD" << std::flush;
  ret = test<d_real, dd_real_vector>(N);
  if (!ret)
    return 1;

  std::cout << "D, D, D" << std::flush;
  ret = test<d_real, dd_real_vector>(N);
  if (!ret)
    return 1;

  return 0;
}
