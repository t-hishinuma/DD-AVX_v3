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
