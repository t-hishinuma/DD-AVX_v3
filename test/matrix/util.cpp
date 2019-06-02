#include<DD-AVX.hpp>
#include<vector>
#include<iostream>

int main(int argc, char** argv){
	d_real_SpMat A;
	A.input_mm("./test.mtx");

	d_real_vector row2(A.get_row(),0.0);
	get_row_vec(1, A, row2);
	row2.print_all();

	d_real_vector col2(A.get_row(),0.0);
	get_col_vec(1, A, col2);
	col2.print_all();

	return 0;
}

