#ifndef DD_AVX_VEC_HPP
#define DD_AVX_VEC_HPP

template<typename T>
class dd_real_vector_ref
{
    typename std::vector<T>::iterator dd_hi_iter;
    typename std::vector<T>::iterator dd_lo_iter;
public:
    dd_real_vector_ref(typename std::vector<T>::iterator hi, typename std::vector<T>::iterator lo)
        : dd_hi_iter(hi), dd_lo_iter(lo) {}

    operator double() const{
		return *dd_hi_iter;
	}

    operator dd_real() const{
		return dd_real(*dd_hi_iter, *dd_lo_iter);
	}

    void operator=(dd_real c)
	{
		*dd_hi_iter = c.x[0];
	   	*dd_lo_iter = c.x[1];
	}

    operator dd_real()
	{
		return dd_real(*dd_hi_iter, *dd_lo_iter);
	}
};


class dd_real_vector{

	private:
		long N=0;
		double memsize=0;

	public:
		std::vector<double> hi;
		std::vector<double> lo;

		dd_real_vector(){}

		dd_real_vector(long n){
			N=n;
 			hi.resize(N);
 			lo.resize(N);
			memsize = N * sizeof(double) * 2;
		}

		dd_real_vector(long n, double val){
			N=n;
			hi.resize(N, val);
			lo.resize(N, 0.0);
			memsize = N * sizeof(double) * 2;
		}

		dd_real_vector(long n, dd_real val){
			N=n;
			hi.resize(N, val.x[0]);
			lo.resize(N, val.x[1]);
			memsize = N * sizeof(double) * 2;
		}

		dd_real_vector_ref<double> operator[](long n) {
			return dd_real_vector_ref<double>(hi.begin() + n, lo.begin() + n);
		}

//--getinfo---------------------------------------
		long size(){return N;};
		double mem_size(){return memsize;};

		double* data(){return hi.data();};
		double* hi_data(){return hi.data();};
		double* lo_data(){return lo.data();};

		dd_real at(int n){
			dd_real tmp;
			tmp.x[0] = hi[n];
			tmp.x[1] = lo[n];
			return tmp;
		};

//--print---------------------------------------
		void print_all(){ for(int i=0; i<N; i++) std::cout << hi[i] << ", " << lo[i] << std::endl; }

		void print(long i){ std::cout << hi[i] << ", " << lo[i] << std::endl;}

//--allocate, free---------------------------------------
		void resize(long n);
		void resize(long n, double val);
		void resize(long n, dd_real val);
		void push_back(const double val);
		void push_back(const dd_real val);

		void clear();
		void erase();
	
};

#endif
// template<typename T>
// class Complex_vector {
// public:
//     std::vector<T> real;
//     std::vector<T> imag;
//
//     }
// };
//
//
// #include <iostream>
//
// int main() {
//     Complex_vector<double> cv(5);
// 	dd_real a;
//     for (int i = 0; i < 5; ++i) {
// 		a = i;
//         cv[i] = a; // set
//     }
//      for (int i = 0; i < 5; ++i) {
//          dd_real item = cv[i]; // get
// 		 std::cout << item << std::endl;
// 		 printf("hoge%f\n",(double)cv[i]);
//      }
// }
//
// 		// add
// 		static dd_real add(double a, double b);
// 		dd_real &operator+=(double a);
// 		dd_real &operator+=(const dd_real &a);
//
// 		//minus
// 		static dd_real sub(double a, double b);
// 		dd_real operator-() const;
// 		dd_real &operator-=(double a);
// 		dd_real &operator-=(const dd_real &a);
//
// 		//mul
// 		static dd_real mul(double a, double b);
// 		dd_real &operator*=(double a);
// 		dd_real &operator*=(const dd_real &a);
// 		//div
// 		static dd_real div(double a, double b);
// 		dd_real &operator/=(double a);
// 		dd_real &operator/=(const dd_real &a);
//
// 		dd_real &operator=(double a);
// 		dd_real &operator=(const char *s);
//
// 		at;
// 		operator[];
// 		data;
// 		front;
// 		back;
//
// 		size;
// 		resize;
//
// 	  new
// 	  (allocate)
//
// 	begin
// 	end
//

// QD_API dd_real operator+(const dd_real &a, double b);
// QD_API dd_real operator+(double a, const dd_real &b);
// QD_API dd_real operator+(const dd_real &a, const dd_real &b);
//
// QD_API dd_real operator-(const dd_real &a, double b);
// QD_API dd_real operator-(double a, const dd_real &b);
// QD_API dd_real operator-(const dd_real &a, const dd_real &b);
//
// QD_API dd_real operator*(const dd_real &a, double b);
// QD_API dd_real operator*(double a, const dd_real &b);
// QD_API dd_real operator*(const dd_real &a, const dd_real &b);
//
// QD_API dd_real operator/(const dd_real &a, double b);
// QD_API dd_real operator/(double a, const dd_real &b);
// QD_API dd_real operator/(const dd_real &a, const dd_real &b);
//
// QD_API bool operator==(const dd_real &a, double b);
// QD_API bool operator==(double a, const dd_real &b);
// QD_API bool operator==(const dd_real &a, const dd_real &b);
//
// QD_API bool operator!=(const dd_real &a, double b);
// QD_API bool operator!=(double a, const dd_real &b);
// QD_API bool operator!=(const dd_real &a, const dd_real &b);
//
//       DD_Scalar dot(D_Vector vx, D_Vector vy);
//       DD_Scalar dot(DD_Vector vx, D_Vector vy);
//       DD_Scalar dot(D_Vector vx, DD_Vector vy);
//       DD_Scalar dot(DD_Vector vx, DD_Vector vy);
//
//       DD_Scalar nrm2(D_Vector vx);
//       DD_Scalar nrm2(DD_Vector vx);
//
