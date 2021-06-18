#include <DD-AVX.hpp>
#include <iostream>
#include <vector>

int main(int argc, char **argv) {
  d_real_SpMat IN;
  IN.input_mm("./test.mtx");

  d_real_SpMat A = IN;

  A.output();
  A.output_mm("./input_test.log");

  return 0;
}
