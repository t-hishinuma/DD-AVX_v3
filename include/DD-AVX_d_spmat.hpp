#ifndef DD_MATRIX_HPP
#define DD_MATRIX_HPP

class d_real_vector;
class dd_real_vector;
struct dd_real;

class d_real_SpMat{
	public:
		int row=0;
		int nnz=0;
		std::vector<double> val;
		std::vector<int> row_ptr;
		std::vector<int> col_ind;

		d_real_SpMat(){}

		d_real_SpMat(int r, int c){
			if(r != c){
				std::cerr << "error, r!=c, square matrix only now" << std::endl;
				assert(1);
			}
			row=r;
			nnz = 0;
			val.resize(nnz, 0.0);
			row_ptr.resize(row+1, 0);
			col_ind.resize(nnz, 0);
		}

		d_real_SpMat(int r, int c, int NNZ){
			if(r != c){
				std::cerr << "error, r!=c, square matrix only now" << std::endl;
				assert(1);
			}
			row=r;
			nnz=NNZ;
			val.resize(nnz, 0.0);
			row_ptr.resize(row+1, 0);
			col_ind.resize(nnz, 0);
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

//--get---------------------------------------
		int get_row() const{return row;};
		int get_nnz() const{return nnz;};

		double at(const int r, const int c);
		void insert(const int r, const int c, const double a);

		d_real_vector get_row_vec(const int r);
		d_real_vector get_col_vec(const int c);
		d_real_vector get_diag_vec();

		std::vector<double>::reference datas(int r, int c) {
			return val[0];
		}


// //--copy---------------------------------------
		void copy(const d_real_SpMat& mat);

		d_real_SpMat& operator=(const d_real_SpMat& mat);
};

#endif
