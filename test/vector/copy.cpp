#include <DD-AVX.hpp>
#include <chrono>
#include <iostream>
#include <vector>

template <typename SRC, typename DST> bool test(long n) {
  SRC vec1(n, 1.0);
  DST vec2;
  DST vec3(n / 2, 5.0);

  vec2.copy(vec1);

  if (vec1 == vec2) {
    // == operator check
  } else {
    std::cout << "...fail" << std::endl;
    vec2.print_all();
    return false;
  }

  vec3 = vec1;

  if (vec1 != vec3) {
    //!= operator check
    std::cout << "...fail" << std::endl;
    vec3.print_all();
    return false;
  }

  auto start = std::chrono::system_clock::now();
  for (int i = 0; i < 100; i++)
    vec2.copy(vec1);
  auto end = std::chrono::system_clock::now();
  double sec = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)
                   .count() /
               1.0e+9 / 100;

  std::cout << "...pass\t" << sec << std::endl;

  return true;
}
int main(int argc, char **argv) {
  bool ret;

  if (argc != 2) {
    std::cout << "error, $1 = size" << std::endl;
    return 1;
  }

  long N = atoi(argv[1]);
  std::cout << "copy, size = " << N << std::endl;

  std::cout << "DD = DD" << std::flush;
  ret = test<dd_real_vector, dd_real_vector>(N);
  if (!ret)
    return 1;

  std::cout << "D = DD" << std::flush;
  ret = test<dd_real_vector, d_real_vector>(N);
  if (!ret)
    return 1;

  std::cout << "DD = D" << std::flush;
  ret = test<d_real_vector, dd_real_vector>(N);
  if (!ret)
    return 1;

  std::cout << "D = D" << std::flush;
  ret = test<d_real_vector, d_real_vector>(N);
  if (!ret)
    return 1;

  return 0;
}
