#ifndef DD_VECTOR_HPP
#define DD_VECTOR_HPP

class d_real_vector;
struct dd_real;

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

class dd_real_vector{

	private:
		int N=0;

	public:
		std::vector<double> hi;
		std::vector<double> lo;
		dd_real_vector(){}

		dd_real_vector(int n){
			N=n;
 			hi.resize(N);
 			lo.resize(N);
		}

		dd_real_vector(int n, double val){
			N=n;
			hi.resize(N, val);
			lo.resize(N, 0.0);
		}

		dd_real_vector(int n, dd_real val){
			N=n;
			hi.resize(N, val.x[0]);
			lo.resize(N, val.x[1]);
		}

		dd_real_vector_ref operator[](int n) {
			return dd_real_vector_ref(hi.begin() + n, lo.begin() + n);
		}
//--cast -------------------------------------
		operator std::vector<double>();
		operator double*();
		operator d_real_vector();

//--getinfo---------------------------------------
		int size() const{return N;};

		double* data(){return hi.data();};
		double* hi_data(){return hi.data();};
		double* lo_data(){return lo.data();};

		std::vector<double> HI(){return this->hi;}
		std::vector<double> LO(){return this->lo;}

		dd_real at(int n){
			dd_real tmp;
			tmp.x[0] = hi[n];
			tmp.x[1] = lo[n];
			return tmp;
		};

//--I/O---------------------------------------
		void print_all(){ for(int i=0; i<N; i++) std::cout << hi[i] << ", " << lo[i] << std::endl; }
		void print(int i){ std::cout << hi[i] << ", " << lo[i] << std::endl;}

		void input(const char* filename);
		void input_mm(FILE *file);
		void input_plane(FILE *file);
		void output_mm(const char *filename);
		void output_plane(const char *filename);

//--allocate, free---------------------------------------
		void resize(int n){
			N=n;
			hi.resize(N);
			lo.resize(N);
		}

		void resize(int n, double val){
			N=n;
			hi.resize(N, val);
			lo.resize(N, 0.0);
		};

		void resize(int n, dd_real val){
			N=n;
			hi.resize(N, val.x[0]);
			lo.resize(N, val.x[1]);
		};

		void push_back(const double val){
			N=N+1;
			hi.push_back(val);
			lo.push_back(0.0);
		}

		void push_back(const dd_real val){
			N=N+1;
			hi.push_back(val.x[0]);
			lo.push_back(val.x[1]);
		}

		void clear(){
			N=0;
			hi.clear();
			lo.clear();
		}

//--copy---------------------------------------
		void copy(const dd_real_vector& vec);
		void copy(const d_real_vector& vec);
		void copy(const std::vector<double>& vec);
		void copy(const std::vector<dd_real>& vec);

		dd_real_vector& operator=(const dd_real_vector& vec);
		dd_real_vector& operator=(const d_real_vector& vec);
		dd_real_vector& operator=(const std::vector<double>& vec);
		dd_real_vector& operator=(const std::vector<dd_real>& vec);

//--comparision---------------------------------------

		bool operator==(const dd_real_vector& vec);
		bool operator==(const d_real_vector& vec);
		bool operator==(const std::vector<double>& vec);
		bool operator==(const std::vector<dd_real>& vec);

		bool operator!=(const dd_real_vector& vec);
		bool operator!=(const d_real_vector& vec);
		bool operator!=(const std::vector<double>& vec);
		bool operator!=(const std::vector<dd_real>& vec);

//--minus---------------------------------------
		void minus();
		dd_real_vector operator-();

//--add---------------------------------------
		void add(dd_real_vector& vec1, dd_real_vector& vec2);
		void add(d_real_vector& vec1, dd_real_vector& vec2);
		void add(dd_real_vector& vec1, d_real_vector& vec2);
		void add(d_real_vector& vec1, d_real_vector& vec2);

		dd_real_vector operator+(dd_real_vector& vec);
		dd_real_vector operator+(d_real_vector& vec);

		dd_real_vector operator+=(dd_real_vector& vec);
		dd_real_vector operator+=(d_real_vector& vec);

//--sub---------------------------------------
		void sub(dd_real_vector& vec1, dd_real_vector& vec2);
		void sub(d_real_vector& vec1, dd_real_vector& vec2);
		void sub(dd_real_vector& vec1, d_real_vector& vec2);
		void sub(d_real_vector& vec1, d_real_vector& vec2);

		dd_real_vector operator-(dd_real_vector& vec);
		dd_real_vector operator-(d_real_vector& vec);

		dd_real_vector operator-=(dd_real_vector& vec);
		dd_real_vector operator-=(d_real_vector& vec);

//--mul---------------------------------------
		void mul(dd_real_vector& vec1, dd_real_vector& vec2);
		void mul(d_real_vector& vec1, dd_real_vector& vec2);
		void mul(dd_real_vector& vec1, d_real_vector& vec2);
		void mul(d_real_vector& vec1, d_real_vector& vec2);

		dd_real_vector operator*(dd_real_vector& vec);
		dd_real_vector operator*(d_real_vector& vec);

		dd_real_vector operator*=(dd_real_vector& vec);
		dd_real_vector operator*=(d_real_vector& vec);

//--div---------------------------------------
		void div(dd_real_vector& vec1, dd_real_vector& vec2);
		void div(d_real_vector& vec1, dd_real_vector& vec2);
		void div(dd_real_vector& vec1, d_real_vector& vec2);
		void div(d_real_vector& vec1, d_real_vector& vec2);

		dd_real_vector operator/(dd_real_vector& vec);
		dd_real_vector operator/(d_real_vector& vec);

		dd_real_vector operator/=(dd_real_vector& vec);
		dd_real_vector operator/=(d_real_vector& vec);
};
#endif
