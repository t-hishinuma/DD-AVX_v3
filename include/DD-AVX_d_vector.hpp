#ifndef D_VECTOR_HPP
#define D_VECTOR_HPP

class dd_real_vector;
class dd_real_vector_ref;
struct dd_real;

/** @brief Double precision vector class, This class is almost same as
 * std::vector<double> **/
class d_real_vector : public std::vector<double> {
  friend class dd_real_vector;

public:
  d_real_vector() : std::vector<double>(){};

  /** @brief create vector from std::vector<double> **/
  d_real_vector(const std::vector<double> &obj) : std::vector<double>(obj) {}
  /** @brief create vector, all elements is a  **/
  d_real_vector(double a) : std::vector<double>(a) {}
  /** @brief create vector, all elements is a  **/
  d_real_vector(int a) : std::vector<double>(a) {}
  /** @brief create vector, all elements is a  **/
  d_real_vector(long a) : std::vector<double>(a) {}

  /** @brief create size n, all elements is val vector  **/
  d_real_vector(int n, double val) : std::vector<double>(n, val) {}
  /** @brief create size n, all elements is val vector  **/
  d_real_vector(long n, double val) : std::vector<double>(n, val) {}

  /** @brief return DD's hi array **/
  std::vector<double> HI() { return *this; }

  /** @brief return DD's lo array (return zero vector) **/
  std::vector<double> LO() {
    std::vector<double> tmp(size(), 0.0);
    return tmp;
  }
  //--I/O---------------------------------------
  /** @brief output vector elements to standard I/O **/
  void print_all() {
    for (int i = 0; i < size(); i++)
      std::cout << std::vector<double>::at(i) << std::endl;
  }

  /** @brief output vector element vec[i] to standard I/O **/
  void print(int i) { std::cout << std::vector<double>::at(i) << std::endl; }

  /** @brief create vector from file  **/
  void input(const char *filename);

  /** @brief create vector from matrix market format file  **/
  void input_mm(FILE *file);

  /** @brief create vector from plane format file  **/
  void input_plane(FILE *file);

  /** @brief outout vector to matrix market format  **/
  void output_mm(const char *filename);

  /** @brief outout vector to plane format  **/
  void output_plane(const char *filename);

  //--copy---------------------------------------
  /** @brief copy from dd_real_vector  **/
  void copy(const dd_real_vector &vec);
  /** @brief copy from d_real_vector  **/
  void copy(const d_real_vector &vec);
  /** @brief copy from std::vector  **/
  void copy(const std::vector<double> &vec);
  /** @brief copy from std::vector (down cast) **/
  void copy(const std::vector<dd_real> &vec);

  /** @brief copy from dd_real_vector  **/
  d_real_vector &operator=(const dd_real_vector &vec);
  /** @brief copy from d_real_vector  **/
  d_real_vector &operator=(const d_real_vector &vec);
  /** @brief copy from std::vector  **/
  d_real_vector &operator=(const std::vector<double> &vec);
  /** @brief copy from std::vector (down cast) **/
  d_real_vector &operator=(const std::vector<dd_real> &vec);

  //--comparision == ---------------------------------------
  /** @brief comparision  **/
  bool operator==(const dd_real_vector &vec);
  /** @brief comparision  **/
  bool operator==(const d_real_vector &vec);
  /** @brief comparision  **/
  bool operator==(const std::vector<double> &vec);
  /** @brief comparision  **/
  bool operator==(const std::vector<dd_real> &vec);

  /** @brief comparision  **/
  bool operator!=(const dd_real_vector &vec);
  /** @brief comparision  **/
  bool operator!=(const d_real_vector &vec);
  /** @brief comparision  **/
  bool operator!=(const std::vector<double> &vec);
  /** @brief comparision  **/
  bool operator!=(const std::vector<dd_real> &vec);

  //--cast -------------------------------------
  /** @brief cast to double precision array  **/
  operator double *() { return data(); }

  /** @brief cast to dd_real_vector  **/
  operator dd_real_vector();

  //--minus---------------------------------------
  /** @brief sign **/
  void minus();
  /** @brief sign **/
  d_real_vector operator-();

  //--add---------------------------------------
  /** @brief all elemetnt arithmetic function **/
  void add(dd_real_vector &vec1, dd_real_vector &vec2);
  /** @brief all elemetnt arithmetic function **/
  void add(d_real_vector &vec1, dd_real_vector &vec2);
  /** @brief all elemetnt arithmetic function **/
  void add(dd_real_vector &vec1, d_real_vector &vec2);
  /** @brief all elemetnt arithmetic function **/
  void add(d_real_vector &vec1, d_real_vector &vec2);

  /** @brief all elemetnt arithmetic function **/
  d_real_vector operator+(dd_real_vector &vec);
  /** @brief all elemetnt arithmetic function **/
  d_real_vector operator+(d_real_vector &vec);

  /** @brief all elemetnt arithmetic function **/
  d_real_vector operator+=(dd_real_vector &vec);
  /** @brief all elemetnt arithmetic function **/
  d_real_vector operator+=(d_real_vector &vec);

  //--sub---------------------------------------
  /** @brief all elemetnt arithmetic function **/
  void sub(dd_real_vector &vec1, dd_real_vector &vec2);
  /** @brief all elemetnt arithmetic function **/
  void sub(d_real_vector &vec1, dd_real_vector &vec2);
  /** @brief all elemetnt arithmetic function **/
  void sub(dd_real_vector &vec1, d_real_vector &vec2);
  /** @brief all elemetnt arithmetic function **/
  void sub(d_real_vector &vec1, d_real_vector &vec2);

  /** @brief all elemetnt arithmetic function **/
  d_real_vector operator-(dd_real_vector &vec);
  /** @brief all elemetnt arithmetic function **/
  d_real_vector operator-(d_real_vector &vec);

  /** @brief all elemetnt arithmetic function **/
  d_real_vector operator-=(dd_real_vector &vec);
  /** @brief all elemetnt arithmetic function **/
  d_real_vector operator-=(d_real_vector &vec);

  //--mul---------------------------------------
  /** @brief all elemetnt arithmetic function **/
  void mul(dd_real_vector &vec1, dd_real_vector &vec2);
  /** @brief all elemetnt arithmetic function **/
  void mul(d_real_vector &vec1, dd_real_vector &vec2);
  /** @brief all elemetnt arithmetic function **/
  void mul(dd_real_vector &vec1, d_real_vector &vec2);
  /** @brief all elemetnt arithmetic function **/
  void mul(d_real_vector &vec1, d_real_vector &vec2);

  /** @brief all elemetnt arithmetic function **/
  d_real_vector operator*(dd_real_vector &vec);
  /** @brief all elemetnt arithmetic function **/
  d_real_vector operator*(d_real_vector &vec);

  /** @brief all elemetnt arithmetic function **/
  d_real_vector operator*=(dd_real_vector &vec);
  /** @brief all elemetnt arithmetic function **/
  d_real_vector operator*=(d_real_vector &vec);
  //--div---------------------------------------
  /** @brief all elemetnt arithmetic function **/
  void div(dd_real_vector &vec1, dd_real_vector &vec2);
  /** @brief all elemetnt arithmetic function **/
  void div(d_real_vector &vec1, dd_real_vector &vec2);
  /** @brief all elemetnt arithmetic function **/
  void div(dd_real_vector &vec1, d_real_vector &vec2);
  /** @brief all elemetnt arithmetic function **/
  void div(d_real_vector &vec1, d_real_vector &vec2);

  /** @brief all elemetnt arithmetic function **/
  d_real_vector operator/(dd_real_vector &vec);
  /** @brief all elemetnt arithmetic function **/
  d_real_vector operator/(d_real_vector &vec);

  /** @brief all elemetnt arithmetic function **/
  d_real_vector operator/=(dd_real_vector &vec);
  /** @brief all elemetnt arithmetic function **/
  d_real_vector operator/=(d_real_vector &vec);
};

#endif
