#include<DD-AVX.hpp>

double d_real_matrix::at(long r, long c){
		for(int j = row_ptr[r]; j < row_ptr[r+1]; j++){
			if(col_ind[j] == c){
				return val[j];
			}
		}
		return 0.0;
}
