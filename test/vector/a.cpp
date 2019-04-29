#include <vector>
#include <complex>
#include<a.hpp>

template<typename T>
class Complex_ref {
    typename std::vector<T>::iterator real_iter;
    typename std::vector<T>::iterator imag_iter;
public:
    Complex_ref(typename std::vector<T>::iterator r, typename std::vector<T>::iterator i)
        : real_iter(r), imag_iter(i) {}

    operator double() const{
		return *real_iter;
	}

    void operator=(dd_real c)
	{
		printf("=dayo %f, %f\n",c.x[0], c.x[1]);
		*real_iter = c.x[0]; *imag_iter = c.x[1];
	}

    operator dd_real()
	{
		printf("()dayo\n");
		return dd_real(*real_iter, *imag_iter);
	}
};

template<typename T>
class Complex_vector {
public:
    std::vector<T> real;
    std::vector<T> imag;
    Complex_vector(std::size_t n) : real(n), imag(n) {}

    Complex_ref<T> operator[](size_t n) {
		printf("[%d]dayo\n",n);
        return Complex_ref<T>(real.begin() + n, imag.begin() + n);
    }
};

#include <iostream>

int main() {
    Complex_vector<double> cv(5);
	dd_real a;
    for (int i = 0; i < 5; ++i) {
		a = i;
        cv[i] = a; // set
    }
     for (int i = 0; i < 5; ++i) {
         dd_real item = cv[i]; // get
		 std::cout << item << std::endl;
		 printf("hoge%f\n",(double)cv[i]);
     }
}
