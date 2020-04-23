#ifndef DD_MATRIX_HPP
#define DD_MATRIX_HPP

class d_real_vector;
class dd_real_vector;
struct dd_real;

class dd_real_SpMat{
	public:
		size_t row=0;
		size_t nnz=0;
		dd_real_vector val;
		std::vector<size_t> row_ptr;
		std::vector<size_t> col_ind;

		dd_real_SpMat(){}

		dd_real_SpMat(size_t r, size_t c){
			if(r != c){
				std::cerr << "error, r!=c, square matrix only now" << std::endl;
				assert(1);
			}
			row=r;
			nnz = 0;
			val.resize(nnz, 0.0);
			row_ptr.resize(row+1, 0);
			col_ind.resize(nnz, -1.0);
		}

		dd_real_SpMat(size_t r, size_t c, size_t NNZ){
			if(r != c){
				std::cerr << "error, r!=c, square matrix only now" << std::endl;
				assert(1);
			}
			row=r;
			nnz=NNZ;
			val.resize(nnz, 0.0);
			row_ptr.resize(row+1, 0);
			col_ind.resize(nnz, -1.0);
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
		size_t get_row() const{return row;};
		size_t get_nnz() const{return nnz;};
		size_t size() const{return row;};

		double at(const size_t r, const size_t c);
		void insert(const size_t r, const size_t c, const double a);

		d_real_vector get_row_vec(const size_t r);
		d_real_vector get_col_vec(const size_t c);
		d_real_vector get_diag_vec();

		std::vector<double>::reference datas(size_t r, size_t c) {
			return val[0];
		}


// //--copy---------------------------------------
		void copy(const d_real_SpMat& mat);

		d_real_SpMat& operator=(const d_real_SpMat& mat);
};

#endif
