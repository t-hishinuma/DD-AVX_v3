#ifndef D_VECTOR_HPP
#define D_VECTOR_HPP

class dd_real_vector;
class dd_real_vector_ref;
struct dd_real;


class d_real_vector : public std::vector<double>{
	friend class dd_real_vector;
	public:
		d_real_vector() : std::vector<double>(){};

		d_real_vector(const std::vector<double>& obj) : std::vector<double>(obj) {}
		d_real_vector(int xxx) : std::vector<double>(xxx) {}
		d_real_vector(long xxx) : std::vector<double>(xxx) {}

		d_real_vector(int n, double val) : std::vector<double>(n, val) {}
		d_real_vector(long n, double val) : std::vector<double>(n, val) {}

		std::vector<double> HI(){return *this;}
		std::vector<double> LO(){
			std::vector<double> tmp(size(), 0.0);
			return tmp;
		}
//--I/O---------------------------------------
		void print_all(){
			for(int i=0; i<(int)size(); i++)
				std::cout << std::vector<double>::at(i) << std::endl;
		}
		void print(int i){
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

//--cast -------------------------------------
		operator double*(){
			return data();
		}

		operator dd_real_vector();

//--minus---------------------------------------
		void minus();
		d_real_vector operator-();

//--add---------------------------------------
		void add(dd_real_vector& vec1, dd_real_vector& vec2);
		void add(d_real_vector& vec1, dd_real_vector& vec2);
		void add(dd_real_vector& vec1, d_real_vector& vec2);
		void add(d_real_vector& vec1, d_real_vector& vec2);

		d_real_vector operator+(dd_real_vector& vec);
		d_real_vector operator+(d_real_vector& vec);

		d_real_vector operator+=(dd_real_vector& vec);
		d_real_vector operator+=(d_real_vector& vec);

//--sub---------------------------------------
		void sub(dd_real_vector& vec1, dd_real_vector& vec2);
		void sub(d_real_vector& vec1, dd_real_vector& vec2);
		void sub(dd_real_vector& vec1, d_real_vector& vec2);
		void sub(d_real_vector& vec1, d_real_vector& vec2);

		d_real_vector operator-(dd_real_vector& vec);
		d_real_vector operator-(d_real_vector& vec);

		d_real_vector operator-=(dd_real_vector& vec);
		d_real_vector operator-=(d_real_vector& vec);
		
//--mul---------------------------------------
		void mul(dd_real_vector& vec1, dd_real_vector& vec2);
		void mul(d_real_vector& vec1, dd_real_vector& vec2);
		void mul(dd_real_vector& vec1, d_real_vector& vec2);
		void mul(d_real_vector& vec1, d_real_vector& vec2);

		d_real_vector operator*(dd_real_vector& vec);
		d_real_vector operator*(d_real_vector& vec);

		d_real_vector operator*=(dd_real_vector& vec);
		d_real_vector operator*=(d_real_vector& vec);
//--div---------------------------------------
		void div(dd_real_vector& vec1, dd_real_vector& vec2);
		void div(d_real_vector& vec1, dd_real_vector& vec2);
		void div(dd_real_vector& vec1, d_real_vector& vec2);
		void div(d_real_vector& vec1, d_real_vector& vec2);

		d_real_vector operator/(dd_real_vector& vec);
		d_real_vector operator/(d_real_vector& vec);

		d_real_vector operator/=(dd_real_vector& vec);
		d_real_vector operator/=(d_real_vector& vec);
};

#endif
