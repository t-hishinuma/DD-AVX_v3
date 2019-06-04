#ifndef DD_MATRIX_HPP
#define DD_MATRIX_HPP

class d_real_vector;
class dd_real_vector;
struct dd_real;

class d_real_SpMat{
	public:
		long row=0;
		long nnz=0;
		std::vector<double> val;
		std::vector<long> row_ptr;
		std::vector<long> col_ind;

		d_real_SpMat(){}

		d_real_SpMat(long N, long NNZ){
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
		void input_mm(const char* filename);
		void output_mm(const char* filename);
		void output();

//--getinfo---------------------------------------
		long get_row() const{return row;};
		long get_nnz() const{return nnz;};
		double at(long r, long c);


// //--copy---------------------------------------
		void copy(const d_real_SpMat& mat);

		d_real_SpMat& operator=(const d_real_SpMat& mat);
};

void get_row_vec(const long r, const d_real_SpMat& A, d_real_vector& ret);
void get_col_vec(const long c, const d_real_SpMat& A, d_real_vector& ret);
void get_diag_vec(const d_real_SpMat& A, d_real_vector& ret);
#endif