#ifndef DD_MATRIX_HPP
#define DD_MATRIX_HPP

class d_real_vector;
class dd_real_vector;
struct dd_real;

class d_real_matrix{
	public:
		long row=0;
		long nnz=0;
		std::vector<double> val;
		std::vector<long> row_ptr;
		std::vector<long> col_ind;

		d_real_matrix(){}

		d_real_matrix(long N, long NNZ){
			row=N;
			nnz=NNZ;
			val.resize(NNZ, 0.0);
			row_ptr.resize(N+1, -1.0);
			col_ind.resize(NNZ, -1.0);
		}

//--allocate, free---------------------------------------
		void clear(){
			row = 0;
			nnz = 0;
			val.clear();
			row_ptr.clear();
			col_ind.clear();
		}

//--I/O---------------------------------------
		void input_mm(char* filename);

//--getinfo---------------------------------------
		long get_row() const{return row;};
		long get_nnz() const{return nnz;};


		double at(long r, long c);


// //--copy---------------------------------------
// 		void copy(const d_matrix& mat);
//
// 		dd_real_vector& operator=(const dd_real_vector& vec);
// 		dd_real_vector& operator=(const d_real_vector& vec);
// 		dd_real_vector& operator=(const std::vector<double>& vec);
// 		dd_real_vector& operator=(const std::vector<dd_real>& vec);
// //--I/O---------------------------------------
// 		void print_all(){ for(int i=0; i<N; i++) std::cout << hi[i] << ", " << lo[i] << std::endl; }
// 		void print(long i){ std::cout << hi[i] << ", " << lo[i] << std::endl;}
//
// 		void input(const char* filename);
// 		void input_mm(FILE *file);
// 		void input_plane(FILE *file);
// 		void output_mm(const char *filename);
// 		void output_plane(const char *filename);
//
// 		void convert();
};
#endif
