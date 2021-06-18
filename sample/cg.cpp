#include <DD-AVX.hpp>
#include <chrono>
#include <iostream>
#include <vector>
template <typename X, typename B, typename R, typename P, typename Q,
          typename ALPHA, typename BETA>
int cg(d_real_SpMat &A, const double tol, int rhisotry) {

  X x(A.get_row(), 2.0);

  X ans(A.get_row(), 1.0);
  B b(A.get_row(), 0.0);

  dd_avx::matvec(A, ans, b); // b = A*1

  R r(A.get_row(), 0.0);
  P p(A.get_row(), 0.0);
  Q q(A.get_row(), 0.0);

  ALPHA alpha = 0;
  BETA beta = 0;

  dd_avx::matvec(A, x, q);
  r = b - q;

  // p0 = Mr0
  p = r;

  for (size_t iter = 0; iter < A.get_row(); iter++) {
    dd_avx::matvec(A, p, q);

    auto tmp = dd_avx::dot(r, r);
    alpha = tmp / dd_avx::dot(p, q);

    dd_avx::axpy(alpha, p, x);

    dd_avx::axpy(-alpha, q, r);

    beta = dd_avx::dot(r, r) / tmp;

    dd_avx::xpay(beta, r, p); // p = r + beta*p

    double resid = dd_avx::nrm2(r);
    if (rhisotry == 1) {
      printf("%ld\t%e\n", iter, resid);
    }

    if (resid < 1.0e-12) {
      printf("iter:\t %ld\n", iter);
      return 0;
    }
  }
  printf("iter:\tmaxiter\n");

  return 1;
}

int main(int argc, char **argv) {
  bool ret = 0;

  if (argc != 4) {
    std::cout << "error, $1 = matrix file, $2=tol, $3=print rhistory(1/0)"
              << std::endl;
    return 1;
  }

  d_real_SpMat A;
  A.input_mm(argv[1]);
  double tol = atof(argv[2]);
  int rhistory = atoi(argv[3]);

  std::cout << "Matrix dimension\t" << A.get_row() << std::endl;
  std::cout << "Matrix nnz\t" << A.get_nnz() << std::endl;
  std::cout << "tol\t" << tol << std::endl;

  // all DD
  std::cout << "===" << std::endl;
  std::cout << "all DD" << std::endl;
  auto start = std::chrono::system_clock::now();
  ret = cg<dd_real_vector, // x
           dd_real_vector, // b
           dd_real_vector, // r
           dd_real_vector, // p
           dd_real_vector, // q
           dd_real,        // alpha
           dd_real         // beta
           >(A, tol, rhistory);
  auto end = std::chrono::system_clock::now();
  double sec = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)
                   .count() /
               1.0e+9 / 100;
  if (ret == 1) {
    std::cout << "error, maxiter" << std::endl;
    return 1;
  }
  std::cout << "...pass\t" << sec << std::endl;

  // all Double
  std::cout << "===" << std::endl;
  std::cout << "all Double" << std::endl;
  start = std::chrono::system_clock::now();
  ret = cg<d_real_vector, // x
           d_real_vector, // b
           d_real_vector, // r
           d_real_vector, // p
           d_real_vector, // q
           d_real,        // alpha
           d_real         // beta
           >(A, tol, rhistory);
  end = std::chrono::system_clock::now();
  sec = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)
            .count() /
        1.0e+9 / 100;
  if (ret == 1) {
    std::cout << "error, maxiter" << std::endl;
    return 1;
  }
  std::cout << "...pass\t" << sec << std::endl;

  // mix
  std::cout << "===" << std::endl;
  std::cout << "mix precision" << std::endl;
  start = std::chrono::system_clock::now();
  ret = cg<d_real_vector,  // x
           d_real_vector,  // b
           dd_real_vector, // r
           dd_real_vector, // p
           d_real_vector,  // q
           dd_real,        // alpha
           dd_real         // beta
           >(A, tol, rhistory);
  end = std::chrono::system_clock::now();
  sec = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)
            .count() /
        1.0e+9 / 100;
  if (ret == 1) {
    std::cout << "error, maxiter" << std::endl;
    return 1;
  }
  std::cout << "...pass\t" << sec << std::endl;
}
