#include<DD-AVX.hpp>

double d_real_SpMat::at(const long r, const long c){
		for(int j = row_ptr[r]; j < row_ptr[r+1]; j++){
			if(col_ind[j] == c){
				return val[j];
			}
		}
		return 0.0;
}

void d_real_SpMat::insert(const long r, const long c, const double a){
	//printf("insert start r = %d, c = %d, a = %f\n", r, c, a);

	for(int j = row_ptr[r]; j < row_ptr[r+1]; j++){
		if(col_ind[j] == c){
			val[j] = a;
			return;
		}
	}

	//pos_check
	int pos = row_ptr[r+1]; 

	for(int j = row_ptr[r]; j < row_ptr[r+1]; j++){
		if( c < col_ind[j]){
			pos = j;
			break;
		}
	}
	//printf("pos = %d\n", pos);


	val.insert(val.begin() + pos, a);
	col_ind.insert(col_ind.begin() + pos, c);
	nnz++;

	for(int i = r+1; i < row+1; i++){
		row_ptr[i]++; 
	}
	//printf("row_ptr: %d, %d, %d\n", row_ptr[0], row_ptr[1], row_ptr[2]);
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

////////////////////////////////////////////////
d_real_vector d_real_SpMat::get_row_vec(const long r){
	if(row < r){
		std::cerr << "error bad row" << std::endl;
		assert(1);
	}

	std::vector<double> ret(row, 0.0);

	for(int j = row_ptr[r]; j < row_ptr[r+1]; j++){
		ret.data()[col_ind[j]] = val[j];
	}
	return ret;
}


d_real_vector d_real_SpMat::get_col_vec(const long c){
	if(row < c){
		std::cerr << "error bad col" << std::endl;
		assert(1);
	}
	std::vector<double> ret(row, 0.0);

#pragma omp parallel for
	for(int i=0; i<row; i++){
		for(int j = row_ptr[i]; j < row_ptr[i+1]; j++){
			if(col_ind[j] == c)
				ret.data()[i] = val[j];
		}
	}
	return ret;
}


d_real_vector d_real_SpMat::get_diag_vec(){
	std::vector<double> ret(row, 0.0);

#pragma omp parallel for
	for(int i=0; i<row; i++){
		for(int j = row_ptr[i]; j < row_ptr[i+1]; j++){
			if(i == col_ind[j])
				ret.data()[i] = val[j];
		}
	}
	return ret;
}
////////////////////////////////////////////////
