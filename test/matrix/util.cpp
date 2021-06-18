#include <DD-AVX.hpp>
#include <iostream>
#include <vector>

int main(int argc, char **argv) {
  d_real_SpMat A;
  A.input_mm("./test.mtx");

  std::cout << "row #2" << std::endl;
  d_real_vector row2 = A.get_row_vec(1);
  row2.print_all();

  std::cout << "col #2" << std::endl;
  d_real_vector col2 = A.get_col_vec(1);
  col2.print_all();

  std::cout << "diag" << std::endl;
  d_real_vector diag = A.get_diag_vec();
  diag.print_all();

  /////////////////////////////////////
  std::cout << "create matrix" << std::endl;
  d_real_SpMat B(3, 3);
  std::cout << B.get_row() << "," << B.get_nnz() << std::endl;
  B.output();
  std::cout << "" << std::endl;
  // create matrix
  B.insert(0, 0, 1.0);
  B.insert(0, 1, 2.0);
  B.insert(0, 2, 3.0);
  B.output();
  std::cout << "a" << std::endl;

  B.insert(1, 0, 4.0);
  B.insert(1, 2, 5.0);
  B.output();
  std::cout << "b" << std::endl;

  B.insert(2, 0, 6.0);
  B.insert(2, 1, 7.0);
  B.insert(2, 2, 8.0);
  B.output();
  std::cout << "c" << std::endl;

  std::cout << B.get_row() << "," << B.get_nnz() << std::endl;
  B.output();

  d_real_vector row1 = B.get_row_vec(0);
  row1.print_all();

  double sum = 0;
  for (int i = 0; i < B.get_row(); i++) {
    for (int j = 0; j < B.get_row(); j++) {
      sum += B.at(i, j);
    }
  }
  std::cout << "summation of elements of B is " << sum << std::endl;

  return 0;
}
