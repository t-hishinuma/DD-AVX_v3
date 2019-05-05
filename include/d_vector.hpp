#ifndef D_VECTOR_HPP
#define D_VECTOR_HPP
#include<./DD-AVX.hpp>
class dd_real_vector;

class d_real_vector : public std::vector<double>{
	public:
		d_real_vector() : std::vector<double>(){};

		d_real_vector(const std::vector<double>& obj) : std::vector<double>(obj) {}
		d_real_vector(int xxx) : std::vector<double>(xxx) {}
		d_real_vector(long xxx) : std::vector<double>(xxx) {}

		d_real_vector(int n, double val) : std::vector<double>(n, val) {}
		d_real_vector(long n, double val) : std::vector<double>(n, val) {}

		std::vector<double> hi(){return hi;}
		std::vector<double> lo(){
			std::vector tmp(size(), 0.0);
			return tmp;
		}
//--I/O---------------------------------------
		void print_all(){
			for(long i=0; i<(long)size(); i++)
				std::cout << std::vector<double>::at(i) << std::endl;
		}
		void print(long i){
			std::cout << std::vector<double>::at(i) << std::endl;
		}

		void input(const char* filename);
		void input_mm(FILE *file);
		void input_plane(FILE *file);
		void output_mm(const char *filename);
		void output_plane(const char *filename);

//--copy---------------------------------------
		void copy(const dd_real_vector& vec);
		void copy(const d_real_vector& vec);
		void copy(const std::vector<double>& vec);
		void copy(const std::vector<dd_real>& vec);

		d_real_vector& operator=(const dd_real_vector& vec);
		d_real_vector& operator=(const d_real_vector& vec);
		d_real_vector& operator=(const std::vector<double>& vec);
		d_real_vector& operator=(const std::vector<dd_real>& vec);

//--comparision == ---------------------------------------
		bool operator==(const dd_real_vector& vec);
		bool operator==(const d_real_vector& vec);
		bool operator==(const std::vector<double>& vec);
		bool operator==(const std::vector<dd_real>& vec);

		bool operator!=(const dd_real_vector& vec);
		bool operator!=(const d_real_vector& vec);
		bool operator!=(const std::vector<double>& vec);
		bool operator!=(const std::vector<dd_real>& vec);
};

#endif
