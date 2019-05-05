#ifndef DD_VECTOR_HPP
#define DD_VECTOR_HPP
#include<./d_vector.hpp>

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

    void operator=(dd_real c){
		*dd_hi_iter = c.x[0];
	   	*dd_lo_iter = c.x[1];
	}

    operator dd_real(){
		return dd_real(*dd_hi_iter, *dd_lo_iter);
	}
};

class dd_real_vector{

	private:
		long N=0;

	public:
		std::vector<double> hi;
		std::vector<double> lo;

		dd_real_vector(){}

		dd_real_vector(long n){
			N=n;
 			hi.resize(N);
 			lo.resize(N);
		}

		dd_real_vector(long n, double val){
			N=n;
			hi.resize(N, val);
			lo.resize(N, 0.0);
		}

		dd_real_vector(long n, dd_real val){
			N=n;
			hi.resize(N, val.x[0]);
			lo.resize(N, val.x[1]);
		}

		dd_real_vector_ref<double> operator[](long n) {
			return dd_real_vector_ref<double>(hi.begin() + n, lo.begin() + n);
		}

//--getinfo---------------------------------------
		long size() const{return N;};

		double* data(){return hi.data();};
		double* hi_data(){return hi.data();};
		double* lo_data(){return lo.data();};

		dd_real at(int n){
			dd_real tmp;
			tmp.x[0] = hi[n];
			tmp.x[1] = lo[n];
			return tmp;
		};

//--I/O---------------------------------------
		void print_all(){ for(int i=0; i<N; i++) std::cout << hi[i] << ", " << lo[i] << std::endl; }
		void print(long i){ std::cout << hi[i] << ", " << lo[i] << std::endl;}

		void input(const char* filename);
		void input_mm(FILE *file);
		void input_plane(FILE *file);
		void output_mm(const char *filename);
		void output_plane(const char *filename);

//--allocate, free---------------------------------------
		void resize(long n){
			N=n;
			hi.resize(N);
			lo.resize(N);
		}

		void resize(long n, double val){
			N=n;
			hi.resize(N, val);
			lo.resize(N, 0.0);
		};

		void resize(long n, dd_real val){
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

//--comparision---------------------------------------
		void add(const dd_real_vector& vec1, const dd_real_vector& vec2);

};
#endif
