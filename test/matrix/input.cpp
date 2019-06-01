#include<DD-AVX.hpp>
#include<vector>
#include<iostream>

int main(int argc, char** argv){
	d_real_SpMat A;
	A.input_mm("./test.mtx");
	A.output();
	A.output_mm("./out");


	return 0;
}

