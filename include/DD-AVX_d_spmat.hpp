#ifndef DD_MATRIX_HPP
#define DD_MATRIX_HPP

class d_real_vector;
class dd_real_vector;
struct dd_real;

/** @brief double precision CRS format sparse matrix **/
class d_real_SpMat{
	public:
		int row=0;
		int nnz=0;
		std::vector<double> val;
		std::vector<int> row_ptr;
		std::vector<int> col_ind;

		d_real_SpMat(){}

/** @brief allocate size r * c matrix **/
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

/** @brief allocate size r * c, nnz=NNZ matrix **/
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
/** @brief free **/
		void clear(){
			row = 0;
			nnz = 0;
			val.clear();
			row_ptr.clear();
			col_ind.clear();
		}

//--I/O---------------------------------------
/** @brief input matrix from matrix market format **/
		void input_mm(const char* filename);

/** @brief output matrix to matrix market format **/
		void output_mm(const char* filename);

/** @brief output matrix to standard I/O **/
		void output();

//--get---------------------------------------
/** @brief get # of row **/
		int get_row() const{return row;};

/** @brief get # of col. **/
		int get_nnz() const{return nnz;};

/** @brief get A[r, c] **/
		double at(const int r, const int c);

/** @brief insert value a to A[r, c] **/
		void insert(const int r, const int c, const double a);

/** @brief get row vector A[r,*] **/
		d_real_vector get_row_vec(const int r);

/** @brief get col vector A[*,c] **/
		d_real_vector get_col_vec(const int c);

/** @brief get diagonal vector **/
		d_real_vector get_diag_vec();

/** @brief get CRS value array **/
		std::vector<double>::reference data() {
			return val[0];
		}


// //--copy---------------------------------------
/** @brief copy, mat = A **/
		void copy(const d_real_SpMat& mat);

/** @brief copy operator  **/
		d_real_SpMat& operator=(const d_real_SpMat& mat);
};

#endif
