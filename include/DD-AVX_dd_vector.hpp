#ifndef DD_VECTOR_HPP
#define DD_VECTOR_HPP

class d_real_vector;
struct dd_real;

/** @brief Double-double precision vector reference class **/
class dd_real_vector_ref
{
public:
    typename std::vector<double>::iterator dd_hi_iter;
    typename std::vector<double>::iterator dd_lo_iter;

    dd_real_vector_ref(typename std::vector<double>::iterator hi, typename std::vector<double>::iterator lo)
        : dd_hi_iter(hi), dd_lo_iter(lo) {}

    operator double() const{
		return *dd_hi_iter;
	}

    operator dd_real() const{
		return dd_real(*dd_hi_iter, *dd_lo_iter);
	}

    void operator=(dd_real c){
		*dd_hi_iter = c.x[0];
	   	*dd_lo_iter = c.x[1];
	}

	void operator=(dd_real_vector_ref& c){
		*dd_hi_iter = *c.dd_hi_iter;
	   	*dd_lo_iter = *c.dd_lo_iter;
	}

	void operator=(double& c){
		*dd_hi_iter = c;
		*dd_lo_iter = 0.0;
	}

	dd_real operator+(const dd_real a);
	dd_real operator+(dd_real_vector_ref c);
	dd_real operator+(double c);
	dd_real operator-(const dd_real a);
	dd_real operator-(dd_real_vector_ref c);
	dd_real operator-(double c);
	dd_real operator*(const dd_real a);
	dd_real operator*(dd_real_vector_ref c);
	dd_real operator*(double c);
	dd_real operator/(const dd_real a);
	dd_real operator/(dd_real_vector_ref c);
	dd_real operator/(double c);
// 	QD_API std::ostream& operator<<(std::ostream &s, const dd_real &a);
// 	QD_API std::istream& operator>>(std::istream &s, dd_real &a);
};

dd_real operator+(const dd_real a, const dd_real_vector_ref b);
dd_real operator+(const double a, const dd_real_vector_ref b);
dd_real operator-(const dd_real a, const dd_real_vector_ref b);
dd_real operator-(const double a, const dd_real_vector_ref b);
dd_real operator*(const dd_real a, const dd_real_vector_ref b);
dd_real operator*(const double a, const dd_real_vector_ref b);
dd_real operator/(const dd_real a, const dd_real_vector_ref b);
dd_real operator/(const double a, const dd_real_vector_ref b);

/** @brief Double-double precision vector class **/
class dd_real_vector{

	private:
		int N=0;

	public:
		std::vector<double> hi;
		std::vector<double> lo;
		dd_real_vector(){}

/** @brief create size N DD vector **/
		dd_real_vector(int n){
			N=n;
 			hi.resize(N);
 			lo.resize(N);
		}

/** @brief create size N, all element is val DD vector **/
		dd_real_vector(int n, double val){
			N=n;
			hi.resize(N, val);
			lo.resize(N, 0.0);
		}

/** @brief create size N, all element is val DD vector **/
		dd_real_vector(int n, dd_real val){
			N=n;
			hi.resize(N, val.x[0]);
			lo.resize(N, val.x[1]);
		}

/** @brief get vec[i] value **/
		dd_real_vector_ref operator[](int i) {
			return dd_real_vector_ref(hi.begin() + i, lo.begin() + i);
		}
//--cast -------------------------------------
/** @brief down cast to std::vector<double> **/
		operator std::vector<double>();

/** @brief down cast to double precision array **/
		operator double*();

/** @brief down cast to d_real_vector **/
		operator d_real_vector();

//--getinfo---------------------------------------
/** @brief get size **/
		int size() const{return N;};

/** @brief get hi array pointer **/
		double* data(){return hi.data();};
/** @brief get hi array pointer **/
		double* hi_data(){return hi.data();};
/** @brief get lo array pointer **/
		double* lo_data(){return lo.data();};

/** @brief get hi array pointer **/
		std::vector<double> HI(){return this->hi;}
/** @brief get lo array pointer **/
		std::vector<double> LO(){return this->lo;}

/** @brief get vec[i] value **/
		dd_real at(int i){
			dd_real tmp;
			tmp.x[0] = hi[i];
			tmp.x[1] = lo[i];
			return tmp;
		};

//--I/O---------------------------------------
/** @brief output all elements to standard I/O **/
		void print_all(){ for(int i=0; i<N; i++) std::cout << hi[i] << ", " << lo[i] << std::endl; }
/** @brief output vec[i] to standard I/O **/
		void print(int i){ std::cout << hi[i] << ", " << lo[i] << std::endl;}

/** @brief create vector from file **/
		void input(const char* filename);
/** @brief create vector from matrix market file **/
		void input_mm(FILE *file);
/** @brief create vector from plane file **/
		void input_plane(FILE *file);
/** @brief output vector to matrix market file **/
		void output_mm(const char *filename);
/** @brief output vector to plane file **/
		void output_plane(const char *filename);

//--allocate, free---------------------------------------
/** @brief resize, this method is almost same as std::vector **/
		void resize(int n){
			N=n;
			hi.resize(N);
			lo.resize(N);
		}

/** @brief resize, this method is almost same as std::vector **/
		void resize(int n, double val){
			N=n;
			hi.resize(N, val);
			lo.resize(N, 0.0);
		};

/** @brief resize, this method is almost same as std::vector **/
		void resize(int n, dd_real val){
			N=n;
			hi.resize(N, val.x[0]);
			lo.resize(N, val.x[1]);
		};

/** @brief push_back, this method is almost same as std::vector **/
		void push_back(const double val){
			N=N+1;
			hi.push_back(val);
			lo.push_back(0.0);
		}

/** @brief push_back, this method is almost same as std::vector **/
		void push_back(const dd_real val){
			N=N+1;
			hi.push_back(val.x[0]);
			lo.push_back(val.x[1]);
		}

/** @brief clear, this method is almost same as std::vector **/
		void clear(){
			N=0;
			hi.clear();
			lo.clear();
		}

//--copy---------------------------------------
/** @brief copy from dd_real_vector **/
		void copy(const dd_real_vector& vec);
/** @brief copy from d_real_vector **/
		void copy(const d_real_vector& vec);
/** @brief copy from std::vector<double> **/
		void copy(const std::vector<double>& vec);
/** @brief copy from std::vector<dd_real> **/
		void copy(const std::vector<dd_real>& vec);

/** @brief copy from dd_real_vector **/
		dd_real_vector& operator=(const dd_real_vector& vec);
/** @brief copy from d_real_vector **/
		dd_real_vector& operator=(const d_real_vector& vec);
/** @brief copy from std::vector<double> **/
		dd_real_vector& operator=(const std::vector<double>& vec);
/** @brief copy from std::vector<dd_real> **/
		dd_real_vector& operator=(const std::vector<dd_real>& vec);

//--comparision---------------------------------------

/** @brief comparision function **/
		bool operator==(const dd_real_vector& vec);
/** @brief comparision function **/
		bool operator==(const d_real_vector& vec);
/** @brief comparision function **/
		bool operator==(const std::vector<double>& vec);
/** @brief comparision function **/
		bool operator==(const std::vector<dd_real>& vec);

/** @brief comparision function **/
		bool operator!=(const dd_real_vector& vec);
/** @brief comparision function **/
		bool operator!=(const d_real_vector& vec);
/** @brief comparision function **/
		bool operator!=(const std::vector<double>& vec);
/** @brief comparision function **/
		bool operator!=(const std::vector<dd_real>& vec);

//--minus---------------------------------------
/** @brief sign **/
		void minus();
/** @brief sign **/
		dd_real_vector operator-();

//--add---------------------------------------
/** @brief all elemetnt arithmetic function **/
		void add(dd_real_vector& vec1, dd_real_vector& vec2);
/** @brief all elemetnt arithmetic function **/
		void add(d_real_vector& vec1, dd_real_vector& vec2);
/** @brief all elemetnt arithmetic function **/
		void add(dd_real_vector& vec1, d_real_vector& vec2);
/** @brief all elemetnt arithmetic function **/
		void add(d_real_vector& vec1, d_real_vector& vec2);

/** @brief all elemetnt arithmetic function **/
		dd_real_vector operator+(dd_real_vector& vec);
/** @brief all elemetnt arithmetic function **/
		dd_real_vector operator+(d_real_vector& vec);

/** @brief all elemetnt arithmetic function **/
		dd_real_vector operator+=(dd_real_vector& vec);
/** @brief all elemetnt arithmetic function **/
		dd_real_vector operator+=(d_real_vector& vec);

//--sub---------------------------------------
/** @brief all elemetnt arithmetic function **/
		void sub(dd_real_vector& vec1, dd_real_vector& vec2);
/** @brief all elemetnt arithmetic function **/
		void sub(d_real_vector& vec1, dd_real_vector& vec2);
/** @brief all elemetnt arithmetic function **/
		void sub(dd_real_vector& vec1, d_real_vector& vec2);
/** @brief all elemetnt arithmetic function **/
		void sub(d_real_vector& vec1, d_real_vector& vec2);

/** @brief all elemetnt arithmetic function **/
		dd_real_vector operator-(dd_real_vector& vec);
/** @brief all elemetnt arithmetic function **/
		dd_real_vector operator-(d_real_vector& vec);

/** @brief all elemetnt arithmetic function **/
		dd_real_vector operator-=(dd_real_vector& vec);
/** @brief all elemetnt arithmetic function **/
		dd_real_vector operator-=(d_real_vector& vec);

//--mul---------------------------------------
/** @brief all elemetnt arithmetic function **/
		void mul(dd_real_vector& vec1, dd_real_vector& vec2);
/** @brief all elemetnt arithmetic function **/
		void mul(d_real_vector& vec1, dd_real_vector& vec2);
/** @brief all elemetnt arithmetic function **/
		void mul(dd_real_vector& vec1, d_real_vector& vec2);
/** @brief all elemetnt arithmetic function **/
		void mul(d_real_vector& vec1, d_real_vector& vec2);

/** @brief all elemetnt arithmetic function **/
		dd_real_vector operator*(dd_real_vector& vec);
/** @brief all elemetnt arithmetic function **/
		dd_real_vector operator*(d_real_vector& vec);

/** @brief all elemetnt arithmetic function **/
		dd_real_vector operator*=(dd_real_vector& vec);
/** @brief all elemetnt arithmetic function **/
		dd_real_vector operator*=(d_real_vector& vec);

//--div---------------------------------------
/** @brief all elemetnt arithmetic function **/
		void div(dd_real_vector& vec1, dd_real_vector& vec2);
/** @brief all elemetnt arithmetic function **/
		void div(d_real_vector& vec1, dd_real_vector& vec2);
/** @brief all elemetnt arithmetic function **/
		void div(dd_real_vector& vec1, d_real_vector& vec2);
/** @brief all elemetnt arithmetic function **/
		void div(d_real_vector& vec1, d_real_vector& vec2);

/** @brief all elemetnt arithmetic function **/
		dd_real_vector operator/(dd_real_vector& vec);
/** @brief all elemetnt arithmetic function **/
		dd_real_vector operator/(d_real_vector& vec);

/** @brief all elemetnt arithmetic function **/
		dd_real_vector operator/=(dd_real_vector& vec);
/** @brief all elemetnt arithmetic function **/
		dd_real_vector operator/=(d_real_vector& vec);
};
#endif
