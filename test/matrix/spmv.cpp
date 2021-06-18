#include <DD-AVX.hpp>
#include <chrono>
#include <iostream>
#include <vector>
#define TOL 1.0e-6

void make_ans(const d_real_SpMat &A, const std::vector<double> &x,
              std::vector<double> &y) {
#pragma omp parallel for
  for (int i = 0; i < A.get_row(); i++) {
    for (int j = A.row_ptr[i]; j < A.row_ptr[i + 1]; j++) {
      y[i] += A.val[j] * x[A.col_ind[j]];
    }
  }
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

template <typename X, typename Y> int test(d_real_SpMat &A) {

  X x(A.get_row(), 1.0);
  Y y(A.get_row(), 0.0);

  std::vector<double> ans(y.size(), 0.0);

  dd_avx::matvec(A, x, y);

  make_ans(A, x.HI(), ans);

  if (!err_check(ans, y.HI(), TOL)) {
    std::cout << "...fail" << std::endl;
    return false;
  }

  auto start = std::chrono::system_clock::now();
  for (int i = 0; i < 100; i++)
    dd_avx::matvec(A, x, y);
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
    std::cout << "error, $1 = matrix file" << std::endl;
    return 1;
  }

  d_real_SpMat A;
  A.input_mm(argv[1]);

  std::cout << "DD = DMat * DD" << std::flush;
  ret = test<dd_real_vector, dd_real_vector>(A);
  if (!ret)
    return 1;

  std::cout << "D = DMat * DD" << std::flush;
  ret = test<d_real_vector, dd_real_vector>(A);
  if (!ret)
    return 1;

  std::cout << "DD = DMat * D" << std::flush;
  ret = test<dd_real_vector, d_real_vector>(A);
  if (!ret)
    return 1;

  std::cout << "D = DMat * D" << std::flush;
  ret = test<d_real_vector, d_real_vector>(A);
  if (!ret)
    return 1;

  return 0;
}
