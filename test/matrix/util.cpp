#include<DD-AVX.hpp>
#include<vector>
#include<iostream>

int main(int argc, char** argv){
	d_real_SpMat A;
	A.input_mm("./test.mtx");

	std::cout << "row #2" << std::endl;
	d_real_vector row2 = A.get_row_vec(1);
	row2.print_all();

	std::cout << "col #2" << std::endl;
	d_real_vector col2 = A.get_col_vec(1);
	col2.print_all();

	std::cout << "diag" << std::endl;
	d_real_vector diag  = A.get_diag_vec();
	diag.print_all();

	/////////////////////////////////////
	std::cout << "" << std::endl;

	d_real_vector row1 = A.get_row_vec(0);
	row1.print_all();
	
	

	return 0;
}

