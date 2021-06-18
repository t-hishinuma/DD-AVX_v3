#include <DD-AVX.hpp>
#include <chrono>
#include <iostream>
#include <vector>
#define TOL 1.0e-6

std::vector<double> make_ans(double alpha, const std::vector<double> &x) {

  std::vector<double> y(x.size(), 0.0);
#pragma omp parallel for
  for (int i = 0; i < y.size(); i++) {
    y[i] = alpha * x[i];
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

template <typename ALPHA, typename X> int test(long N) {
  ALPHA alpha = rand();
  X x;

  for (int i = 0; i < N; i++) {
    x.push_back(rand());
  }

  auto ref = make_ans(alpha, x.HI());

  dd_avx::scale(alpha, x);

  if (!err_check(ref, x.HI(), TOL)) {
    std::cout << "...fail" << std::endl;
    return false;
  }
  auto start = std::chrono::system_clock::now();
  for (int i = 0; i < 100; i++)
    dd_avx::scale(alpha, x);
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
  std::cout << "scale, size = " << N << std::endl;

  std::cout << "DD, DD" << std::flush;
  ret = test<dd_real, dd_real_vector>(N);
  if (!ret)
    return 1;

  std::cout << "D, DD" << std::flush;
  ret = test<d_real, dd_real_vector>(N);
  if (!ret)
    return 1;

  std::cout << "DD, D" << std::flush;
  ret = test<dd_real, d_real_vector>(N);
  if (!ret)
    return 1;

  std::cout << "D, D" << std::flush;
  ret = test<d_real, d_real_vector>(N);
  if (!ret)
    return 1;

  return 0;
}
