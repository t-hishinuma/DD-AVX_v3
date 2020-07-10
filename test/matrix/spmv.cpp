#include<DD-AVX.hpp>
#include<vector>
#include<iostream>
#define TOL 1.0e-6

void make_ans(const d_real_SpMat& A, const std::vector<double>& x, std::vector<double>& y){
#pragma omp parallel for
	for(int i=0 ; i < A.get_row() ; i++){
		for(int j = A.row_ptr[i]; j < A.row_ptr[i+1]; j++){
			y[i] += A.val[j] * x[A.col_ind[j]];
		}
	}
}

bool err_check(const std::vector<double>& ans, const std::vector<double>& val, const double tol){
	for(int i=0; i<ans.size(); i++){
		double err = fabs((val[i] - ans[i])) / fabs(ans[i]);
		if(err > tol){
			printf("ans[%d] = %e, data[%d] = %e, err = %e\n", i, ans[i], i, val[i], err);
			return false;
		}
	}
	return true;
}

template<typename X, typename Y>
int test(d_real_SpMat& A){

 	X x(A.get_row(), 1.0);
 	Y y(A.get_row(), 0.0);

	std::vector<double> ans(y.size(), 0.0);
	
	dd_avx::matvec(A, x, y);

	make_ans(A, x.HI(), ans );

	if(err_check(ans, y.HI(), TOL)){
		std::cout << "pass" << std::endl;
	}
	else{
		std::cout << "fail" << std::endl;
		return false;
	}


	return true;
}

int main(int argc, char** argv){
	bool ret=0;

	d_real_SpMat A;
    std::cout << "hello" << std::endl;
	A.input_mm("./cage9/a");
    std::cout << "hello" << std::endl;

	std::cout << "DD = DMat * DD" << std::endl;
	ret = test<dd_real_vector, dd_real_vector>(A);
	if(ret == false) return ret;

	std::cout << "D = DMat * DD" << std::endl;
	ret = test<d_real_vector, dd_real_vector>(A);
	if(ret == false) return ret;

	std::cout << "DD = DMat * D" << std::endl;
	ret = test<dd_real_vector, d_real_vector>(A);
	if(ret == false) return ret;
	
	std::cout << "D = DMat * D" << std::endl;
	ret = test<d_real_vector, d_real_vector>(A);
	if(ret == false) return ret;

	return 0;
}

