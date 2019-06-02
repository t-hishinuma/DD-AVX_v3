#include<DD-AVX.hpp>

double d_real_SpMat::at(long r, long c){
		for(int j = row_ptr[r]; j < row_ptr[r+1]; j++){
			if(col_ind[j] == c){
				return val[j];
			}
		}
		return 0.0;
}

void d_real_SpMat::copy(const d_real_SpMat& mat){
	row = mat.row;
	nnz = mat.nnz;
	std::copy(mat.val.begin(), mat.val.end(), back_inserter(val));
	std::copy(mat.row_ptr.begin(), mat.row_ptr.end(), back_inserter(row_ptr));
	std::copy(mat.col_ind.begin(), mat.col_ind.end(), back_inserter(col_ind));
}

d_real_SpMat& d_real_SpMat::operator=(const d_real_SpMat& mat){
	this->copy(mat);
	return *this;
}

void get_row_vec(const long r, const d_real_SpMat& A, d_real_vector& ret){
	if((long)ret.size() != (long)A.get_row()){
		std::cerr << "error bad vector size" << std::endl;
		assert(1);
	};

	for(int j = A.row_ptr[r]; j < A.row_ptr[r+1]; j++){
		ret.data()[A.col_ind[j]] = A.val[j];
	}
}

void get_col_vec(const long c, const d_real_SpMat& A, d_real_vector& ret){
	if((long)ret.size() != (long)A.get_row()){
		std::cerr << "error bad vector size" << std::endl;
		assert(1);
	};

#pragma omp parallel for
	for(int i=0; i<A.row; i++){
		for(int j = A.row_ptr[i]; j < A.row_ptr[i+1]; j++){
			if(A.col_ind[j] == c)
				ret.data()[i] = A.val[j];
		}
	}
}

void get_diag_vec(const d_real_SpMat& A, d_real_vector& ret){
	if((long)ret.size() != (long)A.get_row()){
		std::cerr << "error bad vector size" << std::endl;
		assert(1);
	};

#pragma omp parallel for
	for(int i=0; i<A.row; i++){
		for(int j = A.row_ptr[i]; j < A.row_ptr[i+1]; j++){
			if(i == A.col_ind[j])
				ret.data()[i] = A.val[j];
		}
	}
}
